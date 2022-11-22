#define _CRT_SECURE_NO_WARNINGS 1
//电梯智能控制算法设计实现	
//为方便人员上下，对电梯进行进行智能调度可以有效提高人员乘坐电梯的响应速度，节省电梯运行所需的能源，提升电梯运行效率和使用寿命。
//若高楼有m层、n部电梯，则如何进行电梯的运行控制需要进行优化设计。
#include<stdio.h>
#include<stdlib.h>            //生成随机数 
#include<time.h>              //用于重置随机数种子
#include<thread>              //用于创建线程
#include<string.h>            //memset(a,0,sizeof(a)) 将数组a赋值
#include<conio.h>             //getch()
#include<easyx.h>             //内置了windows.h 延时函数Sleep() 单位毫秒
#include<mmsystem.h>          //要写在easyx的下方  多媒体设备接口头文件
#pragma comment(lib,"winmm.lib") //包含静态库

//运行条件：上行的人只按上行按键 只坐上行电梯 下行同理
#define height 10          //楼层高度
#define liftnum 3          //电梯数量
#define loadmax 10         //电梯满载人数
#define speed   1000       //电梯上下行每层所用时间（毫秒）
#define wait   3000       //电梯在楼层等待耗时
typedef struct LIFT
{
	int load;
	int con;       //-1表示下行 0表示待响应 1表示上行
	int full;      //0表示未满 1表示已满
	int goal;           //目标楼层
	int current;        //当前楼层
	int pass[2];   //欲停留的楼层  第一个数字存楼层 第二个数字存信号内外 1表示内 2表示外 3表示内外都有 4表示反向信号
	int button[height];//电梯内的楼层按钮
}LIFT;
typedef struct FLOOR
{
	int ubutton;  //定义楼层按钮 0表示未按下 1表示已按下
	int dbutton;
}FLOOR;
FLOOR f[height] = { 0 };      //初始化楼层信息
void Checkup(LIFT *lift)        //不断检测是否有在当前楼层之上的上行命令
{
	int i, max , j,count;            //检测不到终点下行的信号
	while(1)
	{
		for (i = lift->current,count=0, j = 1, max = lift->current; i <= height; i++)
		{
			if (lift->con == 0)   //只有在未响应状态才接受下行信号
			{
				if (f[i - 1].dbutton == 1)
				{
					max = i;
					lift->pass[0] = i;
					lift->pass[1] = 4;   //反向的信号
					lift->con = 1;
				}
			}
			if (f[i - 1].ubutton == 0 && lift->button[i - 1] == 0)
				continue;
			else 
			{
				max = i;
				if(count++==0)                 //找到第一次
				{
						lift->pass[0] = i;    //存储上行时被按下上行按钮的楼层编号 只需一个数
						if (f[i - 1].ubutton == 1 && lift->button[i - 1] == 1)
							lift->pass[1] = 3;
						else if (f[i - 1].ubutton == 1)
							lift->pass[1] = 2;
						else 
							lift->pass[1] = 1;
				}//分辨电梯内还是外的信号
			}
		}
		if (lift->con != 1)
			lift->con = 1;
		if(max> lift->goal)                 //尽量减少对共享资源的写入次数
			lift->goal = max;               //存储最高响应楼层
		if (lift->current == lift->goal)  //抵达最终目标楼层时停止扫描 即停止该线程
			return;
		Sleep(500);                  //每隔0.5秒扫描一次
	}
}
void Checkdown(LIFT* lift)        //不断检测是否有在当前楼层之上的上行命令
{
	int i, min, j, count;            //检测不到终点下行的信号
	while (1)
	{
		for (i = lift->current, count = 0, j = 1, min = lift->current; i >= 1; i--)
		{
			if (lift->con == 0)   //只有在未响应状态才接受下行信号
			{
				if (f[i - 1].ubutton == 1)
				{
					min = i;
					lift->pass[0] = i;
					lift->pass[1] = 4;   //反向的信号
					lift->con = -1;
				}
			}
			if (f[i - 1].dbutton == 0 && lift->button[i - 1] == 0)
				continue;
			else
			{
				min = i;
				if (count++ == 0)                 //找到第一次
				{
					lift->pass[0] = i;    //存储上行时被按下上行按钮的楼层编号 只需一个数
					if (f[i - 1].dbutton == 1 && lift->button[i - 1] == 1)
						lift->pass[1] = 3;
					else if (f[i - 1].dbutton == 1)
						lift->pass[1] = 2;
					else
						lift->pass[1] = 1;
				}//分辨电梯内还是外的信号
			}
		}
		if (lift->con != -1)
			lift->con = -1;
		if (min < lift->goal)                 //尽量减少对共享资源的写入次数
			lift->goal = min;               //存储最高响应楼层
		if (lift->current == lift->goal)  //抵达最终目标楼层时停止扫描 即停止该线程
			return;
		Sleep(500);                  //每隔0.5秒扫描一次
	}
}
void Goup(LIFT *lift)
{
	IMAGE up,down;
	loadimage(&up, "./up.jpg", 35, 35);
	loadimage(&down, "./down.jpg", 35, 35);
	memset((*lift).pass, 0, sizeof((*lift).pass));        //应该要到达目标楼层 每次上行将路径清零
	std::thread constcheckup(Checkup, std::ref(lift));    //创建持续向上扫描的线程 地址用ref
	constcheckup.detach();
	Sleep(1000);                      //等待扫描完成
	for (int* p = (*lift).pass;;)
	{
		if ((*lift).current == *p)        //电梯在楼层停下 撤销该层和电梯的按钮响应
		{
			switch((*lift).pass[1])
			{
			case 3:   //先下后上
			case 2:
				putimage(60, 15 + (height - (*lift).current) * 40, &up); //撤销该楼层图画响应
				f[(*lift).current - 1].ubutton = 0;                      //撤销该楼层按钮响应
				if ((*lift).pass[1] == 2)
					break;
			case 1:
				(*lift).button[(*lift).current - 1] = 0; //撤销该楼层电梯按钮响应 ？？？ checklist可能有问题 对最终楼层另外处理
				break;
			case 4:
				putimage(100, 15 + (height - (*lift).current) * 40, &down); //撤销该楼层图画响应
				f[lift->current - 1].dbutton = 0;
			}
			FlushBatchDraw();
			Sleep(wait);            //电梯在某层停留
		}
		if ((*lift).current == (*lift).goal)    //对于最终楼层单独处理
			break;
		Sleep(speed);               //电梯上行
		(*lift).current++;
		printf("%d\n", (*lift).current);
	}
	(*lift).con = 0;                     //到达目标楼层后 电梯恢复为未响应状态
}
void Godown(LIFT* lift)
{
	IMAGE up, down;
	loadimage(&up, "./up.jpg", 35, 35);
	loadimage(&down, "./down.jpg", 35, 35);
	memset((*lift).pass, 0, sizeof((*lift).pass));        //应该要到达目标楼层 每次上行将路径清零
	std::thread constcheckdown(Checkdown, std::ref(lift));    //创建持续向上扫描的线程 地址用ref
	constcheckdown.detach();
	Sleep(1000);                      //等待扫描完成
	for (int* p = (*lift).pass;;)
	{
		if ((*lift).current == *p)        //电梯在楼层停下 撤销该层和电梯的按钮响应
		{
			switch ((*lift).pass[1])
			{
			case 3:   //先下后上
			case 2:
				putimage(100, 15 + (height - (*lift).current) * 40, &down); //撤销该楼层图画响应
				f[(*lift).current - 1].dbutton = 0;                      //撤销该楼层按钮响应
				if ((*lift).pass[1] == 2)
					break;
			case 1:
				(*lift).button[(*lift).current - 1] = 0; //撤销该楼层电梯按钮响应 ？？？ checklist可能有问题 对最终楼层另外处理
				break;
			case 4:
				putimage(60, 15 + (height - (*lift).current) * 40, &up); //撤销该楼层图画响应
				f[lift->current - 1].ubutton = 0;
			}
			FlushBatchDraw();
			Sleep(wait);            //电梯在某层停留
		}
		if ((*lift).current == (*lift).goal)    //对于最终楼层单独处理
			break;
		Sleep(speed);               //电梯上行
		(*lift).current--;
		printf("%d\n", (*lift).current);
	}
	(*lift).con = 0;                     //到达目标楼层后 电梯恢复为未响应状态
}
int Checklist(LIFT *lift)  //给未响应的电梯设置目标 上下就近原则  
{
	int i,count,upmin=lift->current,downmin=lift->current,upmin1=0,downmin1= 0;
	//提高电梯内按键的优先级 使其比楼层按键更先响应
	for (i = lift->current, count = 0; i <= height; i++)        //向上扫描是否有任意按键按下
	{
		if (f[i - 1].ubutton == 1 || f[i - 1].dbutton == 1)
		{
			if(count++==0)
				upmin = i;
		}
		if (lift->button[i - 1] == 1)
			upmin1 = i;
	}
	if (lift->current > height)        //解除警告
		exit(-1);
	for (i = lift->current,count=0; i >= 1; i--)        //向下扫描是否有任意按键按下
	{
		if (f[i - 1].ubutton == 1 || f[i - 1].dbutton == 1)
		{
			if (count++ == 0)
				downmin = i;
		}
		if (lift->button[i - 1] == 1)
			downmin1 = i;
	}
	if (upmin1)
		return 1;
	else if (downmin1)
		return -1;
	else if(upmin==downmin)      //上下都没有信号响应
		return 0;
	else if (upmin == lift->current)  //上行无信号 那就下行
		return -1;
	else if (downmin == lift->current)
		return 1;
	else if (fabs(upmin-lift->current) <= fabs(downmin-lift->current)) //？？？
		return 1;
	else 
		return -1;
}
void Run(LIFT *lift)
{
	while (1)
	{
		switch(Checklist(lift))
		{
		case 1: Goup(lift);
			break;
		case -1:Godown(lift);
			break;
		case 0:Sleep(1000);         //让空闲电梯每隔2秒checklist一次
			break;
		}
	}
}
void Imput()
{
	int ran = 1, i = 1;
	while (1)
	{
		srand((unsigned)time(NULL));     //初始化随机数种子
		ran = rand() % height;
		if (i % 2)
		{
			printf("是否按下第%d楼层的下行", ran+1);
			scanf("%d", &f[ran].dbutton);
		}
		else
		{
			printf("是否按下第%d楼层的上行", ran+1);
			scanf("%d", &f[ran].ubutton);
		}
		i++;
	}
}
void Printfloor()
{
	int i;
	char arr[5] = { 0 };
	setbkmode(TRANSPARENT);
	settextstyle(35, 0, "微软黑体");         //定义字高
	IMAGE up, down;
	loadimage(&up, "./up.jpg", 35, 35);      //加载上下按钮图片
	loadimage(&down, "./down.jpg", 35, 35);
	for(i=1;i<=height;i++)                   //输出楼层 实际按钮宽高为40 起始为60 15
	{
		sprintf(arr, "%-d", height - i+1);
		outtextxy(15, 15+(i-1)*40, arr);
		putimage(60, 15 + (i - 1) * 40, &up);    //上键x=60 y=15+（楼数减一）*40
		putimage(100, 15 + (i - 1) * 40, &down);
	}
	FlushBatchDraw();
}
void Pressfloor()
{
	IMAGE up1, down1;
	loadimage(&up1, "./up1.jpg", 35, 35);
	loadimage(&down1, "./down1.jpg", 35, 35);
	int i;
	ExMessage msg;
	while(1)
	{
		if (peekmessage(&msg, EX_MOUSE) && msg.message == WM_LBUTTONDOWN)
		{
			for (i = 1; i <= height; i++) //逐楼层检测是否有按钮按下
			{
				if (msg.x > 60 && msg.x < 100 && msg.y>15 + (i - 1) * 40 && msg.y < 15 + i * 40)
				{
					f[height - i].ubutton = 1;  //令该楼层上行按钮响应
					putimage(60, 15 + (i - 1) * 40, &up1);
					FlushBatchDraw();
				}
				if (msg.x > 100 && msg.x < 140 && msg.y>15 + (i - 1) * 40 && msg.y < 15 + i * 40)
				{
					f[height - i].dbutton = 1;  //令该楼层下行按钮响应
					putimage(100, 15 + (i - 1) * 40, &down1);
					FlushBatchDraw();
				}
			}
		}
	}
}
int main()
{
	LIFT lift[liftnum] = {0};
	int i;
	for (i = 1; i <= liftnum; i++)  //初始化电梯信息  都在一楼
		lift[i - 1] = { 0,0,0,0,1 ,{0} };
	//注意这里参数传的不是地址 只是值而已！！
	initgraph(640,480,EX_SHOWCONSOLE);
	BeginBatchDraw();
	Printfloor();
	//Pressfloor();
	f[2].ubutton = 1;
	lift[0].button[5] = 1;
	//lift[0].current = 10;
	std::thread lift1(Run, &lift[0]);          //创建电梯线程 慎用detach 会很卡
	std::thread pressfloor(Pressfloor);
	lift1.join();
	pressfloor.join();
	EndBatchDraw();
	getchar();
	closegraph();
	return 0;
}

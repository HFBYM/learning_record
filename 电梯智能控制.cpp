#define _CRT_SECURE_NO_WARNINGS 1    //解除scanf的警告
//电梯智能控制算法设计实现	
//为方便人员上下，对电梯进行进行智能调度可以有效提高人员乘坐电梯的响应速度，节省电梯运行所需的能源，提升电梯运行效率和使用寿命。
//若高楼有m层、n部电梯，则如何进行电梯的运行控制需要进行优化设计。
#include<stdio.h>
#include<thread>                 //用于创建线程
#include<string.h>               //memset(a,0,sizeof(a)) 将数组a赋值
#include<easyx.h>                //内置了windows.h 延时函数Sleep() 单位毫秒
#include<mmsystem.h>             //要写在easyx的下方  多媒体设备接口头文件
#pragma comment(lib,"winmm.lib") //包含静态库

//                           README
//运行条件：上行的人只按上行按键 只坐上行电梯 不乱按电梯 下行同理
//按下按钮有所卡顿属于正常情况  设置了延时 防止乱按  多按几次即可
//音乐方面不知道为什么只会响一次  已经注释掉了
//人员输入输出等程序 若嫌麻烦可以注释掉
//注意！！更改电梯数目后要去主函数更改相应的线程数量！！
#define height 15          //楼层高度
#define liftnum 3          //电梯数量
#define loadmax 15         //电梯满载人数
#define speed   1000       //电梯上下行每层所用时间（毫秒）
#define wait   3000       //电梯在楼层等待耗时
typedef struct LIFT
{
	int load;           //电梯所载的人数
	int con;            //电梯状态 -1表示下行 0表示待响应 1表示上行
	int goal;           //目标楼层
	int current;        //当前楼层
	int pass[2];        //欲停留的楼层  第一个数字存楼层 第二个数字存这个信号的类型 1表示电梯内信号 2表示楼层信号 3表示两者都有 4表示楼层的反向信号
	int button[height]; //电梯内的按钮 1表示被按下
}LIFT;
typedef struct FLOOR
{
	int ubutton;  //定义楼层上行按钮 0表示未按下 1表示已按下
	int dbutton;
}FLOOR;
FLOOR f[height] = { 0 };      //初始化楼层信息
void Printbutton(int x, int y, int w, int h,int i,int color) //用于画电梯按钮
{ //左上角的坐标 长宽 楼层号 颜色 0为蓝 其他为红
	char text[4];
	sprintf(text, "%d", i);             //转换函数 把数字和文字信息一起存到字符串中
	if (color == 0)
		setfillcolor(RGB(0, 117, 218));
	else
		setfillcolor(RED);
	settextstyle(30, 0, "微软黑体");
	int tx, ty;                         //居中处理
	tx = x + (w - textwidth(text))/2;
	ty = y + (h - textheight(text)) / 2;
	solidrectangle(x, y, x + w, y + h);
	outtextxy(tx,ty,text);
}
void Dingdong()
{
	mciSendString("open ./dingdong.mp3 alias dingdong",0,0,0 );
	mciSendString("play dingdong", 0, 0, 0);
	mciSendString("close dingodng", 0, 0, 0);

}
void Chageliftbutton(int i,int n,int h)    //用于改变被点击的电梯按钮颜色
{                                          //i是楼层号 n是电梯编号 h是一组电梯图案的高度
	int k,j;                               //用于确定被按的按钮位置
	if (i % 10 == 0)
		k = i / 10-1;
	else
		k = i / 10 ;
	j = i - k * 10;
	Printbutton(360 + (j - 1) * 40, 15 + k * 40 + (n - 1) * h,35, 35, i, 0);
}
void Load(LIFT* lift, int n, int check)  //用于写入电梯人数的进出  check==0是进入 1是出去
{
	char imput[5] = { 0 };
	char tip[50];               //弹出窗口的提示
	sprintf(tip, "请输入%d号电梯在第%d层", n, lift->current);
	if (check == 0)
		strcat(tip, "进入了多少人");
	else
		strcat(tip, "下去了多少人");
	HWND hnd = GetHWnd();       //获得绘图窗口句柄
	int num = 0;
	if(check==0)
	{
		do
		{
			InputBox(imput, 5, tip, 0, 0, 500, 0);    //弹出写入窗口
			num = atoi(imput);                        //将字符串转换为整型
			if (num + lift->load > loadmax)
				MessageBox(hnd, NULL, "超载 请重新输入", MB_OK);   //弹出警示窗口
			else
			{
				lift->load += num;
				break;
			}
		} while (1);
	}
	else
	{
		InputBox(imput, 5, tip, 0, 0, 500, 0);
		num = atoi(imput);
		lift->load -= num;
	}
	return;
}
void Checkup(LIFT *lift)        //不断检测是否有在当前楼层之上的上行命令
{
	int i, max , j,count;            
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
						lift->pass[0] = i;    //存储上行时被按下上行按钮的楼层编号 
						if (f[i - 1].ubutton == 1 && lift->button[i - 1] == 1)//分辨电梯内还是外的信号
							lift->pass[1] = 3;
						else if (f[i - 1].ubutton == 1)
							lift->pass[1] = 2;
						else 
							lift->pass[1] = 1;
				}
			}
		}
		if (lift->con != 1)                 //尽量减少对共享资源的写入次数
			lift->con = 1;
		if(max> lift->goal)                 //尽量减少对共享资源的写入次数
			lift->goal = max;               //存储最高响应楼层
		if (lift->current == lift->goal)  //抵达最终目标楼层时停止扫描 即停止该线程
			return;
		Sleep(500);                  //每隔0.5秒扫描一次
	}
}
void Checkdown(LIFT* lift)        //不断检测是否有在当前楼层之下的下行命令
{
	int i, min, j, count;            
	while (1)
	{
		for (i = lift->current, count = 0, j = 1, min = lift->current; i >= 1; i--)
		{
			if (lift->con == 0)   //只有在未响应状态才接受上行信号
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
					lift->pass[0] = i;    //存储下行时被按下下行按钮的楼层编号 只需一个数
					if (f[i - 1].dbutton == 1 && lift->button[i - 1] == 1)
						lift->pass[1] = 3;
					else if (f[i - 1].dbutton == 1)
						lift->pass[1] = 2;
					else
						lift->pass[1] = 1;
				}
			}
		}
		if (lift->con != -1)
			lift->con = -1;
		if (min < lift->goal)                //尽量减少对共享资源的写入次数
			lift->goal = min;               //存储最低响应楼层
		if (lift->current == lift->goal)  //抵达最终目标楼层时停止扫描 即停止该线程
			return;
		Sleep(500);                  //每隔0.5秒扫描一次
	}
}
void Updateinfo(LIFT* lift, int n, int h)
{
	char a[25] = "电梯1: 人数:";                    //主要是为了得到这个字符串的宽度
	const char* b[3] = { "下行","待响应","上行" };
	int w = textwidth(a);
	settextstyle(30, 0, "微软黑体");   //设置字体样式
	clearrectangle(760 + w, 20 + (n - 1) * h, 760 + w + 100, 20 + (n - 1) * h + 30); //擦除人数
	sprintf(a, "%d", lift->load);       //把人数当字符串存储
	outtextxy(760 + w, 20 + (n - 1) * h, a); //显示人数
	clearrectangle(760 + w, 60 + (n - 1) * h, 760 + w + 100, 90 + (n - 1) * h ); //擦除状态
	outtextxy(760 + w, 20 + (n - 1) * h+40, b[lift->con+1]); //显示状态
	strcpy(a, "电梯1: 当前楼层:");  //主要是为了得到这个字符串的宽度
	w = textwidth(a);
	clearrectangle(760 + w, 100 + (n - 1) * h , 760 + w + 100, 130 + (n - 1) * h ); //擦除当前楼层
	sprintf(a, "%d", lift->current);
	outtextxy(760 + w, 100 + (n - 1) * h, a); //显示当前楼层
	FlushBatchDraw();
}
void Goup(LIFT *lift,int n)  //n是电梯编号
{
	int h;
	if (height % 10 == 0)
		h = height / 10;
	else
		h = height / 10 + 1;
	h = ((h * 40) > 120) ? h * 40 : 120;  //计算出电梯图像的高度 即左边楼层按钮高度与右侧状态栏高度的较大值
	IMAGE up,down;      //加载图片 准备覆盖
	loadimage(&up, "./up.jpg", 35, 35);
	loadimage(&down, "./down.jpg", 35, 35);
	memset((*lift).pass, 0, sizeof((*lift).pass));        //预到达的楼层 每次上行清零
	std::thread constcheckup(Checkup, std::ref(lift));    //创建持续向上扫描的线程 
	constcheckup.detach();                                //将刚创建的线程挂在后台
	Sleep(1000);                      //等待这个扫描线程执行完第一次完成
	for (int* p = (*lift).pass;;)
	{
		if ((*lift).current == *p)        //电梯在楼层停下 
		{
			//Dingdong();
			switch((*lift).pass[1])       //判断这个楼层停留是楼层按的按钮还是电梯内按的
			{
			case 3:   //先下后上
			case 2:
				putimage(60, 15 + (height - (*lift).current) * 40, &up); //撤销该楼层图画响应
				f[(*lift).current - 1].ubutton = 0;                      //撤销该楼层按钮响应
				Load(lift, n, 0);                                        //下去几个人
				if ((*lift).pass[1] == 2)
					break;
			case 1:
				Chageliftbutton(lift->current, n, h);    //撤销该楼层电梯图画按钮响应
				(*lift).button[(*lift).current - 1] = 0; //撤销该楼层电梯按钮响应 
				Load(lift, n, 1);                       //进入几个人
				break;
			case 4:
				putimage(100, 15 + (height - (*lift).current) * 40, &down); //撤销该楼层图画响应
				f[lift->current - 1].dbutton = 0;
				Load(lift, n, 0);                       //进入几个人
			}
			FlushBatchDraw();
			Sleep(wait);            //电梯在某层停留
		}
		if ((*lift).current == (*lift).goal)    //对于最终楼层单独处理
			break;
		Sleep(speed);               //电梯上行
		(*lift).current++;
		printf("%d号电梯在%d层\n",n, (*lift).current);
		Updateinfo(lift, n, h);   //更新状态栏
	}
	(*lift).con = 0;                     //到达目标楼层后 电梯恢复为未响应状态
	Updateinfo(lift, n, h);      //更新状态栏

}
void Godown(LIFT* lift,int n)
{
	int h;
	if (height % 10 == 0)
		h = height / 10;
	else
		h = height / 10 + 1;
	h = ((h * 40) > 120) ? h * 40 : 120;
	IMAGE up, down;
	loadimage(&up, "./up.jpg", 35, 35);
	loadimage(&down, "./down.jpg", 35, 35);
	memset((*lift).pass, 0, sizeof((*lift).pass));        //应该要到达目标楼层 每次下行将路径清零
	std::thread constcheckdown(Checkdown, std::ref(lift));    //创建持续向下扫描的线程 地址用ref
	constcheckdown.detach();
	Sleep(1000);                      //等待扫描完成
	for (int* p = (*lift).pass;;)
	{
		if ((*lift).current == *p)        //电梯在楼层停下 撤销该层和电梯的按钮响应
		{
			Dingdong();
			switch ((*lift).pass[1])
			{
			case 3:   //先下后上
			case 2:
				putimage(100, 15 + (height - (*lift).current) * 40, &down); //撤销该楼层图画响应
				f[(*lift).current - 1].dbutton = 0;                      //撤销该楼层按钮响应
				Load(lift, n, 0);                       //下去几个人
				if ((*lift).pass[1] == 2)
					break;
			case 1:
				Chageliftbutton(lift->current, n, h);    //撤销该楼层电梯图画按钮响应
				(*lift).button[(*lift).current - 1] = 0; //撤销该楼层电梯按钮响应
				Load(lift, n, 1);                       //进入几个人
				break;
			case 4:
				putimage(60, 15 + (height - (*lift).current) * 40, &up); //撤销该楼层图画响应
				f[lift->current - 1].ubutton = 0;
				Load(lift, n, 0);                       //进入几个人
			}
			FlushBatchDraw();
			Sleep(wait);            //电梯在某层停留
		}
		if ((*lift).current == (*lift).goal)    //对于最终楼层单独处理
			break;
		Sleep(speed);               //电梯下行
		(*lift).current--;
		printf("%d号电梯在%d层\n", n, (*lift).current);
		Updateinfo(lift, n, h);
	}
	(*lift).con = 0;                     //到达目标楼层后 电梯恢复为未响应状态
	Updateinfo(lift, n, h);

}
int Checklist(LIFT *lift)  //给未响应的电梯设置目标 上下采用就近原则  
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
	if (upmin1)             //通过优先执行这两个数的判断来提高优先级
		return 1;
	else if (downmin1)
		return -1;
	else if(upmin==downmin)      //上下都没有信号响应
		return 0;
	else if (upmin == lift->current)  //上行无信号 那就下行
		return -1;
	else if (downmin == lift->current)
		return 1;
	else if (fabs(upmin-lift->current) <= fabs(downmin-lift->current)) // 比较上下响应楼层的距离 找近的那个
		return 1;
	else 
		return -1;
}
void Run(LIFT *lift,int n)
{
	while (1)
	{
		switch(Checklist(lift))     //检测上下行
		{
		case 1: Goup(lift,n);
			break;
		case -1:Godown(lift,n);
			break;
		case 0:Sleep(1000);         //让空闲电梯每隔2秒checklist一次
			break;
		}
	}
}
void Printfloor()
{
	int i;
	char arr[5] = { 0 };
	setbkmode(TRANSPARENT);                  //定义字体背景
	settextstyle(30, 0, "微软黑体");         //定义字高
	IMAGE up, down;
	loadimage(&up, "./up.jpg", 35, 35);      //加载上下按钮图片
	loadimage(&down, "./down.jpg", 35, 35);
	for(i=1;i<=height;i++)                   //输出楼层 实际按钮宽高为40 起始为60 15
	{
		sprintf(arr, "%-d", height - i+1);   //存储字符串
		outtextxy(15, 20+(i-1)*40, arr);
		putimage(60, 15 + (i - 1) * 40, &up);    //上键x=60 y=15+（楼数减一）*40
		putimage(100, 15 + (i - 1) * 40, &down);
	}
	FlushBatchDraw();
}
void Pressfloor()
{
	IMAGE up1, down1;                                 //加载被按下的图片
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
void Printliftandimput(LIFT *p)      
{
	int i,j,temp,w,h,k;   //h为上下电梯图像的间隔
	if (height % 10==0)
		h = height / 10;
	else
		h = height / 10+1;
	h = ((h * 40) > 120) ? h * 40 : 120;  
	char a[20] = { 0 };
	setfillcolor(RGB(0, 117, 218));    //设置按钮颜色
	settextstyle(30, 0, "微软黑体");   //设置字体样式
	for(k=1;k<=liftnum;k++)
	{
		for (i = 1, temp = 360, j = 0; i <= height; i++)
		{
			Printbutton(temp, 15 + j * 40 + (k - 1) * h, 35, 35, i, 0);  //0是蓝色 其他为红色 
			temp += 40;
			if (i % 10 == 0)               //十楼换一层
			{
				j++;
				temp -= 400;
			}
		}
		sprintf(a, "电梯%d: 人数:0", k);               //存储电梯编号
		outtextxy(760, 20 + (k - 1) * h, a);           
		w = textwidth("电梯0: ");
		strcpy(a , "状态:未响应");
		outtextxy(760 + w, 60 + (k - 1) * h, a);
		strcpy(a, "当前楼层:1");
		outtextxy(760 + w, 100 + (k - 1) * h, a);
	}
	FlushBatchDraw();
	ExMessage msg;
	while(1)
	{
		if (peekmessage(&msg, EX_MOUSE) && msg.message == WM_LBUTTONDOWN)  //直接对所有电梯进行写入 怎么画就怎么写入
		{
			for (k = 1; k <= liftnum; k++)
			{
				for (i = 1, temp = 360, j = 0; i <= height; i++)
				{
					if (msg.x > temp && msg.x < temp + 35 && msg.y>15 + j * 40 + (k - 1) * h && msg.y < 15 + j * 40 + (k - 1) * h + 35)
					{
						Printbutton(temp, 15 + j * 40 + (k - 1) * h, 35, 35, i, 1);  //0是蓝色 其他为红色
						(p + k - 1)->button[i - 1] = 1;
						FlushBatchDraw();
					}
					temp += 40;
					if (i % 10 == 0)
					{
						j++;
						temp -= 400;
					}
				}
			}
		}
	}
	FlushBatchDraw();
}
int main()
{
	LIFT lift[liftnum] = {0};
	int i,h;
	if (height % 10 == 0)
		h = height / 10;
	else
		h = height / 10 + 1;
	h = ((h * 40) > 120) ? h * 40 : 120;  //计算出电梯图像的高度 即左边楼层按钮高度与右侧状态栏高度的较大值
	h = (liftnum * h > height * 40) ? liftnum * h : height * 40;  //比较楼层总高和电梯图案总高 确定绘图窗口的大小
	for (i = 1; i <= liftnum; i++)  //初始化电梯信息  都在一楼
		lift[i - 1] = { 0,0,0,1 ,{0} };
	initgraph(1100,h+20,EX_SHOWCONSOLE);    //开始绘图窗口 可通过控制台查看各个电梯运行轨迹
	BeginBatchDraw();                       //开始批量制图
	Printfloor();                           //画楼
	std::thread pressfloor(Pressfloor);     //开辟按楼线程
	std::thread liftimput(Printliftandimput, std::ref(lift)); //开辟按电梯线程
	//创建电梯线程  最后一个数是电梯编号
	std::thread lift1(Run, &lift[0], 1);     
	std::thread lift2(Run, &lift[1], 2);
	std::thread lift3(Run, &lift[2], 3);

	liftimput.join();                                   //线程加入
	pressfloor.join();
	lift1.join();      //由于线程的创建限制 每个电梯都要手输 所以当电梯数更改时 电梯线程数也要手动更改
	lift2.join();
	lift3.join();

	EndBatchDraw();   //结束批量绘图
	getchar();
	closegraph();
	return 0;
}

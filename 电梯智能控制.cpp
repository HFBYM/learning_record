#define _CRT_SECURE_NO_WARNINGS 1
//电梯智能控制算法设计实现	
//为方便人员上下，对电梯进行进行智能调度可以有效提高人员乘坐电梯的响应速度，节省电梯运行所需的能源，提升电梯运行效率和使用寿命。
//若高楼有m层、n部电梯，则如何进行电梯的运行控制需要进行优化设计。
#include<stdio.h>
#include<string.h>            //memset(a,0,sizeof(a)) 将数组a赋值
#include<conio.h>             //getch()
#include<easyx.h>             //内置了windows.h 延时函数Sleep() 单位毫秒
#include<mmsystem.h>          //要写在easyx的下方  多媒体设备接口头文件
#pragma comment(lib,"winmm.lib") //包含静态库

//运行条件：上行的人只按上行按键 只坐上行电梯 下行同理
#define height 10          //楼层高度
#define liftnum 3          //电梯数量
#define loadmax 10         //电梯满载人数
#define speed   3000       //电梯上下行每层所用时间（毫秒）
#define wait   6000       //电梯在楼层等待耗时
typedef struct LIFT
{
	int load;
	int con;       //-1表示下行 0表示待响应 1表示上行
	int full;      //0表示未满 1表示已满
	int goal;           //目标楼层
	int current;        //当前楼层
	int pass[height];   //欲停留的楼层
	int lbutton[height];//电梯内的楼层按钮
}LIFT;
typedef struct FLOOR
{
	int ubutton;  //定义楼层按钮 0表示未按下 1表示已按下
	int dbutton;
}FLOOR;
FLOOR f[height] = { 0 };      //初始化楼层信息
int Checkup(LIFT lift)        //不断检测是否有在当前楼层之上的上行命令
{
	int i,max=lift.current,j;
	for (i = lift.current,j=1; i <= height; i++)
	{
		if (f[i - 1].ubutton == 0&&lift.lbutton[i-1]==0)
			continue;
		else
		{
			f[i - 1].ubutton = 0;
			lift.lbutton[i - 1] = 0;
			lift.pass[j++ - 1] = i;              //存储上行时被按下上行按钮的楼层编号
			max = i;
		}
	}
	return max;
}
void Goup(LIFT lift)
{
	memset(lift.pass, 0, sizeof(lift.pass));        //应该要到达目标楼层 每次上行将路径清零
	lift.goal = Checkup(lift);
	for (int*p=lift.pass;;)
	{
		if (lift.current==*p)        //电梯在楼层停下
		{
			Sleep(10000);
			p++;
		}
		if (lift.current == lift.goal)
			break;
		//Sleep(speed);               //电梯上行
		lift.current++;
		printf("%d\n", lift.current);
	}
}
int main()
{
	LIFT lift[liftnum] = {0};
	int i;
	for (i = 1; i <= liftnum; i++)  //初始化电梯信息  都在一楼
		lift[i - 1] = { 0,0,0,0,1 ,{0} };

	f[3].ubutton = 1;
	lift[0].lbutton[5] = 1;
	Goup(lift[0]);

	return 0;
}
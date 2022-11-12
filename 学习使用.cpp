#define _CRT_SECURE_NO_WARNINGS 1  //备注与提示
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>           //malloc函数  用其构成的二维数组可以传递二级指针而不用数组指针
#include <conio.h>           //getch 
#include<easyx.h>            //在项目 配置设置 高级 选择使用多字节
#include<mmsystem.h>         //音乐播放  有些mp3格式是假的 无法播放
#pragma comment(lib,"winmm.lib")   //静态库
//对于矩形外框 还是每边独立循环好 每次是类似的变换  每边都是i=1 到i=n-1

void E(int(*a)[m], int m, int n)
{
	printf("%d", a[m - 1][n - 1]);
}
int main()
{
	int a[1][2] = { 0 };
	E(a, 1, 2);
	return 0;
}

//easyx内容从此开始

//void Change()
//{   
//	HWND hnd = GetHWnd(); //获取窗口句柄   这是设的640 480的窗口句柄
//	SetWindowText(hnd, "油饼食不食");    //更改窗口名
//	int isok=MessageBox(hnd, "你是不是真ikun？", "请作答", MB_YESNO);  //是有返回值的
//	if (isok == IDYES)
//	{
//		printf("铁粉是黑的");
//	}
//	else if (isok == IDNO)
//		printf("钾粉是白的");
//}
//void Bgm()
//{
//	mciSendString("open ./鸡.mp3 alias song", 0, 0, 0);       //文件拓展名不要隐藏！！！
//	mciSendString("play song ", 0, 0, 0);
//	//wait 等待音乐放完再进行接下来的代码
//	//repeat 重复播放
//}
//int main()
//{
//	initgraph(640, 480, EX_SHOWCONSOLE | EX_NOMINIMIZE);
//	int x = 30, y = 30;
//	Bgm();
//	setfillcolor(GREEN);
//	IMAGE img;
//	loadimage(&img, "./CTRL.jpg",500,300);
//	putimage(0, 0, &img);
//	Change();
//	while(1)               
//	{
//		BeginBatchDraw();   //防止闪图 放在绘图代码的前面和后面 对图片进行缓存处理 有延迟?
//		setbkcolor(YELLOW);
//		cleardevice();
//		putimage(0, 0, &img);
//		fillcircle(x, y, 10);
//		//if(_kbhit())               //防止阻塞      延迟突然没了 可能与此有关
//		//{
//		//	char key = _getch();      //会阻塞在这里 一直等
//		//	switch (key)              //要判断出每个键的虚拟值才好用
//		//	{
//		//	case 72:
//		//	case 'w':        printf("UP\n");
//		//		y -= 8;
//		//		break;
//		//	case 80:
//		//	case 's':        printf("DOWN\n");
//		//		y += 8;
//		//		break;
//		//	case 75:
//		//	case 'a':        printf("LEFT\n");
//		//		x -= 8;
//		//		break;
//		//	case 77:
//		//	case 'd':        printf("RIGHT\n");
//		//		x += 8;
//		//		break;
//		//	}
//		//}
//		if (GetAsyncKeyState(VK_UP))      //极其丝滑  可以斜着走 但太快了
//			y -= 1;
//		if (GetAsyncKeyState(VK_DOWN))
//			y += 1;
//		if (GetAsyncKeyState(VK_LEFT))
//			x -= 1;
//		if (GetAsyncKeyState(VK_RIGHT))
//			x += 1;
//		EndBatchDraw();
//
//	}
//
//
//	getchar();
//	closegraph();
//	return 0;
//}

//void Button(int x, int y, int w, int h);
//int main()
//{
//	initgraph(640, 480,EX_SHOWCONSOLE|EX_NOMINIMIZE);
//	Button(30,20,400,300);
//	setbkmode(TRANSPARENT);        //主函数与分支函数中定义不一样
//	settextstyle(50, 0, "黑体");
//	ExMessage msg;                 //定义一个信息结构体
//	while(1)
//	{
//		if (peekmessage(&msg, EX_MOUSE))   //判断鼠标信息
//		{                                  //悬停也算有鼠标信息
//			switch (msg.message)           //判断鼠标位置
//			{
//			case WM_LBUTTONDOWN: 
//				if (msg.x < 430 && msg.x>30 && msg.y < 320 && msg.y>20)
//					cleardevice();
//					outtextxy(30, 320, "MOUSE LBUTTONDOWN");
//				break;
//			case WM_RBUTTONDOWN: 
//				if (msg.x < 430 && msg.x>30 && msg.y < 320 && msg.y>20)
//					cleardevice();
//					outtextxy(30, 320, "MOUSE RBUTTONDOWN");
//				break;
//			}
//		}
//	}
//
//	getchar();
//	closegraph();
//	return 0;
//}
//void Button(int x,int y,int w,int h)
//{
//	setfillcolor(YELLOW);
//	settextcolor(RED);
//	setbkmode(TRANSPARENT);
//	settextstyle(50, 0, "黑体");
//	fillrectangle(x, y, x + w, y + h);
//	int tx, ty;
//	char text[] = "Button";
//	tx = x + (w - textwidth(text))/2;
//	ty = y + (h - textheight(text)) / 2;
//	outtextxy(tx, ty, text);
//}

//int main()              //基本图形与线条
//{
//	initgraph(640,480,EX_SHOWCONSOLE|EX_NOMINIMIZE);//定义大小和关闭性
//	setbkcolor(YELLOW);
//	cleardevice();                                  //要换背景必须写这个
//	setlinestyle(PS_SOLID,5);
//	setfillcolor(RED);
//	setlinecolor(GREEN);
//	circle(300, 300, 50);
//	fillcircle(50, 50, 50);
//	solidcircle(500, 50, 25);
//	settextcolor(RGB(175, 103, 184));               //可用qq截图找颜色
//	setbkmode(TRANSPARENT);                         //一般写字也要搞这个
//	settextstyle(40, 0, "微软雅黑");
//	outtextxy(50, 50, "YOU ARE A STUPID SHIT");
//	char arr[] = "YOU ARE A STUPID SHIT";
//	int a = textwidth(arr);
//	IMAGE img;
//	loadimage(&img, "./CTRL.jpg",40,50);   // 相对路径./表示当前文件夹  ../表示上级文件夹
//	putimage(0, 0, &img);
//
//	getchar();                                 //防止图像直接关闭
//	closegraph();                              //关闭图像
//	return 0;
//}

//以上为easyx基本内容

//void Print1()
//{
//	setbkmode(TRANSPARENT);
//	settextcolor(BLACK);
//	settextstyle(50, 0, "黑体");
//	outtextxy(60, 300, "鸡你太美!");
//}
//void Print2()
//{
//	setbkmode(TRANSPARENT);
//	settextcolor(RED);
//	settextstyle(30, 0, "黑体");
//	outtextxy(440, 40, "你干嘛，哎呦~");
//}
//void Bgm()
//{
//	mciSendString("open ./鸡.mp3 alias song", 0, 0, 0);
//	mciSendString("play song ", 0, 0, 0);
//}
//int main()
//{
//	initgraph(640, 480, EX_SHOWCONSOLE | EX_NOMINIMIZE);
//	IMAGE img;
//	loadimage(&img, "./CTRL.jpg", 640, 480);
//	putimage(0, 0, &img);
//	ExMessage msg;
//	while(1)
//	{
//		if (peekmessage(&msg, EX_MOUSE))
//		{
//			switch (msg.message)
//			{
//			case WM_LBUTTONDOWN:
//				if (msg.x > 77 && msg.x < 175 && msg.y>193 && msg.y < 259)
//				{
//					cleardevice();
//					mciSendString("close ./鸡.mp3", 0, 0, 0);
//					putimage(0, 0, &img);
//					Print1();
//					Bgm();
//				}
//				if (msg.x > 237 && msg.x < 332 && msg.y>25 && msg.y < 90)
//				{
//					mciSendString("close ./鸡.mp3", 0, 0, 0);
//					putimage(0, 0, &img);
//					Print2();
//					Bgm();
//				}
//			}
//		}
//	}
//
//
//	getchar();
//	closegraph();
//	return 0;
//}

//int main()
//{
//	int i, k, count, s;
//	char c, * b[20] = { 0 };
//	char* a[] = { (char*)"零",(char*)"壹",(char*)"贰",(char*)"叁",(char*)"肆",(char*)"伍",(char*)"陆",(char*)"柒",(char*)"捌",(char*)"玖" };
//	char* d[] = { (char*)"仟",(char*)"百",(char*)"拾",(char*)"万",(char*)"亿" };
//	//字符常量的值和地址是不变的  其地址不能赋给其他变量 但值可以
//	//最好强制类型转换掉
//	for (i = 1; (c = getchar()) != '\n'; i++)
//		b[i - 1] = a[c - 48];
//	k = --i;
//	count = 0;
//	s = 0;
//	if (k == 9)                      //分块输出
//		printf("%s亿", b[count++]);  //同样考虑函数的值传递
//	if (k >= 5)
//	{
//		for (i = count + 1; i <= k - count - 4; i++)
//		{
//			if (b[i - 1] == "零" && i != k - count - 4)
//			{
//				s++;
//				if (s == 1)
//					printf("零");
//			}
//			else if (b[i - 1] == "零" && i == k - count - 4)
//				continue;
//			else
//			{
//				printf("%s", b[i - 1]);
//				printf("%s", d[i - 1 - count]);
//				s = 0;
//			}
//		}
//		printf("万");
//		count = k - count - 4;
//		k -= count;
//	}
//	for (i = count + 1; i <= )
//}

//int main()              //龟兔赛跑  分阶段性判断求法
//{
//	int t=0, rab=0, tur=0,T;
//	scanf("%d", &T);
//	for (;t<T; )
//	{
//	
//		if (rab > tur)
//		{
//			tur += (T-t>30?30:T-t)*3;        //用这种简单的语句取极值
//			t += (T - t > 30 ? 30 : T - t);
//		}
//		else
//		{
//			tur += (T - t > 10 ? 10 : T - t)*3;
//			rab += (T - t > 10 ? 10 : T - t)*9;
//			t += (T - t > 10 ? 10 : T - t);
//		}
//	}
//	if (rab > tur)
//		printf("^_^ %d", rab);
//	else if (rab == tur)
//		printf("-_- %d", rab);
//	else
//		printf("@_@ %d", tur);
//	return 0;
//}

//#define num 4
//void Exc(int*, int*);
//void F(int*,int);
//int main()                           //全排列问题 递归
//{
//	int a[num] = { 0 },n,i;
//	printf("请输入一个不超过%d的正整数\n",9-num);
//	scanf("%d", &n);
//	for (i = 1; i <= num; i++)
//		a[i - 1] = n + i - 1;
//	F(a,num);
//	return 0;
//}
//void F(int* a,int n)
//{
//	int i;
//	if(n==1)
//	{
//		for (i = 1; i <= num; i++)
//			printf("%d", a[i - 1]);
//		printf("\n");
//	}
//	else
//	{
//		for (i =1; i<= n; i++)         //从两位数开始 逐个交换两数字的地位
//		{
//			Exc(&a[n - 1], &a[n - i]); //先交换次序输出
//				F(a, n-1);             //不能用自减 会改变当层递归的n值
//			Exc(&a[n - 1], &a[n - i]); //再换回来保持原位
//		}
//
//	}
//}
//void Exc(int* a, int* b)
//{
//	int k;
//	k = *a;
//	*a = *b;
//	*b = k;
//}  

//double F1(double,double);
//double F2(double,int);
//	double x;
//	int y;
//int main()            //二分法求开次方根
//{                     //注意每次区间端点判断  递归时每次判断右值即可
//	int i = 0, a = 0, left, right;
//	scanf("%lf%d", &x,&y);
//	if (x < 0 && (y % 2 == 1))
//	{
//		x = -x;
//		a = 1;
//	}
//	while (F2(i,y) < x)
//		i++;
//	left = i - 1;
//	right = i;
//	if (a==1)
//		printf("sqrt(x)=%lf", -F1(left, right));
//	else
//		printf("sqrt(x)=%lf", F1(left, right));
//	return 0;
//}
//double F1(double left,double right)   //递归函数每一个分支都有返回值
//{                                             //每一次返回值都返回到上一层递归
//	if (F2(right,y) == x)                    //检测右边界
//		return right;
//	double mid=(left+right)/2,a;
//	if (right - left < 1e-4)
//		return mid;
//	if (F2(mid,y) < x)
//		a=F1(mid, right);
//	else
//		a=F1(left, mid);
//	return a;
//}
//double F2(double x, int y)
//{
//	int i;
//	double a = 1;
//	if (y == 0)
//		return 1;
//	else if (x == 0)
//		return 0;
//	else
//	{
//		if (y < 0)
//			x = 1 / x;
//		y = (int)fabs(y);
//		for (i = 1; i <= y; i++)
//			a *= x;
//	}
//	return a;

//int main()          //注意所有的print都有函数传递机制
//{
//	int i = 1;
//	printf("%d %d %d %d",i++, ++i,i, i++);
//	//结果为 4 5 5 2
// 
// int a[]={1,2,3,4,5},*p=a;
// printf("%d  %d  %d  %d  ",*p++,*++p,(*p)++,++(*p));  //++优先级高于*
// //结果为 1 3 3 5
// //(1 2 5 4 5)
//	//从右往左看 后置直接传在变 前置先变 自己待定 i直接待定
//	//i=i+1 和前置逻辑类似
//	return 0;
//}

//行指针引用一次变成位指针（即某位数的地址） 再引用一次变成数
//区分多维数组与一维数组的首地址类型 前者要低一次（此时只有位指针）
//字符串常量的本质表示其实是一个地址

//递归调用从外往里 运行从里往外
//a>b>c  从左向右运算
//可用(T - t > 10 ? 10 : T - t)来替换取最值函数

//-6%5=-1  6%-5=1 -5%6=-5 5%-6=5 只由第一个数确定正负 然后正常运算
//左右两端必须是整型


//数组下标从0开始
//数组可相当于数列 f[i+2]=f[i+1]+f[i] 可以把每次变化的值存下来


//正数原码 补码 反码相等  负数原码取反加一为补码

//自动类型转换：赋值语句时 右边的总结果强变为左边类型  
//              计算混合类型表达式时 往高精度变 结果也是高精度的
//强制类型转换：(double)sum/count=3.147   (double)(sum/count)=3.000

//若i为三位数，则百位a=(int)i/100,十位b=(i-a*100)/10,个位c=i%10 可避免多重循环
//但若对每个位都有范围要求，则用多重循环更便于控制，且可直接把数字打在一起而不用计算总数
//用If放在for之前作判断可以减少循环次数

//用fabs(x)与1e-6的比较判断x是否为0
//控制正负交替：j *=-1 或 if语句 i%2==0 控制奇偶项

//continue 跳过未执行的循环体，直接进行表达式3运算
//break 跳出当前一重循环,不执行表达式三，执行循环的下一个语句，注意跳出多重循环时限定条件 不可跳出goto循环
//goto语句可直接跳出多重循环至被标注部分 但被标注语句参与正常运行 
//for循环中判别变量若外定义，可被保留并在外改变；若内定义则不行
//for语句的判别式可跟while语句一样
//do-while 最后要加分号
// return 是终止整个函数 跟continue break 有相似之处
// while(a=5) 是先赋值 再判断a的真假 一般是死循环

//用md形式控制所占的列数 -表示左顶格
//int a = 10;
//printf("%-3d%3d", a, 50);
//	double x = 20.402;
//printf("%10.2f\n", x);  //小数总体10位 保留小数2位
//scanf里面可以有中文
//输出字符串时%s a 不用方括号

//转义字符在字符串存储和打印时都要考虑
// 0——数字零 '0' 字符零 '\0'转义字符
//char arr[] =  "c:\\test\\32\\test.c";
//printf("%s", arr);
//getchar()可以用来消回车 按下回车时回车与数字、空格一起进入内存缓存区
//%c可以识别转义字符，如回车
//注意空语句的使用

//先变后用 用在当前逗号或分号
// 先用后变，变的值在下个分号或逗号
// ? : 运算参照逗号运算 在当前表达式改变或运用
//int a = 0, b = 0;
//a = (b=0,++b,b++);
//a = --a == b++ ? a++ : b++;
//printf("a=%d b=%d", a,b);

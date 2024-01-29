#define _CRT_SECURE_NO_WARNINGS 1  //备注与提示
#include<stdio.h>
#include<math.h>
#include<stdarg.h>           //变参函数
#include<complex.h>          //复数处理
#include<time.h>             //用于重置随机数种子 两次(double)clock的差值除以CLOCKS_PER_SEC得到运行用时
#include<string.h>           //memset(a,0,sizeof(a)) 将数组a赋初值 memmove()赋值任意数组和数据
#include<thread>             //多线程库
#include<stdlib.h>           //malloc函数  
#include <conio.h>           //_getch   （c=getchar())要加括号  _getche 一输入就马上读取 不用回车
#include<easyx.h>            //在项目 配置设置 高级 选择使用多字节 内置了windows.h 延时函数Sleep() 单位毫秒
#include<mmsystem.h>         //音乐播放  有些mp3格式是假的 无法播放 重复播放要close
#pragma comment(lib,"winmm.lib")   //静态库
//#define NDEBUG               //把assert函数无用化
#include<assert.h>           //assert()函数 用于检测某些条件为真的关键位置
#pragma warning(disable:6031)      //解除scanf警告
//using namespace std;         //用标准名 使thread 可用 但会导致结构体异常
//先想好再写 除变量名以外第二个及以后的单词首字母大写调用的时候小写 结构体名、宏定义全大写 不超过四个字母 

typedef struct node
{
	int data;
	node* next;
}NODE;
node* createNode(int data)
{
	NODE* node = (NODE*)malloc(sizeof(NODE));
	if (node == NULL)
		exit(EXIT_FAILURE);
	node->data = data;
	node->next = NULL;
	return node;
}
void insertByEnd(NODE* head, NODE* newNode)
{
	NODE* p = head;
	while (p->next)
		p = p->next;
	p->next = newNode;
}
void goThough(NODE* head)
{
	NODE* p = head->next;
	while (p)
	{
		printf("%d\n", p->data);
		p = p->next;
	}
}	
int main()
{
	NODE* head = createNode(NULL);
	int i;
	for (i = 1; i <= 5; i++)
	{
		NODE* newNode = createNode(i);
		insertByEnd(head, newNode);
	}
	goThough(head);
	return 0;
}

//#include"Tree.h"
//void showWords(ITEM* data)
//{
//	printf("%s\n", data->word);
//	return;
//}
//int main()  //用树
//{
//	FILE* p;
//	TREE tree;
//	ITEM temp = { {0} };
//	iniTree(&tree);
//	if ((p = fopen("text2.txt", "r")) == NULL)
//		exit(EXIT_FAILURE);
//	char c;
//	int i=1;
//	while ((c = fgetc(p)) != EOF&&!isFull(&tree))
//	{
//		if (c == '\n' || c == ',' || c == ' '||c=='.')  //遇到这些字符就跳过
//		{
//			if(*temp.word)
//			{
//				i = 1;
//				addNode(&tree, &temp);
//				memset(temp.word, 0, WORDMAX*sizeof(char));     //重置单词
//			}
//			continue;
//		}
//		temp.word[i++ - 1] = c;
//		if (i > WORDMAX)
//		{
//			printf("The word is too long:%s\n",temp.word);
//			exit(EXIT_FAILURE);
//		}
//	}
//	goThroughTree(&tree, showWords);
//	clearTree(&tree);
//	return 0;
//}

//int sum(int n, ...)  //省略号前面的是参数列表的参数个数
//{
//	va_list ap;      //ap是参数列表
//	va_start(ap, n); //启用参数列表 第二个是个数
//	va_list apcopy;
//	va_copy(apcopy, ap); //保存参数副本
//	int i,sum=0;
//	for(i=1;i<=n;i++)
//		sum += va_arg(ap, int); //从参数列表中取值 第二个是返回值类型 注意这里必须与穿进来的参数一样
//	va_end(ap);      //注销参数列表  有start就有end
//	va_end(apcopy);
//	return sum;
//}
//int main() //变参含数
//{
//	printf("sum=%d\n", sum(3, 1, 45, 9));
//	return 0;
//}

//#define length 100
//int count = 1,num;
//void Split(int** a,int n,int k,int*temp,int end) //存结果的数组 当前操作数 当前数组操作位置 暂存结果的数组 终止数
//{
//	int i;
//	if (n == end)    //递归结束
//	{
//		//int s = 1;
//		if (count > length)
//			exit(-1);
//		temp[k - 1] =end ;
//		for (i = 1; i <= k; i++)
//			a[count - 1][i - 1] = temp[i - 1];    //将结果传回去
//		count++;
//		return;
//	}
//	else
//	{
//		for(i=1;i<=n-1;i++)                //3 去1拆2 去2拆1  
//		{
//			temp[k - 1] = i;         //存储去掉的那个数
//			Split(a,n - i,k+1,temp,end);            //将剩下的那个数放进来继续拆
//		}
//	}
//	return;
//}
//void Sort(int* a)
//{
//	int i,j,temp;
//	for (i = 1; i <= num; i++)        ///冒泡排序并把0放在最后面
//	{
//		for (j = i; j <= num; j++)
//		{
//			if (a[i - 1] > a[j - 1]&&a[j-1]!=0)
//			{
//				temp = a[i - 1];
//				a[i - 1] = a[j - 1];
//				a[j - 1] = temp;
//			}
//		}
//	}
//}
//int Check(int* a, int* b)    //用于检测两个数组是否相同 若相同返回0
//{
//	int i = 1,count=0;
//	while (*a && *b && i <= num&&*a==*b)
//	{
//		a++;
//		b++;
//		i++;
//	}
//	if (i == num + 1)
//		return 0;
//	else 
//		return *a - *b;
//}
//void Memset0(int* a, int n)       //数组置零
//{
//	int i;
//	for (i = 1; i <= n; i++)
//		a[i - 1] = 0;
//}
//void Exc(int* a, int* b)          //数组交换
//{
//	int temp, i;
//	for (i = 1; i <= num; i++)
//	{
//		temp = a[i - 1];
//		a[i - 1] = b[i - 1];
//		b[i - 1] = temp;
//	}
//}
//int main()
//{
//	int* a[length],i,j,s,*temp;        //创建并检验二维数组a[1000][num]
//	scanf("%d", &num);
//	if (num <= 0)
//		exit(-1);
//	temp = (int*)malloc(num * sizeof(int));
//	if (temp == NULL)
//		exit(-1);
//	for(i=1;i<=length;i++)
//	{
//		a[i-1] = (int*)malloc(num * sizeof(int));
//		if (a[i-1] == NULL)
//			exit(-1);
//		Memset0(a[i - 1], num);
//	}
//	for(i=1;i<=num/2;i++)
//		Split (a, num, 1,temp,i);             //重复拆分并存储
//	for (i = 1; i <= count - 1; i++)    //排序
//		Sort(a[i - 1]);
//	for (i = 1; i <= count - 1; i++)        //冒泡把重复的置零
//	{
//		if (a[i - 1][0] == 0)
//			continue;
//		for (j = i+1; j <= count - 1; j++)
//		{
//			if (a[j - 1][0] == 0)
//				continue;
//			if (Check(a[i - 1], a[j - 1]) == 0)
//				Memset0(a[j - 1], num);
//		}
//	}
//	for (i = 1; i <= count - 1; i++)        //冒泡排序
//	{
//		if (a[i - 1][0] == 0)
//			continue;
//		for (j = i + 1; j <= count - 1; j++)
//		{
//			if (a[j - 1][0] == 0)
//				continue;
//			if (Check(a[i - 1], a[j - 1]) > 0)
//				Exc(a[i - 1], a[j - 1]);
//		}
//	}
//	for (i = 1,temp[0]=0; i <= count - 1; i++)        //输出
//	{
//		if (a[i - 1][0] == 0)
//			continue;
//		for (j = 1,s=0; j <= num; j++)
//		{
//			if (a[i - 1][j - 1] == 0)
//				continue;
//			if (s++ == 0)
//				printf("%d=%d", num, a[i - 1][j - 1]);
//			else
//				printf("+%d", a[i - 1][j - 1]);
//		}
//		temp[0]++;
//		if (temp[0] % 4 == 0)
//			printf("\n");
//		else
//			printf(";");
//	}
//	printf("%d=%d", num, num);       //补上最后一个
//	for (i = 1; i <= length; i++)       //a不是可变数组 不能释放a
//		free(a[i - 1]);
//	free(temp);
//	return 0;
//} 

//int main()
//{
//	FILE* pf; //文件操作 FILE *pf=fopen("","r") 文件末尾自带EDF  
//	int i = 1, count = 0, check[3] = {0};
//	char const imput[50] = "This is a file\nIt\'s the next line\n";
//	char b[10] = { 0 };
//	unsigned char output[50];    //要这样才能匹配void*
//	if ((pf = fopen("text1.txt", "a+")) == NULL) // 要检测是否为空指针或成功操作 此处要表明对这个文本所作的操作
//		exit(-1); 
//	//注意用w的时候没有文件就会创建一个文件 而其他操作必须要先有文件 对已有文件再写入时会清空！！！
//	//t是文本 b是二进制文件
//	//数据块读写函数 也是二进制型fread 和fwrite 都返回读入或写入的项数 若小于所给的项代表到文件末尾或出错 
//	fwrite(imput, 1, strlen(imput), pf);             //文件写入后要再关闭然后读取！！
//	fclose(pf);
//	pf = fopen("text.txt", "r");
//	while (count = (int)fread(output, 1, 8, pf))          //只有这样写入的东西才能从缓存区流入文件
//	{
//		for (i = 1; i <= count; i++)
//			printf("%c", output[i - 1]);
//		if (count < 8)
//			break;
//	}
//	//格式化输入函数
//	fprintf(pf, "%+d%+d\n", i, b[0]);
//	fscanf(pf, "%[^0-9]", b);
//	printf("%s", b);
//	//字符和字符串读写函数
//  fgets(存的数组，读取的字符串长度，文件指针)遇到换行和结束会停止 //buffer 是用来存结果的
//	//在文件内部也有个隐藏的指针 用于指向读写的位置 改变这个指针位置的函数为 rewind和fseek 
//  //这两种方法对于二进制文本好用
//	rewind(pf);  //将指针移到文件起始位
//	fseek(pf, 100L, 0);  //位移量单位是字节要加后缀L 文件首是0 当前位置是1 文件尾是2 
//  ftell();  //返回当前位置到开始处的距离(long)
//	//文件检测函数
//	check[0]=feof(pf);          //用于检测是否在文件结束位置 不是返回零
//	check[1]=ferror(pf);        //检测在各种读写时有没有出错 如果有返回非0值
//	clearerr(pf);      //将上述两个函数归0? 
//	fclose(pf); //用完要关掉文件
//	return 0;
//}

//easyx内容从此开始

//void Change()
//{   
//	HWND hnd = GetHWnd(); //获取窗口句柄   这是设的640 480的窗口句柄
//	SetWindowText(hnd, "油饼食不食");    //更改窗口名
//  InputBox(a,"s","b");                  //用于有输入值的弹窗
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
//	mciSendString("play song ", 0, 0, 0);                     //有些文件不是真mp3
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
//		setbkcolor(YELLOW);  //也可用flushbatchdraw
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
//  clearrectangular();                             //清除指定位置图案
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
//

//easyx到此结束

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

//int main()
//{
//	srand((unsigned)time(NULL));
//	int a[20] = { 0 },i,j,num=0;            //冒泡排序法
//	for (i = 1; i <= 20; i++)
//		a[i - 1] = rand() % 100;
//	for (i = 1; i <= 10; i++)      //改变i的终止量可以控制已经排好几个
//	{
//		for (j = i; j <= 20; j++)  //注意j的初始化为i 终止量与数组长度相同
//		{
//			if (a[i - 1] > a[j - 1]) //此时为从小到大排序 已经排好的在左边
//			{
//				num = a[j - 1];
//				a[j - 1] = a[i - 1];
//				a[i - 1] = num;
//			}
//		}
//	}
//	for (i = 1; i <= 20; i++)
//		printf("%d  ", a[i - 1]);
//	return 0;
//}

// 对于矩形外框 还是每边独立循环好 每次是类似的变换  
//	for (j = 1,k=n; j <= count; j++,k-=2)     j是圈数 k是每边的循环次数 n是总行数不变
//	{
//		for (i = 1; i <= k - 1; i++)           圈层问题
//			a[j - 1][j - 1 + i - 1] = j;
//		for (i = 1; i <= k - 1; i++)
//			a[j - 1 + i - 1][n - 1 - j + 1] = j;
//		for (i = 1; i <= k - 1; i++)
//			a[n - 1 - j + 1][n - i - j + 1] = j;
//		for (i = 1; i <= k - 1; i++)
//			a[n - i - j + 1][j - 1] = j;
//	}

//int main()          //注意所有的print都有函数传递机制
//{
//	int i = 1;
//	printf("%d %d %d %d\n",i++, ++i,i, i++);   //结果为 3 4 4 1
//	int a[]={1,2,3,4,5},*p=a;
//	printf("%d  %d  %d  %d  ",*p++,*++p,(*p)++,++(*p));  //++优先级高于*
//	//结果为 1 3 3 5
//	//(1 2 5 4 5)
//	//从右往左看 后置直接传在变 前置先变 自己待定 i直接待定
//	//i=i+1 和前置逻辑类似
//	return 0;
//}

//#define 定义宏 相当于在预编译的时候直接字符替换 也可以定义类函数宏 
//可以用#ifndef LIST_H #define LIST_H #endif 这个空宏来防止被重复包含
//注意预处理器不作计算 只替换字符！所以与函数参数不完全一致  有可能运算顺序被改变 不要用自增自减 记得括号
//可用“#x”来作为替换记号 预处理后才处理串联字符串
//一个#只能替换一个变量 #define MAX(x,y) printf(""#x","#y" is %d\n",x>y?x:y)
//##是记号粘合器 #define STICK(n) x##n 所以STICK(1)就是x1
//参数可变的宏#define PR(...) printf(__VA_ARGS__)
//头文件中放声明（即原型）和宏 一个源文件放定义 一个源文件放主函数
//#ifdef   用于判断某个宏是否被定义 #ifndef相反 用于避免重复包含  #else  #endif 
//#if  #elif  #endif 相当于代码里的if使用 用于处理预编译指令
//预定义宏 __FILE__文件名 __DATE__日期 __TIME__ 时间__LINE__ 当前行数__fun__当前函数名
//atexit()函数可以注册一个函数 这些被注册的函数将在exit的时候倒序调用 整个程序默认隐式exit
//快速排序qsort(void* base,size_t nnumb,size_t size,int (*compar)(const void*,const void*))
//比较函数自己写 来调控升序和降序 注意强制类型转换
//assert()函数 用于检测某些条件为真的关键位置 要assert.h头文件 可用#define NDEBUG将其无用化

//常用布尔型进行判断
// int argc字符串个数  char*argv[]字符串地址  默认把文件名作为第一个字符串 要先运行一下代码才能保存
//输入类型有无缓存和有缓存 完全缓存（文件）和行缓存 控制台输入可视为文件输入 ctrl z 是文本结束
//可通过重定向改变输入流从键盘输入到文件输入 达到类文件操作的结果
// int ungetc(int c,FILE *p)  把一个字符重新放入输入流可用于实现读取输入的每个字符串
// stdout stdin stderr 是标准输出 输入 错误流
// int fflush(FILE *p) 刷新输出缓存区 setvbuf()创建一个缓存区(具体用途还需搜索)
// scanf会把读取失败的字符和回车放回输入缓存区 返回值为成功读取项的个数 不是字符个数！！
// 每次使用scanf时 若输入流无信息 则会等待缓存区输入 getchar（）也是
// 可用strtol（读取的字符串，存放非数字字符的一级指针的地址，进制）来转换，比atoi更好用
// strstr用于找到字串 返回一个指向第二个字符串在第一个字符串出现的位置的指针 strchr差不多
//位段的成员最好全是int 或全是char int a:2;指该变量站两个比特位 定义和用法与结构体一样
//创建链表 ：1.创建节点（无数据）2.节点插入方式 3.节点赋值 4.将这三个功能连起来 LIST{NODE* head;NODE*end}
//可用printf调试代码

//运算符优先级从高到低 () [] -> . ++ * 
//结构体自引用时注意typedef的使用会产生影响
//结构体地址对齐（该成员的对齐量为该成员的字节大小与默认大小的较小值 VS默认大小为8） 
//第一个成员在偏移量为0处 此后的成员须从自己对齐量的整数倍位置开始存放
//结构体总大小为所有成员对齐量的较大值的整数倍 若嵌套结构体 则该结构体成员的对齐量为它内部的最大对齐量
//用#pragma pack(4) 修改默认对齐数 括号里面不放东西就是还原
//结构体传参最好传地址 怕被改变就加const
//结构体里可以有伸缩性数组pf=(FILE*)malloc(sizeof(FILE)+n*sizeof(int))

//sizeof 是一种运算 如++ 而不是函数  用于获取字节大小
//sizeof(a) 当a是可变数组时 无法获取数组a的整个大小 要用n*sizeof(int)
//当括号内有数组类型时 获得整个数组的字节大小（此时与数组的类型也有关）
//当括号内为结构体时 获取整个结构体字节大小（与地址对齐有关） 为联合体时 获取其中字节最大的部分

//多线程的使用 包含thread 并且using namespace std 创建 thread text1(max); text1.join;
//线程不用会报错 一个线程只能join一次 该处所有子线程执行完在执行主线程 会卡住主线程
//detach将子线程和主线程分离运行 把子线程驻留后台 此后不能再join了
//joinable()判断是否可以join或detach 可以为true 不可以为false
// 传参直接在函数创造线程的线程名右边传递 传地址要ref(num)
//return 可以把某个函数的线程结束

//scanf的高级用法 一 指定长度 scanf("%10d",&a) 
// 二 匹配特定的字符 scanf("%[a-zA-Z]",&a) 不匹配某些特点字符 scanf("%[^\n]",&a) 即除换行符以外
// 三 丢弃某些字符 scanf("%*d") scanf("%*[a-z]") scanf("%*[^\n]") scanf("%*c") 即清空缓存区
//sprintf(str,"a=%d",a); 即可将printf的结果存在str里面

//malloc函数要检测输入的行或列数是否为正
//用其构成的二维数组可以传递二级指针而不用数组指针
//不是可变数组的不要去释放内存！！！

//行指针引用一次变成位指针（即某位数的地址） 再引用一次变成数
//区分多维数组与一维数组的首地址类型 前者要低一次（此时只有位指针）
// strcpy(s,s+1)可以实现对字符串的删减 尝试用指针移位进行for循环和指针函数
//字符串的表示类型相似于字符指针  sizeof(str)表示其开辟空间大小  将其首地址加n 可对后面的部分表示
//字符指针和字符数组存字符串的区别是 前者先开辟字符串，然后把其首地址的值给到指针 
//        搞清楚哪些是不变的         后者先开辟变量 再对变量赋值

//递归调用从外往里 运行从里往外 void 函数结束递归用return就行 写递归从简单例子开始剖析 抓住主要规律
//a>b>c  从左向右运算
//可用(T - t > 10 ? 10 : T - t)来替换取最值函数

//-6%5=-1  6%-5=1 -5%6=-5 5%-6=5 只由第一个数确定正负 然后正常运算
//左右两端必须是整型

//正数原码 补码 反码相等  负数原码取反加一为补码

//自动类型转换：赋值语句时 右边的总结果强变为左边类型  
//              计算混合类型表达式时 往高精度变 结果也是高精度的
//强制类型转换：(double)sum/count=3.147   (double)(sum/count)=3.000

//用md形式控制所占的列数 -表示左顶格  %+d  表示输出的值带符号 % d输出的正数带空格 负数带负号
//int a = 10;
//printf("%-3d%3d", a, 50);
//	double x = 20.402;
//printf("%10.2f\n", x);  //数总体10位 保留小数2位 %24.5s 是只打印5个字符 共24格

//先变后用 用在当前逗号或分号
// 先用后变，变的值在下个分号或逗号
// ? : 运算参照逗号运算 在当前表达式改变或运用
//int a = 0, b = 0;
//a = (b=0,++b,b++);
//a = --a == b++ ? a++ : b++;
//printf("a=%d b=%d", a,b);
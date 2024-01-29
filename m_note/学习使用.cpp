#define _CRT_SECURE_NO_WARNINGS 1  //��ע����ʾ
#include<stdio.h>
#include<math.h>
#include<stdarg.h>           //��κ���
#include<complex.h>          //��������
#include<time.h>             //����������������� ����(double)clock�Ĳ�ֵ����CLOCKS_PER_SEC�õ�������ʱ
#include<string.h>           //memset(a,0,sizeof(a)) ������a����ֵ memmove()��ֵ�������������
#include<thread>             //���߳̿�
#include<stdlib.h>           //malloc����  
#include <conio.h>           //_getch   ��c=getchar())Ҫ������  _getche һ��������϶�ȡ ���ûس�
#include<easyx.h>            //����Ŀ �������� �߼� ѡ��ʹ�ö��ֽ� ������windows.h ��ʱ����Sleep() ��λ����
#include<mmsystem.h>         //���ֲ���  ��Щmp3��ʽ�Ǽٵ� �޷����� �ظ�����Ҫclose
#pragma comment(lib,"winmm.lib")   //��̬��
//#define NDEBUG               //��assert�������û�
#include<assert.h>           //assert()���� ���ڼ��ĳЩ����Ϊ��Ĺؼ�λ��
#pragma warning(disable:6031)      //���scanf����
//using namespace std;         //�ñ�׼�� ʹthread ���� ���ᵼ�½ṹ���쳣
//�������д ������������ڶ������Ժ�ĵ�������ĸ��д���õ�ʱ��Сд �ṹ�������궨��ȫ��д �������ĸ���ĸ 

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
//int main()  //����
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
//		if (c == '\n' || c == ',' || c == ' '||c=='.')  //������Щ�ַ�������
//		{
//			if(*temp.word)
//			{
//				i = 1;
//				addNode(&tree, &temp);
//				memset(temp.word, 0, WORDMAX*sizeof(char));     //���õ���
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

//int sum(int n, ...)  //ʡ�Ժ�ǰ����ǲ����б�Ĳ�������
//{
//	va_list ap;      //ap�ǲ����б�
//	va_start(ap, n); //���ò����б� �ڶ����Ǹ���
//	va_list apcopy;
//	va_copy(apcopy, ap); //�����������
//	int i,sum=0;
//	for(i=1;i<=n;i++)
//		sum += va_arg(ap, int); //�Ӳ����б���ȡֵ �ڶ����Ƿ���ֵ���� ע����������봩�����Ĳ���һ��
//	va_end(ap);      //ע�������б�  ��start����end
//	va_end(apcopy);
//	return sum;
//}
//int main() //��κ���
//{
//	printf("sum=%d\n", sum(3, 1, 45, 9));
//	return 0;
//}

//#define length 100
//int count = 1,num;
//void Split(int** a,int n,int k,int*temp,int end) //���������� ��ǰ������ ��ǰ�������λ�� �ݴ��������� ��ֹ��
//{
//	int i;
//	if (n == end)    //�ݹ����
//	{
//		//int s = 1;
//		if (count > length)
//			exit(-1);
//		temp[k - 1] =end ;
//		for (i = 1; i <= k; i++)
//			a[count - 1][i - 1] = temp[i - 1];    //���������ȥ
//		count++;
//		return;
//	}
//	else
//	{
//		for(i=1;i<=n-1;i++)                //3 ȥ1��2 ȥ2��1  
//		{
//			temp[k - 1] = i;         //�洢ȥ�����Ǹ���
//			Split(a,n - i,k+1,temp,end);            //��ʣ�µ��Ǹ����Ž���������
//		}
//	}
//	return;
//}
//void Sort(int* a)
//{
//	int i,j,temp;
//	for (i = 1; i <= num; i++)        ///ð�����򲢰�0���������
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
//int Check(int* a, int* b)    //���ڼ�����������Ƿ���ͬ ����ͬ����0
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
//void Memset0(int* a, int n)       //��������
//{
//	int i;
//	for (i = 1; i <= n; i++)
//		a[i - 1] = 0;
//}
//void Exc(int* a, int* b)          //���齻��
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
//	int* a[length],i,j,s,*temp;        //�����������ά����a[1000][num]
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
//		Split (a, num, 1,temp,i);             //�ظ���ֲ��洢
//	for (i = 1; i <= count - 1; i++)    //����
//		Sort(a[i - 1]);
//	for (i = 1; i <= count - 1; i++)        //ð�ݰ��ظ�������
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
//	for (i = 1; i <= count - 1; i++)        //ð������
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
//	for (i = 1,temp[0]=0; i <= count - 1; i++)        //���
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
//	printf("%d=%d", num, num);       //�������һ��
//	for (i = 1; i <= length; i++)       //a���ǿɱ����� �����ͷ�a
//		free(a[i - 1]);
//	free(temp);
//	return 0;
//} 

//int main()
//{
//	FILE* pf; //�ļ����� FILE *pf=fopen("","r") �ļ�ĩβ�Դ�EDF  
//	int i = 1, count = 0, check[3] = {0};
//	char const imput[50] = "This is a file\nIt\'s the next line\n";
//	char b[10] = { 0 };
//	unsigned char output[50];    //Ҫ��������ƥ��void*
//	if ((pf = fopen("text1.txt", "a+")) == NULL) // Ҫ����Ƿ�Ϊ��ָ���ɹ����� �˴�Ҫ����������ı������Ĳ���
//		exit(-1); 
//	//ע����w��ʱ��û���ļ��ͻᴴ��һ���ļ� ��������������Ҫ�����ļ� �������ļ���д��ʱ����գ�����
//	//t���ı� b�Ƕ������ļ�
//	//���ݿ��д���� Ҳ�Ƕ�������fread ��fwrite �����ض����д������� ��С��������������ļ�ĩβ����� 
//	fwrite(imput, 1, strlen(imput), pf);             //�ļ�д���Ҫ�ٹر�Ȼ���ȡ����
//	fclose(pf);
//	pf = fopen("text.txt", "r");
//	while (count = (int)fread(output, 1, 8, pf))          //ֻ������д��Ķ������ܴӻ����������ļ�
//	{
//		for (i = 1; i <= count; i++)
//			printf("%c", output[i - 1]);
//		if (count < 8)
//			break;
//	}
//	//��ʽ�����뺯��
//	fprintf(pf, "%+d%+d\n", i, b[0]);
//	fscanf(pf, "%[^0-9]", b);
//	printf("%s", b);
//	//�ַ����ַ�����д����
//  fgets(������飬��ȡ���ַ������ȣ��ļ�ָ��)�������кͽ�����ֹͣ //buffer ������������
//	//���ļ��ڲ�Ҳ�и����ص�ָ�� ����ָ���д��λ�� �ı����ָ��λ�õĺ���Ϊ rewind��fseek 
//  //�����ַ������ڶ������ı�����
//	rewind(pf);  //��ָ���Ƶ��ļ���ʼλ
//	fseek(pf, 100L, 0);  //λ������λ���ֽ�Ҫ�Ӻ�׺L �ļ�����0 ��ǰλ����1 �ļ�β��2 
//  ftell();  //���ص�ǰλ�õ���ʼ���ľ���(long)
//	//�ļ���⺯��
//	check[0]=feof(pf);          //���ڼ���Ƿ����ļ�����λ�� ���Ƿ�����
//	check[1]=ferror(pf);        //����ڸ��ֶ�дʱ��û�г��� ����з��ط�0ֵ
//	clearerr(pf);      //����������������0? 
//	fclose(pf); //����Ҫ�ص��ļ�
//	return 0;
//}

//easyx���ݴӴ˿�ʼ

//void Change()
//{   
//	HWND hnd = GetHWnd(); //��ȡ���ھ��   �������640 480�Ĵ��ھ��
//	SetWindowText(hnd, "�ͱ�ʳ��ʳ");    //���Ĵ�����
//  InputBox(a,"s","b");                  //����������ֵ�ĵ���
//	int isok=MessageBox(hnd, "���ǲ�����ikun��", "������", MB_YESNO);  //���з���ֵ��
//	if (isok == IDYES)
//	{
//		printf("�����Ǻڵ�");
//	}
//	else if (isok == IDNO)
//		printf("�ط��ǰ׵�");
//}
//void Bgm()
//{
//	mciSendString("open ./��.mp3 alias song", 0, 0, 0);       //�ļ���չ����Ҫ���أ�����
//	mciSendString("play song ", 0, 0, 0);                     //��Щ�ļ�������mp3
//	//wait �ȴ����ַ����ٽ��н������Ĵ���
//	//repeat �ظ�����
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
//		BeginBatchDraw();   //��ֹ��ͼ ���ڻ�ͼ�����ǰ��ͺ��� ��ͼƬ���л��洦�� ���ӳ�?
//		setbkcolor(YELLOW);  //Ҳ����flushbatchdraw
//		cleardevice();
//		putimage(0, 0, &img);
//		fillcircle(x, y, 10);
//		//if(_kbhit())               //��ֹ����      �ӳ�ͻȻû�� ��������й�
//		//{
//		//	char key = _getch();      //������������ һֱ��
//		//	switch (key)              //Ҫ�жϳ�ÿ����������ֵ�ź���
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
//		if (GetAsyncKeyState(VK_UP))      //����˿��  ����б���� ��̫����
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
//	setbkmode(TRANSPARENT);        //���������֧�����ж��岻һ��
//	settextstyle(50, 0, "����");
//	ExMessage msg;                 //����һ����Ϣ�ṹ��
//	while(1)
//	{
//		if (peekmessage(&msg, EX_MOUSE))   //�ж������Ϣ
//		{                                  //��ͣҲ���������Ϣ
//			switch (msg.message)           //�ж����λ��
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
//	settextstyle(50, 0, "����");
//	fillrectangle(x, y, x + w, y + h);
//	int tx, ty;
//	char text[] = "Button";
//	tx = x + (w - textwidth(text))/2;
//	ty = y + (h - textheight(text)) / 2;
//	outtextxy(tx, ty, text);
//}

//int main()              //����ͼ��������
//{
//	initgraph(640,480,EX_SHOWCONSOLE|EX_NOMINIMIZE);//�����С�͹ر���
//	setbkcolor(YELLOW);
//	cleardevice();                                  //Ҫ����������д���
//  clearrectangular();                             //���ָ��λ��ͼ��
//	setlinestyle(PS_SOLID,5);
//	setfillcolor(RED);
//	setlinecolor(GREEN);
//	circle(300, 300, 50);
//	fillcircle(50, 50, 50);
//	solidcircle(500, 50, 25);
//	settextcolor(RGB(175, 103, 184));               //����qq��ͼ����ɫ
//	setbkmode(TRANSPARENT);                         //һ��д��ҲҪ�����
//	settextstyle(40, 0, "΢���ź�");
//	outtextxy(50, 50, "YOU ARE A STUPID SHIT");
//	char arr[] = "YOU ARE A STUPID SHIT";
//	int a = textwidth(arr);
//	IMAGE img;
//	loadimage(&img, "./CTRL.jpg",40,50);   // ���·��./��ʾ��ǰ�ļ���  ../��ʾ�ϼ��ļ���
//	putimage(0, 0, &img);
//
//	getchar();                                 //��ֹͼ��ֱ�ӹر�
//	closegraph();                              //�ر�ͼ��
//	return 0;
//}

//void Print1()
//{
//	setbkmode(TRANSPARENT);
//	settextcolor(BLACK);
//	settextstyle(50, 0, "����");
//	outtextxy(60, 300, "����̫��!");
//}
//void Print2()
//{
//	setbkmode(TRANSPARENT);
//	settextcolor(RED);
//	settextstyle(30, 0, "����");
//	outtextxy(440, 40, "��������~");
//}
//void Bgm()
//{
//	mciSendString("open ./��.mp3 alias song", 0, 0, 0);
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
//					mciSendString("close ./��.mp3", 0, 0, 0);
//					putimage(0, 0, &img);
//					Print1();
//					Bgm();
//				}
//				if (msg.x > 237 && msg.x < 332 && msg.y>25 && msg.y < 90)
//				{
//					mciSendString("close ./��.mp3", 0, 0, 0);
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

//easyx���˽���

//#define num 4
//void Exc(int*, int*);
//void F(int*,int);
//int main()                           //ȫ�������� �ݹ�
//{
//	int a[num] = { 0 },n,i;
//	printf("������һ��������%d��������\n",9-num);
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
//		for (i =1; i<= n; i++)         //����λ����ʼ ������������ֵĵ�λ
//		{
//			Exc(&a[n - 1], &a[n - i]); //�Ƚ����������
//				F(a, n-1);             //�������Լ� ��ı䵱��ݹ��nֵ
//			Exc(&a[n - 1], &a[n - i]); //�ٻ���������ԭλ
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
//	int a[20] = { 0 },i,j,num=0;            //ð������
//	for (i = 1; i <= 20; i++)
//		a[i - 1] = rand() % 100;
//	for (i = 1; i <= 10; i++)      //�ı�i����ֹ�����Կ����Ѿ��źü���
//	{
//		for (j = i; j <= 20; j++)  //ע��j�ĳ�ʼ��Ϊi ��ֹ�������鳤����ͬ
//		{
//			if (a[i - 1] > a[j - 1]) //��ʱΪ��С�������� �Ѿ��źõ������
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

// ���ھ������ ����ÿ�߶���ѭ���� ÿ�������Ƶı任  
//	for (j = 1,k=n; j <= count; j++,k-=2)     j��Ȧ�� k��ÿ�ߵ�ѭ������ n������������
//	{
//		for (i = 1; i <= k - 1; i++)           Ȧ������
//			a[j - 1][j - 1 + i - 1] = j;
//		for (i = 1; i <= k - 1; i++)
//			a[j - 1 + i - 1][n - 1 - j + 1] = j;
//		for (i = 1; i <= k - 1; i++)
//			a[n - 1 - j + 1][n - i - j + 1] = j;
//		for (i = 1; i <= k - 1; i++)
//			a[n - i - j + 1][j - 1] = j;
//	}

//int main()          //ע�����е�print���к������ݻ���
//{
//	int i = 1;
//	printf("%d %d %d %d\n",i++, ++i,i, i++);   //���Ϊ 3 4 4 1
//	int a[]={1,2,3,4,5},*p=a;
//	printf("%d  %d  %d  %d  ",*p++,*++p,(*p)++,++(*p));  //++���ȼ�����*
//	//���Ϊ 1 3 3 5
//	//(1 2 5 4 5)
//	//�������� ����ֱ�Ӵ��ڱ� ǰ���ȱ� �Լ����� iֱ�Ӵ���
//	//i=i+1 ��ǰ���߼�����
//	return 0;
//}

//#define ����� �൱����Ԥ�����ʱ��ֱ���ַ��滻 Ҳ���Զ����ຯ���� 
//������#ifndef LIST_H #define LIST_H #endif ����պ�����ֹ���ظ�����
//ע��Ԥ�������������� ֻ�滻�ַ��������뺯����������ȫһ��  �п�������˳�򱻸ı� ��Ҫ�������Լ� �ǵ�����
//���á�#x������Ϊ�滻�Ǻ� Ԥ�����Ŵ������ַ���
//һ��#ֻ���滻һ������ #define MAX(x,y) printf(""#x","#y" is %d\n",x>y?x:y)
//##�ǼǺ�ճ���� #define STICK(n) x##n ����STICK(1)����x1
//�����ɱ�ĺ�#define PR(...) printf(__VA_ARGS__)
//ͷ�ļ��з���������ԭ�ͣ��ͺ� һ��Դ�ļ��Ŷ��� һ��Դ�ļ���������
//#ifdef   �����ж�ĳ�����Ƿ񱻶��� #ifndef�෴ ���ڱ����ظ�����  #else  #endif 
//#if  #elif  #endif �൱�ڴ������ifʹ�� ���ڴ���Ԥ����ָ��
//Ԥ����� __FILE__�ļ��� __DATE__���� __TIME__ ʱ��__LINE__ ��ǰ����__fun__��ǰ������
//atexit()��������ע��һ������ ��Щ��ע��ĺ�������exit��ʱ������� ��������Ĭ����ʽexit
//��������qsort(void* base,size_t nnumb,size_t size,int (*compar)(const void*,const void*))
//�ȽϺ����Լ�д ����������ͽ��� ע��ǿ������ת��
//assert()���� ���ڼ��ĳЩ����Ϊ��Ĺؼ�λ�� Ҫassert.hͷ�ļ� ����#define NDEBUG�������û�

//���ò����ͽ����ж�
// int argc�ַ�������  char*argv[]�ַ�����ַ  Ĭ�ϰ��ļ�����Ϊ��һ���ַ��� Ҫ������һ�´�����ܱ���
//�����������޻�����л��� ��ȫ���棨�ļ������л��� ����̨�������Ϊ�ļ����� ctrl z ���ı�����
//��ͨ���ض���ı��������Ӽ������뵽�ļ����� �ﵽ���ļ������Ľ��
// int ungetc(int c,FILE *p)  ��һ���ַ����·���������������ʵ�ֶ�ȡ�����ÿ���ַ���
// stdout stdin stderr �Ǳ�׼��� ���� ������
// int fflush(FILE *p) ˢ����������� setvbuf()����һ��������(������;��������)
// scanf��Ѷ�ȡʧ�ܵ��ַ��ͻس��Ż����뻺���� ����ֵΪ�ɹ���ȡ��ĸ��� �����ַ���������
// ÿ��ʹ��scanfʱ ������������Ϣ ���ȴ����������� getchar����Ҳ��
// ����strtol����ȡ���ַ�������ŷ������ַ���һ��ָ��ĵ�ַ�����ƣ���ת������atoi������
// strstr�����ҵ��ִ� ����һ��ָ��ڶ����ַ����ڵ�һ���ַ������ֵ�λ�õ�ָ�� strchr���
//λ�εĳ�Ա���ȫ��int ��ȫ��char int a:2;ָ�ñ���վ��������λ ������÷���ṹ��һ��
//�������� ��1.�����ڵ㣨�����ݣ�2.�ڵ���뷽ʽ 3.�ڵ㸳ֵ 4.������������������ LIST{NODE* head;NODE*end}
//����printf���Դ���

//��������ȼ��Ӹߵ��� () [] -> . ++ * 
//�ṹ��������ʱע��typedef��ʹ�û����Ӱ��
//�ṹ���ַ���루�ó�Ա�Ķ�����Ϊ�ó�Ա���ֽڴ�С��Ĭ�ϴ�С�Ľ�Сֵ VSĬ�ϴ�СΪ8�� 
//��һ����Ա��ƫ����Ϊ0�� �˺�ĳ�Ա����Լ���������������λ�ÿ�ʼ���
//�ṹ���ܴ�СΪ���г�Ա�������Ľϴ�ֵ�������� ��Ƕ�׽ṹ�� ��ýṹ���Ա�Ķ�����Ϊ���ڲ�����������
//��#pragma pack(4) �޸�Ĭ�϶����� �������治�Ŷ������ǻ�ԭ
//�ṹ�崫����ô���ַ �±��ı�ͼ�const
//�ṹ�������������������pf=(FILE*)malloc(sizeof(FILE)+n*sizeof(int))

//sizeof ��һ������ ��++ �����Ǻ���  ���ڻ�ȡ�ֽڴ�С
//sizeof(a) ��a�ǿɱ�����ʱ �޷���ȡ����a��������С Ҫ��n*sizeof(int)
//������������������ʱ �������������ֽڴ�С����ʱ�����������Ҳ�йأ�
//��������Ϊ�ṹ��ʱ ��ȡ�����ṹ���ֽڴ�С�����ַ�����йأ� Ϊ������ʱ ��ȡ�����ֽ����Ĳ���

//���̵߳�ʹ�� ����thread ����using namespace std ���� thread text1(max); text1.join;
//�̲߳��ûᱨ�� һ���߳�ֻ��joinһ�� �ô��������߳�ִ������ִ�����߳� �Ῠס���߳�
//detach�����̺߳����̷߳������� �����߳�פ����̨ �˺�����join��
//joinable()�ж��Ƿ����join��detach ����Ϊtrue ������Ϊfalse
// ����ֱ���ں��������̵߳��߳����ұߴ��� ����ַҪref(num)
//return ���԰�ĳ���������߳̽���

//scanf�ĸ߼��÷� һ ָ������ scanf("%10d",&a) 
// �� ƥ���ض����ַ� scanf("%[a-zA-Z]",&a) ��ƥ��ĳЩ�ص��ַ� scanf("%[^\n]",&a) �������з�����
// �� ����ĳЩ�ַ� scanf("%*d") scanf("%*[a-z]") scanf("%*[^\n]") scanf("%*c") ����ջ�����
//sprintf(str,"a=%d",a); ���ɽ�printf�Ľ������str����

//malloc����Ҫ���������л������Ƿ�Ϊ��
//���乹�ɵĶ�ά������Դ��ݶ���ָ�����������ָ��
//���ǿɱ�����Ĳ�Ҫȥ�ͷ��ڴ棡����

//��ָ������һ�α��λָ�루��ĳλ���ĵ�ַ�� ������һ�α����
//���ֶ�ά������һά������׵�ַ���� ǰ��Ҫ��һ�Σ���ʱֻ��λָ�룩
// strcpy(s,s+1)����ʵ�ֶ��ַ�����ɾ�� ������ָ����λ����forѭ����ָ�뺯��
//�ַ����ı�ʾ�����������ַ�ָ��  sizeof(str)��ʾ�俪�ٿռ��С  �����׵�ַ��n �ɶԺ���Ĳ��ֱ�ʾ
//�ַ�ָ����ַ�������ַ����������� ǰ���ȿ����ַ�����Ȼ������׵�ַ��ֵ����ָ�� 
//        �������Щ�ǲ����         �����ȿ��ٱ��� �ٶԱ�����ֵ

//�ݹ���ô������� ���д������� void ���������ݹ���return���� д�ݹ�Ӽ����ӿ�ʼ���� ץס��Ҫ����
//a>b>c  ������������
//����(T - t > 10 ? 10 : T - t)���滻ȡ��ֵ����

//-6%5=-1  6%-5=1 -5%6=-5 5%-6=5 ֻ�ɵ�һ����ȷ������ Ȼ����������
//�������˱���������

//����ԭ�� ���� �������  ����ԭ��ȡ����һΪ����

//�Զ�����ת������ֵ���ʱ �ұߵ��ܽ��ǿ��Ϊ�������  
//              ���������ͱ��ʽʱ ���߾��ȱ� ���Ҳ�Ǹ߾��ȵ�
//ǿ������ת����(double)sum/count=3.147   (double)(sum/count)=3.000

//��md��ʽ������ռ������ -��ʾ�󶥸�  %+d  ��ʾ�����ֵ������ % d������������ո� ����������
//int a = 10;
//printf("%-3d%3d", a, 50);
//	double x = 20.402;
//printf("%10.2f\n", x);  //������10λ ����С��2λ %24.5s ��ֻ��ӡ5���ַ� ��24��

//�ȱ���� ���ڵ�ǰ���Ż�ֺ�
// ���ú�䣬���ֵ���¸��ֺŻ򶺺�
// ? : ������ն������� �ڵ�ǰ���ʽ�ı������
//int a = 0, b = 0;
//a = (b=0,++b,b++);
//a = --a == b++ ? a++ : b++;
//printf("a=%d b=%d", a,b);
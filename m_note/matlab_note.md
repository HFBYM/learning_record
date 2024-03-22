## 基本操作
 % clc 清除命令行窗口  clear all 清除工作区所有变量
s ='a'
abs(s)
char(97)
num2str(65)
length(s)
    % format rat 指定输出为分数 short四位小数 longE以科学计数输出
    % 双引号和单引号不一样！！！！！
disp('a is even') %在命令行输出    
prod(1:n) %将向量中的各项乘起来
tic toc %计时开始和结束
... %换行号 ctrl+c可以直接中止程序
    edit(which('mean.m')) %打开源文件
'a'=='aabbc' %得到的是一个序列 每个字符都比较
str(11001)='Z' %是把第一位 第二位 第五位变成Z

## 矩阵
A=[1 2 3; 4 5 6; 7 8 9]
B=A' %转置
C=A(:) %竖着拉直
D=inv(A) %求逆
E=zeros(10,5,3) %三层的十行五列矩阵 
A(2,:)=[] %删除第二行
F=[A B] %横向增广 F=[A;B] 竖向增广
    %rand 生成均匀分布在0到1之间伪随机数
    %rand(m,n) 生成m行n列的伪随机数
    %rand(m,n，'double')指定精度 也可以是single
    %rand('RandStream'm,n) 利用伪随机数种子
    %randn 生成标准正态分布的伪随机数
    %randi([iMin,iMax],m,n)生成在开区间内的随机矩阵
E(:,:,1)=randi(5,10,5) %更改第一层 开区间0~5
linspace(0,1,6) %等间距生成6个
diag([2,3,4]) %生成对角阵

max(A) %得到每一列的最大值 min用法一样
sum(A) %每一列的和 mean 每一列的均值
    %sort(A) 每一列从小到大 sortrows(A) 每一行根据第一个排序
    %size 得到行数和列数

## 元胞数组 类似结构体
A=cell(1,6) %A是一个一行六列的数组 未填充 也可以是两行的
A{2}=eye(3) %索引从1开始 eye指n阶单位阵
A{5}=magic(5) %magic指n阶幻方
    %A{1,2}得到内容 A(1,2)得到指针 
    %num2cell 可以将数字矩阵每格变成Cell
    %mat2cell 类似分块 
    %cat(1,A,B) 竖着接 2 横着接 3升一维接
    %reshape(A,1,4) 按列来将数组重排

## 结构体 不同于C
books=struct('name',{{'Mechine','Data'}},'price',[40,50])
    %name和price是key值用来索引
books.name='name';
books.id=1234;  %可以直接通过赋值来创建 第二个用books(2).id
    %用fieldname(books)得到里面变量类型
books.name %取出来的是一个cell数组
books.name(1) %取出来的是1*1的cell
books.name{1} %取出来的是字符串
%cell2struct 两者可以互相转换
%rmfield 删除某类变量

## 矩阵运算
B=1:2:9 %二为步长 从起点开始
C=repmat(B,3,2) %把B视为分块矩阵 将块重复三行两列
D=ones(2,4) %全为一的矩阵

A=[1 2 3; 4 5 6; 7 8 9]
B=[4 2 3; 4 8 9; 3 3 6]
C=A*B'
D=A.*B %带点意味着对应项相乘
E=A./B

A=magic(5)
B=A(3,2) %第三行第二列
C=A(3,:) %第三行
[m,n]=find(A>20) %找到A中大于20的项

## 流程控制
sum=0 %不等于是~=
for n=1:5 %n=1:1:5 步长1可省略 从1开始<=5
    sum=sum+n^2
end
while n<=10
end
if n == 5
elseif n == 3    
else n == 4
end 
switch n
    case 1
end

## 函数
function output=function_name(imput) 
    %这一行放在文件头 函数名与文件名要相同 可以只有方程名
    %注意式子中要点乘 防止输入的是序列
    %输出也可以是一个序列
val=input('Enter your number:');  %读取输入
isempty(val) %检测有无输入
label=['The C temperature is:',num2str(val+20)]; %用矩阵将两个字符串放在一起
    %内建变量 inputname mfilename nargin 实际输入参数个数 ~out输出的
    %varargin 输入参数的长度
f=@(x)exp(-2*x) %lambda表达式 可以直接使用f(x)

## 文件操作 (有更贴近C的文件操作)
save myData_1.mat %保存所有变量和名字 加上后缀-ascii可以用文本读取 但没有名字
load('myData_2.mat', '-ascii') %打开文本内容
Score=xlsread('04Score.xlsx') %读取excel表格的数字 加上B2:D4就可以读取特定矩形
xlswrite('045Score.xlsx',M,1,'E1:E4') %文件名 写入的变量 sheet 位置
[Score Header]=xlsread() %可以分开读取字符和数字

## 二维平面绘图
x=0:0.01:2*pi;
y=sin(x);
figure; %建立一个幕布
plot(x,y) %绘制一个图 如果只有plot(x序列) 也行
title("y=sin(x)")
xlabel('x')
ylabel("sin(x)")
    % hold on 在该指令以下继续在同一张幕布上画线 因为每一次画线都会清除前面的
    % hold off 不保存当前的东西
    % 线形可以在plot(x,y,'-')中改变 此处可以直接画
    % 也可以用legend('sin(x)','cos(x)') 来对每一条曲线进行标注 
    % legend('样本点','拟合直线','Location','northwest')
    % \pi e^{-x} 都是转义字符
str='$$ \int_{0}^{2} x^2\sin(x) dx $$'; %latex语法
text(0.25,2.5,str,'Interpreter','latex'); %在表格的0.25 2.5处引入latex文本
annotation('arrow','X',[0.32,0.5],'Y',[0.6,0.4]) %画出一个箭头
h=plot(x,y); %获得该曲线的句柄 gca获得当前坐标轴句柄 gcf获得当前画布句柄
get(h); %得到该物件的所有属性 set(gca,'Xlim',[0,2*pi]);更改坐标轴属性
    %每个取值的点(marker)的颜色和大小可以改
    %画多张图像时 注意gca和gcf的改变
subplot(m,n,1) %将一个幕布分成多个区域绘制图像 1~m*n的索引
    % axis square x总长与y一样 equal x单位长度与y一样 normal正常 
    % equal tight 坐标轴夹紧图像
    % grid on 在幕布中加网格线 axis off 只剩曲线 box off 去掉上面和右边的线
saveas(gcf,'<filename>','<filetype>') %图像保存

## 进阶绘图
x=logspace(-1,1,100); %从10的-1次方到10的1次方间取100个点
y=x^2;
semilogx(x,y); %x轴为对数显示 semilogy 是y轴 loglog两者都是对数显示

x=0:0.01:20;
y1=sin(x).*x*2;  %注意要点乘才可以结合两个函数
y2=sin(x)-cos(x);
[AX,H1,H2]=plotyy(x,y1,x,y2,'plot') %共用同一个x变量画图 Ax是坐标句柄
set(get(AX(1),'Ylabel'),'String','Function_1') %设置左右标签
set(get(AX(2),'Ylabel'),'String','Function_2')
set(H1,'LineStyle','--')  %改变线型
set(H2,'LineStyle','\:')  %改变线型

y=randn(1,1000);
hist(y,10); %绘制直方图 后者是区间个数
x=[1 2 5 4 8];
bar(x); %以下标1，2...的形式绘制x的条形图 matrix就是分成每一行来画 bar3(y)是3D
    %bar(y,'stacked')堆叠在一起 barh(y)横向绘制 指令可叠加
pie(y); %绘制饼状图 加上[0 0 0 1]可裂开 pie3(y)绘制3D
polarplot(theta,r); %绘制极坐标图
stairs(y); %阶梯链接 stem(y) 离散信号形 
%errorbar 绘制置信区间的

## 三维绘图
t=0:pi/50:10*pi;
plot3(sin(t),cos(t),t)
xlabel('sin(t)')
ylabel('cos(t)')
zlabel('t')

## 统计
fit=polyfit(x,y,1) %x和y是两个向量 1代表一次拟合 但图还没画出来 只得到两个参数
xfit=x(1):0.1:x(end);
yfit=fit(1)*xfit+fit(2);
plot(x,y,'ro',xfit,yfit); %此时把图像画出来

常用示例：
x=[60,80,100,110,116,126,146,159,179,199,226,246,266,290,330,360,420].*10;
y1=[4.48,6.4,8.64,10.37,11.08,12.05,12.67,12.8,11.92,10.87,9.6,8.63,7.86,6.72,5.76,5.12,4.32]./12.8;
y2=abs(670./(2.*3.14.*0.1.*x.*1i+1./(2.*3.14.*x.*0.0000001.*1i)+670));
plot(x,y1,x,y2,'--');
legend("实际幅频响应","理论幅频响应");
title("谐振电路的幅频响应","FontSize",20);
xlabel("f/Hz","FontSize",18);
ylabel("I/I0","FontSize",18);
axis square;

% x=[0, 0.03, 0.12, 0.25, 0.41, 0.59, 0.75, 0.88, 0.97, 1];
% y1=[1, 4.2, 17.5, 31.2, 57.2, 81.9, 107.1, 127.2, 141.5, 147];
% y2=[1.2, 5.8, 20.6, 34.5, 60.5, 87.9, 111.3, 132.9, 144.5, 148];
% 
% fit_1=polyfit(x,y1,1);
% fit_2=polyfit(x,y2,1);
% xfit=x(1):0.01:x(end);
% yfit_1=xfit*fit_1(1)+fit_1(2);
% yfit_2=xfit*fit_2(1)+fit_2(2);fit
% 
% subplot(1,2,1);
% 
% plot(x,y1,'ro',xfit,yfit_1,'r');
% hold on;
% plot(x,y2,'g>',xfit,yfit_2,'g--');
% 
% title('通过两偏振器后光强与两光轴夹角的关系','FontSize',18);
% xlabel('cos^{2}x');
% ylabel('光照电流I/10^{-7} A');
% set(gca,'FontSize',16);
% legend('左旋样本点','左旋拟合直线','右旋样本点','右旋拟合直线', ...
%     'Location','northwest');
% axis square;


% %%
% phi=0:1/18*pi:2*pi;
% I=[87.3, 86.4, 82.1, 75.6, 67.0, 57.2, 41.8, 39.6, 34.4, 31.8, 32.5,...
%    36.4, 43.6, 52.4, 62.5, 72.3, 80.4, 86.2, 89.0, 88.6, 84.2, 77.2,...
%    68.5, 58.2, 48.8, 40.6, 34.8, 32.0, 32.8, 36.7, 43.4, 52.4, 61.9,...
%    71.5, 79.1, 84.7,87.3];
% I_i=123*(3/4*cos(phi).*cos(phi)+1/4*sin(phi).*sin(phi));
% 
% subplot(1,2,2);
% polarplot(phi,I,'o',phi,I_i);
% title('线偏振光经过λ/2波片后偏振方向的变化规律','FontSize',18);
% legend('样本点','理论曲线');
% set(gca,'FontSize',14);

## 基本流程
可从powershell执行iverilog -o <module_name> \<file> 然后再执行vvp <module_name>
若要观察波形 可在终端执行命令 gtkwave .\wave.vcd
在设计时最好使用可综合的语言 不可综合的语言用在仿真
always之类的是行为级描述建模 在仿真测试后还要变成门级建模 后者是布局布线的基础
## 变量与基本数据
x 意味着信号数值的不确定，即在实际电路里，信号可能为 1，也可能为 0。设计者不关心其到底是0还是1(不建议出现)
z 意味着信号处于高阻状态，常见于信号（input, reg）没有驱动时的逻辑结果。例如一个 pad 的 input 呈现高阻状态时，其逻辑值和上下拉的状态有关系。上拉则逻辑值为 1，下拉则为 0 。
字符串被看为8位ascll序列

wire 类型表示硬件单元之间的物理连线，由其连接的器件输出端连续驱动。若没有驱动元件连接到 wire 型变量，缺省值一般为 "Z" 对wire类型赋值用assign 只要在always中左值都用reg 其他都是wire
寄存器（reg）用来表示存储单元，默认初始值为x。它会保持数据原有的值，直到被改写。reg[15:0] mem1[255:0],reg1 定义了256个16位和一个16位寄存器 位宽支持随机访问 data1[31-: 8] data1[31:24] 两种表示等价 都是8位
integer声明一个一般为32位有符号整数 辅助运算
time对仿真时间进行保存 位宽为64位
real实数型 默认值为0 赋给整数时只要整数部分被赋予
paremeter声明参数 一般只能赋值一次
注意平时使用时要避免隐式转换 可用 `default_nettype none 避免
向量访问按位支持变量 但不支持连续 即可以in[sel] 不能in[sel+3:sel] 注意中间是分号!!
## 模块
module \<modulename>(
    //端口定义 即在这里面写上input和output 这是2001的语法特性 声明就相当于创建 注意逗号
);
参数定义（可选）
输入输出信号定义 信号位宽与管脚有关
信号说明
功能定义：有assign 其他模块 always语句三种方式 三种方式之间是并行的

与模块对外接口相连的需要是wire型
多模块之间要做模块例化 最好把名字列出来一个个连 上层实例化下层模块时可以传参#(3,0)来改变下层的参数 Module  #(.W(6), .D(128)) name (<接口>)
在一个模块中改变另一个模块的参数时，需要使用defparam命令
## 程序块
assign是连续赋值并且可以并行 作用相当于连线
always是条件执行语句 always @(敏感条件) begin 程序语句 end 比如(a or b or d) 任意一个改变一次 则程序语句执行一次
也可以在条件里用*代替 则指代程序语句所有的条件信号(组合逻辑) 或者换成posedge(negetive) clk 上升沿或下降沿 (时序逻辑)
组合逻辑赋值用= 时序逻辑用<= 前者串行 后者并行 即执行完always块后再赋值

三态门 当wr_en有效时 将wr_data赋给data 当其无效时则不去动data 其代码为assign data=wr_en?wr_data:1'bz; z表示不驱动总线的行为

多位信号A&&B 是A和B内部先过或门 两者结果再过与门 最好不要使用
按位运算时 得到的不知道是什么就写x
单目按位与、或 就是将每一位之间连起来运算 &A=A[2]&A[1]&A[0]
逻辑比较中 只要有一个含x或z 则结果为x
可用{{4{1'b1, a, b}}, a}来连续拼接

case(S) 2'b10:         default:     endcase 多写else和default避免锁存器
普通的case必须都一样才能匹配 casez是把z和其他都能匹配，casex是在前者基础上对x同样操作(少用) 在电路中可用?代表z
casez和casex都是从上往下匹配的
begin end类似与大括号代码块     B={A[2],A[3],A[1]} 则代表后者拼接起来再赋值 B[0]=A[1]; B[1]=A[3]之类

可用begin:block1来命名 在块中可用disable block1 类似与break
genvar i 然后用generate和for循环来生成块 其本质像复制粘贴 对生成块必须进行命名用于区分 如xor_loop生成的就是xor_loop[0].member等
在生成块中想前后联系 最好创造一个向量来储存

一般都用异步复位 即敏感列表里面有or negetive rst_n 看波形时一般往时钟之前看
敏感列表里clk无法实现既检测上升又检测下降
注意时序逻辑中的临时变量会导致延时
可用宏函数
一个变量最好不要出现在多个块中 很容易被多重赋值
## 函数和任务
        function [N-1:0]     data_rvs ;     //可以定义返回和输入的类型 若在function后面加上automatic则该函数可并行使用和递归
            input     [N-1:0] data_in ;
            parameter         MASK = 32'h3 ;
            integer           k ;
            begin
                for(k=0; k<N; k=k+1) begin
                    data_rvs[N-k-1]  = data_in[k] ;  
                end
            end
        endfunction
函数只能与主模块共用同一个仿真时间单位，而任务可以定义自己的仿真时间单位。
函数不能启动任务，而任务能启动其它任务和函数。
函数至少要有一个输入变量，而任务可以没有或有多个任何类型的变量。
函数返回一个值，而任务则不返回值。
函数不能非阻塞赋值且是组合的
函数不能单独作为一条语句出现，只能放在赋值语言的右端	

        task xor_oper_iner;
            input [N-1:0]   numa;
            input [N-1:0]   numb;
            output [N-1:0]  numco ;     //无需再注明 reg 类型，虽然注明也可能没错
            #3  numco = numa ^ numb ;   //不用assign，因为输出默认是reg
        endtask
任务定义结构内不允许出现过程块(initial或always过程块)
任务可以作为一条单独的语句出现语句块中
任务定义结构内可以出现disable终止语句，这条语句的执行将中断正在执行的任务。在任务被中断后，程序流程将返回到调用任务的地方继续向下执行。

预处理指令用\` 宏的调用也要用\` 也可以\`include包含其他文件 注意没有pragma once 要自己写ifndef防止重复包含 \`timesclae 定义时间单位和精度

event可以定义一个事件名 在后面用#\<time> -> <event_name>来触发这个事件给always用
## testbench
主要内容有信号说明、时钟、复位、激励、模块例化、自校验
包含的其他模块在控制台一起编译 ~~可不用include 在iverilog扩展参数里面加上-i来忽视报错 或者在include path里面加上${workspaceFolder}/**/~~ 在设置里找到 run at file location __一般情况下可以看设置__
时钟用initial和forever语句编写
\$display系统函数 类似与printf 其中%m可以显示调用堆栈 \$time和\$realtime可以得到仿真时间 \$finish结束仿真 \$stop暂停 \$random生成随机数
\$dumpfile("mul_wave.vcd")生成vcd文件 \$dumpvars(1, m_mul) 即只储存top下第一层的变量 0表示其下所有层的变量 \$dumpon \$dumpoff启动和开始存储功能 #100 $finish结束仿真
\$monitor 配合on与off可以格式化监控各个变量的变化值并输出
\$bit(in)得到in的位数
force reg1 = 1'b1; release reg1;    可以对任意变量强制驱动
仿真流程
* md build  创建用于存放文件的文件夹(不一定需要放在特定文件夹里面)
* iverilog -o ./build/a.out ./src/tb_code.v ./src/code.v  编译源文件 若有include则只要一个 前者指定生成的文件位置
* vvp -n ./build/a.out      生成波形文件
* gtkwave ./build/wave.vcd  查看波形
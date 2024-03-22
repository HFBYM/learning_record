## 一般格式：
atlas语法：<STATEMENT> <PARAMETER>=<VALUE>
#statement 关键字必须在前，但语句中参数的顺序并不重要 
#<VALUE>的四种类型：
#实数、整数、字符和逻辑（ Real, Integer, Character, and Logical

一些符号的作用：
^：放在在逻辑参数前面，将逻辑参数设置为 false。
#：用在开头开头，用作单行注释。
\：用在行尾的，表示继续。（Atlas 最多可以在一行中读取 256 个字符。 但最好将长输入语句分散在多行中，以使输入文件更具可读性。）

命令顺序：
1. structure specification: mesh region electrode doping
2. material modols: material modols contact interface
3. numerical method selection: method
4. solution specification: log solve load save
5. results analysis

---
## 结构定义(atlas)
### 网格
#第一个statement必须是MESH SPACE.MULT=<VALUE>
#SPACE.MULT 参数值用作 X.MESH 和 Y.MESH 语句创建的网格的比例因子（scaling factor）。 默认值为 1。
#大于 1 的值将创建全局较粗的网格以进行快速模拟。 小于 1 的值将创建全局更精细的网格以提高精度。
#X.MESH 和 Y.MESH 语句分别用于指定垂直线和水平线的微米位置，以及与该线关联的垂直或水平间距。
X.MESH LOCATION=<VALUE> SPACING=<VALUE>
Y.MESH LOCATION=<VALUE> SPACING=<VALUE>
#必须为每个方向指定至少两条网格线。 Atlas 会自动插入允许任何相邻行之间的间距值逐渐过渡所需的任何新行。
#X.MESH 和 Y.MESH 语句必须按 x 和 y 递增的顺序列出。 x 和 y 的负值和正值都是允许的。 
 
ELIMINATE COLUMNS X.MIN=0 X.MAX=4 Y.MIN=0.0 Y.MAX=3
#从指定矩形内沿指定方向每隔一条网格线删除一次。
#删除以 x=0、x=4、y=0 和 y=3 微米为边界的矩形内的每隔一条垂直网格线 用row就删水平
### 区域
REGION number=<integer> <material_type> <position parameters>
#Region number必须从 1 开始，并为每个后续 region 语句增加。Atlas 中最多可以有 15000 个不同的区域。区域边缘最好与网格重叠 不然会自动补齐三角形
#Atlas中有大量的材料可用。 如果定义了依赖于成分的材料类型，则还可以在 REGION 语句中指定 x 和 y 成分的分数。
#使用 X.MIN、X.MAX、Y.MIN 和 Y.MAX 参数以微米为单位指定position parameters。
#如果新语句的position parameters与之前的 REGION 语句的position parameters重叠，则将重叠区域指定为新区域的材料类型。
#确保将材料分配给结构中的所有网格点。 如果不这样做，将出现错误消息并且 Atlas 将无法成功运行 
用compx.top=0.1 compx.bottom=0.53来划分区域上下的线性组分渐变 也可用grad让区域内某一处下降到0
### 电极
ELECTRODE NAME=<electrode name> <position_parameters> #默认接触为欧姆接触
#最多可以指定 50 个electrode。使用 X.MIN、X.MAX、Y.MIN 和 Y.MAX 参数以微米为单位指定position_parameters。
#多个electrode语句可能具有相同的电极名称。与相同electrode名称相关联的 node 被视为已经电气连接。
定义电极位置时可以使用一些快捷方式：
如果没有指定 Y 坐标参数，则假定电极位于结构的顶部。
使用 RIGHT、LEFT、TOP 和 BOTTOM 参数来定义位置。
ELECTRODE NAME=SOURCE LEFT LENGTH=0.5
#指定源电极从结构的左上角开始并向右延伸距离 LENGTH
### 参杂
DOPING <distribution_type> <dopant_type> <position_parameters>
分布方式可以为uniform(均匀) gaussion(高斯) n.type concentration= 1e16 浓度 位置可以是坐标也可以是区域编号
DOPING GAUSSIAN CONCENTRATION=1E18 CHARACTERISTIC=0.05 P.TYPE X.LEFT=0.0 X.RIGHT=1.0 PEAK=0.1
#DOPING 语句指定峰值浓度为 10^18 cm-3 的 p 型高斯分布。该声明指定峰值掺杂位于从 x = 0 到 x = 1 微米的一条线上。
#垂直于峰线，掺杂根据高斯分布下降，标准偏差为 (0.05/2^(1/2)) µm。在 x < 0 或 x > 1 处，掺杂横向下降，默认标准偏差为 (70/2^(1/2))% *char 
#可以使用 RATIO.LATERAL 参数更改此横向滚降。
#如果将 Gaussian profile添加到已使用相反掺杂类型定义的区域，则可以使用 JUNCTION 参数指定结深度的位置，而不是使用 CHARACTERISTIC 参数指定标准偏差 
DOPING ERFC N.TYPE PEAK=0.5 JUNCTION=1.0 CONC=1.0E19 X.MIN=0.25 X.MAX=0.75 RATIO.LAT=0.3 ERFC.LAT
DOPING P.TYPE CONC=1E18 UNIFORM
#这建立了一个施主分布，在 X = 0.5 微米处的峰值浓度为 1.0x10^19 cm-3。CHAR 参数决定了掺杂水平随距离的变化率，它没有直接设置在 DOPING 配置文件上。
#而且，它的计算使得 JUNCTION 参数给出的位置处的净掺杂水平为零。在这个例子中，受主浓度是 1.0×10^18 cm-3，均匀分布
#所以我们需要在 1 微米位置的施主浓度为 1.0×1018 cm 3 以在那里创建 p-n 结。CHAR 的值由公式计算，得到大约 0.43 微米的 CHAR 值。 JUNCTION是结深的意思
#此外，施主浓度在横向方向上下降到 0.25 至 0.75 微米的范围之外。横向衰减参数定义为主要衰减参数的 0.3 倍，并具有互补误差函数的形状 。
### 自动网格(适用于多层结构)
MESH AUTO (与绝对坐标混合使用时可能会引发错误 使用stay可以更好的构造中断结构)
X.MESH LOCATION=-1.0 SPACING=0.1
X.MESH LOCATION=1.0 SPACING=0.1
与“使用命令语言定义结构”指定mesh的区别：在 MESH 语句中包含了 AUTO 参数。 （需要此参数来指示要使用自动网格划分）
不会指定任何 Y.MESH 语句。（Y 网格线的位置将由 REGION 语句的参数自动确定。可以指定一个或多个 Y.MESH 语句。 此类定义的网格线将包含在网格中。 但是在自动网格划分中包含 Y.MESH 语句是可选的 ）
指定region 
REGION TOP THICKNESS=0.02 MATERIAL=GaN NY=5 DONOR=1E16
REGION BOTTOM THICKNESS=0.1 MATERIAL=AlGaN NY=5 DONOR=1E17 X.COMP=0.2 #Al的浓度
REGION TOP THICKNESS=0.08 MATERIAL=AlGaN NY=4 ACCEPTOR=1E17 X.COMP=0.2
REGION BOTTOM THICKNESS=0.5 MATERIAL=AlGaN NY=10 DONOR=1E18 X.COMP=0.2
DONOR、ACCEPTOR、X.COMPOSITION 和 Y.COMPOSITION 参数：指定 specified region上的均匀掺杂或成分（或者两个都指定）。
TOP、BOTTOM、THICKNESS 和 NY 参数：用于描述层的相对位置和厚度以及 Y 网格线的位置。运行一句就堆叠一层
THICKNESS 参数：描述了每层 Y 方向上的厚度（以微米为单位）。
在 X 方向，在没有指定任何 X.MIN 或 X.MAX 参数，假定该区域扩展到上述 X.MESH 语句中描述的 X 网格的整个范围。
NY 参数：描述region中包含多少 Y 网格线，以便 Y 网格线在该区域上均匀分布。
可以使用 SY 参数而不是 NY 来指定区域中 Y 网格线之间的间距（以微米为单位）。确保 SY 的值不超过 THICKNESS 的值。
SY、NY和THICKNESS之间的关系：SY = THICKNESS/NY
y方向的线不一定总是符合数目，因为其间距会自动插值
构造完了可以加上 save outfile = <filename>.str   tonyplot <filename>.str 来保存和显示结构

---
## 材料参数和模型
结构定义好后，就需要定义电极参数，材料特性、界面特性和物理模型
### 接触特性
电极接触特性用contact来定义，可以设置功函数、边界状态、外电阻等
### 材料特性
用material设置，有很多模型，可采用默认值。有些参数可用C注释器写成函数表达式
### 界面特性
用interface 可指明面电荷密度qf、电子空穴表面复合密度s.n s.p和界面交接情况
### 物理模型
由models 和impact指定 可用models mos print 采用mos管的默认模型

---
## 数值计算方法

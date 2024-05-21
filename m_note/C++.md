# 大规模设计
## 第零章
* 各个类的实现不应循环包含 难以单独模块化的测试
* 不应该包含一大堆不必要的头文件
* 最好不要有全局命名空间污染 typedef TargetId int 最好放在某个类内部
## 第一章
* const inline static typedef enum 宏指令都是内部链接
* 使用驼峰 类型名称首字母大写 成员变量使用m_前缀
* 一般的类函数按构造析构、操控更改、常量接口来分布
# 基础知识
* <cctype>                字符处理函数 isalpha isdigital之类的
* <algorithm>             包含STL算法
* <numeric>               包含小型库算法 累加 集合等

lambda表达式是隐式内联 [capture list(通常为空)](parameter list(可省)) -> return type(可省) {function body}
捕获列表表明此lambda函数使用的它所载函数中的局部变量 auto f=[]{return 42;};  f()调用lambda函数 不可使用默认参数
类似于仿函数，lambda函数定义了一种类 该类可以实例化对象  也可以被函数返回 由[=] 或[&]让编译器自动捕获所需变量
值捕获时在创建时捕获而不是在调用时捕获 引用捕获注意变量是否被销毁 [val] ()mutable{return ++val;}可更改捕获的变量
bind是一个函数适配器，可以用来更改一个函数的接口，具体使用要搜索

constexpr函数如果输入是个常量，那么这个函数的返回也视为一个常量
可以用assert和NDEBUG宏来辅助调试 __FILE__ __LINE__ __TIME__ __DATE__

异常处理机制： throw表达式 try语句块 一套异常类
出现异常就throw一个error 如runtime_error 抛出异常将终止当前函数，并转移控制权给能处理该异常的代码
try块后面的是至少一个catch子句 括号内一个(可能为命名的)对象的声明 称为异常声明 执行某个子句后跳转到所有子句之后
注意try块中的变量在其他块无法使用 在catch子句中也无法使用 搜索异常顺序与函数调用相反 在找到对应子句前函数都暂停
要是都找不到就会调用terminate标准库函数 会导致程序非正常退出 对于没有try语句定义的异常也是如此
常见异常：exception runtime_error range_error(超出了有意义的值域) overflow_error(计算上溢) 
underflow_error logic_error domain_error(参数对应的结果值不存在) invalid_argument length_error out_of_range

<numeric> accumulate累加 起始位置和起始值 fill将区间内的值变为指定值 set_intersection获取交集 集合处理都要是有序
set_union 获取并集 a和b的差集意为在a中但不在a和b的并集中 所以没有交换律 set_diffence获取差集
replace将区间内指定值替换为新值 replace_if将区间内满足条件的值替换为指定值
reverse()反转指定范围内的元素 copy把一个容器的指定范围内元素拷贝到另一个容器中 要先resize
merge()第一个容器的始末 第二个始末 第三个开始 两个容器都要是有序的 最后合并的也是有序的 目标容器也要开辟空间
random_shuffle() 把起始和末尾之间的数据随机打乱 用srand((unsigned int)time(NULL))打乱随机数种子 include<ctime>
for_each(,,fun)起始和末尾的迭代器 然后函数或者仿函数 会对之间的每一个元素调用这个函数
transform(,,,fun)第一个容器起始和末尾的迭代器 第二个容器的起始迭代器 一个(仿)函数 搬运的过程中对每个元素调用一次
这个函数的返回值作为新容器的元素 目标容器要提前开辟空间 用resize 而不是reserve因为后者虽增大容量 
但迭代器无法访问 因此有时候会多出无效数据0 所以要注意一些算法的返回值 是指向有效数据的迭代器
find_if条件查找算法(v.begin(),v.end(),MyCompare()) 后面传入的就是一元谓词 传入了一个匿名函数对象 返回迭代器
count count_if按条件查找  adjacent_find查找相邻的重复元素 binary_search二分法查找 bool类型 只用在有序序列中
sort(v.begin(),v.end(),MyCompare()) 后面传入的要是二元谓词 用于比较和排序
unique算法将不重复的部分放到前面，并返回不重复部分的尾后迭代器

函数对象，即仿函数 重载()后可以当函数使用 但可以记录这个函数对象的一些状态 可以当作值被传递 
返回bool类型的仿函数被称为谓词 一个参数为一元谓词 两个参数称为二元谓词
<functional> 内建的仿函数 用法与函数完全相同 这些都只是模板 要自己填充且实例化才能使用
算数仿函数：用于四则运算 plus minus multipiles divides modulus取模运算 negate取反 只有这个是一元的运算
关系仿函数：greater_equal less equal_to 也都是模板 要填充且实例化才能当仿函数用 
逻辑仿函数：logic_not logic_or logic_add

<map> 每个元素都是一对 第一个为key值 起到索引、下标作用 第二个为实值 元素插入时根据键值自动排序 底层也是二叉树
 用迭代器输出key值和实值 lo=m.lower_bound(1),hi=m.upper_bound(2) 可以输出所有key为1，2的实值(用second)
 或者用begin 来顺序输出容器里的值 此时不需要知道键值 或用find和count结合使用输出实值 一般用at(key) 输出 更安全  
mutimap可以有重复的key值 有size empty swap函数 插入时要用pair对组 erase(key)删除key值 find(key) count(key)
也是通过仿函数更改排序规则 只需要对key值进行比较就行 因此仿函数只要key值类型进行比较

pair<T1,T2> ret(value1,value2) 是一个对组 用first second 访问两个元素 pair<T1,T2> p=make_pair(v1,v2)

<set> set不可以有重复数字 mutiset可以有重复函数 这是一个关联式容器 底层是二叉树 会对插入的数据进行排序
插入数据时只有insert 类似vector的使用迭代器 也有size empty swap函数 erase(elem)不仅可以用迭代器 还能传数据删除
find(key) 查到返回其迭代器 否则返回end cout(key)统计这个元素个数 用仿函数实现更改排序规则
先写class MyCompare 在里面重载()bool函数 然后在创建容器时指定 set<int,MyCompare> s1

<list>双向循环链表 即头节点prev为尾节点 尾节点next为头节点 且链表的变动不会让其迭代器失效 vector就不行
其构造函数、大小操作与vector相似 也有swap函数 不可以跳跃访问 只能自增自减 不能加一减一
头尾都可以插入和删除 其他地方的插入和删除方式也与vector类似 但多了个remove(elem)移除所有和elem相等的元素
reverse 反转链表 sort函数里可以传入自定义的bool类型排序函数 

<stack>先进后出 push入栈 pop出栈 top看栈顶元素 <queue>先进先出 push队尾进 pop队头出 top看队头 back看队尾
deque容器是双端容器 vector是单端 前者可以从头部进行插入删除 push_front pop_front 其构造和赋值操作与vector一样
其大小容量、数据读写、插入删除进行操作的函数与vector几乎一样 头文件是<deque>

vector<int> 是编译器根据模板生成一种新的类型 类似数组 而vector<vector<int>>像二维数组
vector<T> a(n) 是有n个默认初始化的T 不是把n赋值给一个元素上 vector<T> a 是a为空 但潜在类型为T
列表初始化要用花括号把数值列出来 和圆括号初始化不一样 当列表中的值不能初始化时 将其用来构建vector数量
用push_back(i) 从末尾压入vector对象中 vector其他操作类似string
迭代器是一种类似指针的可访问容器元素的方式 auto b=vec.begin().c=vec.end(); （尾迭代器c）指向end的下一个
用*it来访问迭代器所指的元素 不能访问尾后迭代器 但可以auto it=back_inserter(vec) 得到可以增加元素的尾后迭代器
习惯使用迭代器和!=来进行循环 ++it --it是移动迭代器的指向
使用了迭代器的循环体 不要往里面的容器添加元素 	for_each(v.begin(), v.end(), fun);遍历算法
可以用vector<T> v(v.begin,v.end) 来获取[v.begin,v.end)中的元素 注意左闭右开
.empty判断是否为空.capacity得到容量 插入元素时动态增加.size得到元素个数 resize重新指定大小 多了用0补 少了去除
pop_back尾删除 插入和中间删除与string一样 但用迭代器指定位置 clear()清空容器 重载[]进行下标访问
swap(&vec) 将两个容器内容互换 用vector<T>(v).swap(v)来收缩v的容量与大小相符
reserve(1000)来给容器空间但不初始化 减少容器的容量扩展次数

string s(10,'c') 是十个c getline(is,s) 从流中读取一行  换行符也被读取进来 但是不存储
s.size() 返回长度 是string::size_type类型 小心混用！！ s1+s2 连接 s[n] 引用字符 可直接比 
字面值不能直接相加 要在运算中转化成string型才可以 str=str+"1"+"2"
范围for循环 for(auto 变量: 序列) 直接得到序列中的每一个元素的值 想要进行改变就用auto &c 不应改变序列大小
对于字符串的循环下标 用decltype(str.size()) i 或string::size_t
stf.find 查找第一次出现位置 rfind查找最后一次出现位置 replace 从pos开始后面n个字符换为str2
insert表示插入字符 erase表示删除 substr表示返回从pos位置开始的子串
npos是size_t的最大值 用于表示不存在的位置 比如find函数找不到就会返回这个值 在string中表长度的话 是直到字符串末尾
const char* str=R"(aabb\n\t)"		原生字符串 内不做转义且可以换行

template<typename T> 先声明T是一个通用的数据类型 然后直接用T去写某些函数 将类型参数化 一个声明下接一个函数模板
两种使用方式： 1.自动类型转换 即直接用这个函数 2.显示转换 swap<int>(a,b)
写在template下的函数必须要用到模板类型T或者显示确定T的类型且T的类型要一致
优先调用普通函数，但可通过空模板来强制使用函数模板 函数模板也可以发生重载
模板也可以重载 template<typename T> fun... 重载 template<> void fun(Person &p1,Person& pw)
类模板：template<class NameType,class AgeType> 声明后可以在下面的一个类中使用虚拟的数据类型
Person<string,int>p1("ah",87);来使用类模板 只有类模板可以有默认参数 template<class NameType,class AgeType=int>
类模板对象作参数：1.指定类型 即把数据类型参数给出 2.参数模板化 即在函数前加上template<class T1,class T2>然后使用
用typeid(T1).name()输出类型名字 3.整个类模板化 即用template<class T> 让编译器自己推断类的名字 一般用第一种
子类继承父类模板时 要么指定类型:public Base<int> 要么子类也使用类模板:public Base<T>
类模板的作用域发生改变Person<T1 ,T2>::Person(T1 name,T2,age)
类模板的成员函数是在运行阶段生成的 因此一般方法将类模板分文件编写是不行的 因此把声明和实现写在一起 后缀改为.hpp
全局函数作类模板的友元 最好直接在类内实现
不同数据类型填充的类模板不算一个类 不能访问私有成员  其拷贝初始化最好都是同一数据类型 在类内对传进来的同一类型
直接用MyArray& a 就可以使用或者设定为返回值 默认两者数据类型是一样的

当在做一个项目时  可以写一个管理全局的类来贯穿整个项目，管理文件 提供接口

文件操作：要包含头文件<fstream>  ofstream写文件 ifstream读文件 fstream读写文件
ios::in out ate初始位置文件尾 app追加写 trunc若存在先删除再创建 binary以二进制形式 用|使用多种方法
创建流对象 ofstream ofs 指定打开方式 ofs.open("text.txt",ios::ofstream|ios::binary)
ofs<<"Tom"<< endl   ofs.close()  用ifs.is_open()判断是否打开成功
char buffer[1024]={0}第一种 while(ifs>>buffer) 第二种 ifs.getline(buffer,sizeof(buffer)) 
string buffer 第三种 getline(ifs,buffer)通过string的内置函数操作 第四种用c=ifs.get()逐字符操作
二进制读写:Person p;ofs.write((const char*)&p,sizeof(Person))  ofs.read((char*)&p,sizeof(Person))
若文件为空 则里面只有一个字符eof 用一个字符ch读出一个字符后 让文件指针指向文件末尾
再用ifs.eof()用于判断文件是否为空

        class Animal
        {
        public:
            virtual void speak() 用了虚函数 就可以进行函数晚绑定 即根据传入对象来执行函数
            {
                std::cout << "Animal is speaking"<<std::endl;
            }
        };    地址早绑定：在编译阶段就绑定函数的地址 地址晚绑定：在运行阶段绑定地址
        class Cat :public Animal
        {
        public:
            Cat() :m_name("Tom") {};
            void speak()
            {
                std::cout << "Cat is speaking" << std::endl;
            }
            std::string m_name;
        };
        void doSpeak(Animal& animal) 父类的引用和指针可以指向子类的对象 
        {
            animal.speak();    如果不是虚函数，那么此处调用的就是父类的函数 因为函数地址早就绑定了
        }
        int main()
        {
            Cat cat;
            doSpeak(cat);
            cat.Animal::speak();
            return 0;
        } 

动态多态：首先要有继承关系 然后子类要重写父类的虚函数  重写：函数返回值，名称，形参都一样
使用： 父类的指针或引用指向子类的对象 然后调用那个虚函数
当一个成员函数被声明为虚函数时，其派生类所有同名函数默认为虚函数
virtual void speak() 此时在类里已经有了一个虚函数指针，指向一个虚函数表(vbtable) 
可以在子类的同名函数中写上override提示该函数已被重写
表内部记录一个虚函数地址(即为&Animal::speak)若子类没有重写 则这个虚函数指针也会一并继承 指向同个虚函数表
当子类重写了父类的虚函数 则子类中的虚函数表内部会加上子类的虚函数地址 
这个添加在类被创建时发生，在父类的指针或引用指向子类的对象 然后调用那个虚函数时使用
用多态实现计算器：写一个抽象类（只有成员属性 函数为空） 再写四个类来继承 用多态的方式实现每部分功能
纯虚函数：virtual int fun()=0; 含有这种函数的即为抽象类 无法实例化对象 其子类必须重写纯虚函数
多态就是一种接口多种形态 父类相当于于一种模板 抽象类虽无法实例化对象，但可以使用其指针和引用
虚析构和纯虚析构:父类的指针或引用指向子类的对象 只能操控其从父类继承来的成员 导致在销毁时子类析构不会触发
利用虚析构可以让子类在被释放时可以运行子类的析构 纯虚析构要类内声明 类外实现 一有纯虚就变成抽象类

继承：class 子类: 继承方式 父类 子类也称为派生类 父类也称为基类 两者不算同一个类了
class Java: public BasePage {}; 即可继承BasePage类public的所有内容
任何继承方式都不能访问父类private内容 但是会被继承下去 公共继承： 子类的继承项访问权限和父类一样
保护继承：都变成了保护权限  私有继承：都变成私有继承
p129 查看对象模型  先构造父类 再构造子类 析构相反
子类访问同名成员 直接访问  子类的同名成员函数 会隐藏掉父类的所用同名成员函数（包括重载函数）
若要访问继承自父类的同名成员属性或函数 要加作用域 s.Base::m_a 
子类继承下来的静态变量与父类的是同一个 多继承的情况下也是一样
菱形继承（或钻石继承）要在每一个重复继承项前加作用域 可用虚继承来解决资源浪费问题
sheep和tuo :virtual public Animal 后者称为虚基类 同时继承sheep和tuo的子类就不会出现二义性

运算符重载 这些函数本身也可以发生函数重载 就是可以写多个同一个运算符的重载
通过成员函数重载 Person opetator+ (Person &p) Person p3=p1.operator(p2) =>Person p3=p1+p2
通过全局函数重载：Person operator+ (Person &p1,Person &p2)
左移运算符重载：一般不用成员函数来实现 因为无法实现cout在左边 
所以ostream &operator<<  (ostream &cout,Person &p) 	int& a = int(8)对于单纯的一个值无法进行引用
Person operator++(int){Person temp=*this;this->num++; return temp}   用占位参数来表示后置递增
赋值运算符重载函数也是默认的浅拷贝 在有堆区开辟时要重载它为深拷贝
函数调用运算符重载，也叫仿函数：void operator()(string str){cout} myprint("Hello")用对象来调用这个函数
用匿名对象调用仿函数：MyAdd()(100,100)

友元：把friend 全局函数的声明 放在一个类内 则这个全局函数就可以访问这个类的私有成员 
也可以friend class goodgay 放在一个类内 则goodgay 可以访问这个类的私有成员
若是成员函数 要在函数名前加上类作用域 然后与全局函数操作类似

静态成员变量：所有对象都共享一份数据  类内声明，类外初始化 即在类外int Person::m_A=10  
可以通过类名直接访问 cout<< Person::m_A
静态成员函数：访问方式和静态成员变量一样   其只能访问静态成员变量
只有非静态成员变量是属于类（或其对象）上的   静态成员变量，静态成员函数及普通成员函数与类大小无关 
this指针指向被调用的成员函数所属的对象，可以在成员函数中通过这种方式来使用其对象
它隐含在每一个非静态成员函数里 不用定义 直接使用 是指针常量
返回值的传递方式和函数调用时的传递方式一样 是拷贝模式 若想返回并使用同一个内存 要返回引用 链式编程
可以用Person *p=NULL; p-> 来访问与this指针无关的成员函数 if(this==NULL) return
 常对象const Person p; 常对象只能调用常函数 但可以修改静态变量的值
常函数const放在函数声明后面 实质上是修饰了this指针 使其指向性和指向的值都不能更改
但如果一个成员变量前有mutable关键字修饰 那么它就可以在常函数中被更改，也能在常对象中被更改

构造函数没有返回值也不写void 函数名称与类名相同 可以有参数 因此可以重载 只在程序创建对象时自动调用一次
用Log()=delete;来删除构造函数使其不能实例化
列表初始化构造函数 Person(int a,int b,int c):m_A(a),m_B(b),m_Phone(string){ } 可以利用类的构造函数
拷贝构造函数 Person(const Person &p){ age=p.age  } 把传入的参数数据拷贝到自己身上
调用 ： Person p1;  Person p2(10); Person p3(p2);  编译器有默认拷贝函数 里面只有属性值拷贝
Person p2=Person (10); Person p3=Person (p2);  显示调用 右侧是匿名对象 当前行结束后就会被销毁
在类进行值传递和值返回时 会默认使用拷贝函数来创建临时对象或赋值 要注意此时是否要用到深拷贝操作
浅拷贝：简单的赋值拷贝操作  深拷贝：在堆区申请空间进行赋值操作
析构函数与构造函数相似 只是名称是~类名 且不能有参数 在其销毁前程序自动调用 两个函数都要在public下
当其他类对象作为本类成员时，先构造类对象，再构造自身  析构相反 但如果成员属性是类的指针 就按正常顺序进行
析构函数主要把对象开辟的堆区空间给释放 在浅拷贝时可能导致堆区内存重复释放
C++只支持一次隐式转换 不能从const char* 到string再用构造函数
在构造函数前加上explicit使得该函数的使用必须为显式转换

头文件里只除去函数实现就行   记得分号放在函数后面 使用时要包含头文件
函数实现单独放在另外的文件 但是成员函数要在前面添上类的作用域

public  公共权限 成员 类内可以访问 类外也可以访问      访问即更改和使用
protected 保护权限 类内可以访问 类外不可访问  子类可以访问
private  私有权限  类内可以访问 类外不可访问  子类不可以访问 成员函数可以访问同类所有对象的私有成员
struct默认权限是公共 class默认权限是私有
最好成员属性私有 然后提供公共的函数作为借口以控制各属性的权限 也可以检测输入的有效性

函数形参的默认值 int fun(int a,int b=10,int c=20) 从第一个有默认值的形参往后都要有默认值 
现在可用fun(10) 或者 fun(10,20)  函数声明和函数实现只能有一个有默认参数
int fun(int a,int=10) 这里是一个占位参数 调用时也要传值 或者用默认参数
函数重载 返回值类型是不能作为重载条件的 只能有参数的不同 但本质还是要看函数调用是否出现二义性

system("cls");  清除控制台屏幕  system("pause");       按任意键继续
int *p=new int(10)  在堆区开辟一个空间里面的值是10并返回指针 也可以不写10和括号 delete p 释放堆区数据 
int *arr=new int[10] 开辟数组空间  delete[] arr 释放数组空间
不要返回局部变量的引用  函数的调用可以作为左值存在

定义数组的时候必须指定数组的类型，不能用auto关键字
int *beg=end(arr); 类似尾迭代器  也可用范围for来逐层访问多维数组的行与列，且每层都要引用
vector<int> arr_1(begin(arr),end(arr));          用数组来初始化容器       

标准流 cin cout cerr clog  C4828: 高级保存选项 改成UTF-8 带签名 在行首的ctrl+z才是结束符！！
<< 这种运算符 返回值是流 会略过分隔符 当对流进行判断时 若遇到结束符和无效输入 流就会变成无效状态
<< flush刷新缓冲区 << ends加上空格刷新缓冲区  << endl加上回车刷新缓冲区 << unitbuf即输即刷 << nonunitbuf恢复原状
cin.tie(&cout)关联流 更改前者会立即刷新后者
可用圆括号初始化 int num(0);   不能混用有符号和无符号！！！
引用 相当于变量的别名 int& num=n; 被引用的变量要先被定义 且引用一定要被初始化
顶层const指针本身是个常量  底层const 指向的对象是常量
 auto sum=a+b; 根据表达式类型自动创建类型 会忽视顶层const
 decltype(?) x=...  得到？的结果表达式类型但并不实际运行它 保留顶层和底层const
int i;表达式 i=x ;的类型是引用 用这个类型定义变量 *p=&i *p是引用类型而不是int 双重括号结果类型一定是引用 
枚举常量可用: unsigned char 来定义枚举常量的类型
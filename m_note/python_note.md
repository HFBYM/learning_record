# 环境搭建
    python -m venv .venv 
* 在指定的项目下用终端输入 上述代码 运行在虚拟环境 便于版本控制
  虚拟环境创建成功之后，一般不会自动启用，所以需要启用它
  可以在powershell中运行脚本Activate.ps1（也可以在cmd中运行activate。bat）
  注意：可能遇到不能执行脚本的错误，可以以管理员身份打开powershell，并执行set-executionpolicy remotesigned，提示是否更改执行策略时，输入“y”并回车即可执行ACtivate.ps1脚本
* 有时候使用cmd而不是power shell  
* pytest可用于测试 需要在设置里启用
# 基本语法和特性
## 数据类型和基本函数
    # -*- coding: utf-8 -*- 用该指令告诉解释器以utf-8解读
#为注释 可用autoDocstring插件来写文档注释
三引号可以内部换行 多引号可以包含少引号 或者用转义字符
* type内置函数查看类型 **是幂运算 //是取商的整数 False True为bool值 None表示空值 注意大小写
* print ('%d 是一个合数' % num) 可用格式符来输出 print('{}x{}={}\t'.format(i, j, i*j), end='') 也是格式化输出
* isinstance(num, (float, int)) 判断前者是否为后者的类型
* raise TypeError("错误参数") 抛出错误
* dir()函数时，它会返回一个包含对象属性和方法的字符串列表
* year = int(input("请输入一个年份: ")) 输入函数
|方法|说明|
|-----|------|
|int(x [,base ])  |       将x转换为一个整数  |
|float(x )    |           将x转换到一个浮点数  |
|complex(real [,imag ])|  创建一个复数  |
|str(x ) |                将对象 x 转换为字符串  |
|repr(x ) |               将对象 x 转换为表达式字符串  |
|eval(str )  |            用来计算在字符串中的有效 Python 表达式,并返回一个对象  |
|tuple(s )  |             将序列 s 转换为一个元组  |
|list(s )   |             将序列 s 转换为一个列表  |
|chr(x )   |              将一个整数转换为一个字符  |
|unichr(x )  |            将一个整数转换为 Unicode 字符  |
|ord(x )     |            将一个字符转换为它的整数值  |
|hex(x )     |            将一个整数转换为一个十六进制字符串  |
|oct(x )     |            将一个整数转换为一个八进制字符串  |
类型转换可以直接转 但不合规则的字符串不能转相应的数字
python不声明变量类型
* 列表：list = [12, "Hello World", 'U'] 可用list[0:2]左闭右开区间来访问 用list.append()进行尾插 用del list[2]删除
        列表可以用运算符进行计算 跟容器一样有许多内置函数: insert pop 可以用负数索引访问list[-1]
* 元组：tuple = (123, ) 当只有一个值时后面要加逗号 无修改函数 不能修改元组的指向 但可以修改指向本身的值 比如里面有个列表 可以修改这个列表来改变元组
        元组也有许多运算操作符和辅助函数
* 字典：dict= {'一点水': '131456780001', '两点水': '131456780002', '三点水': '131456780003'} 类似于map dict1['jack']='44‘ 直接改或加键值对 
        或通过键值del删除 或del删除整个字典 或调用clear清除所有元素 可用内置函数操作和转换
* 集合：set1=set([123,456,789]) 其创建需要列表 内部无序不重复 类似只有key值的字典 用.add .remove修改 可做集合的交并差运算
## 分支
    if java > 80 and  python > 80:
        print('优秀')
    else :
        print('不优秀')
每个if或else或elif的条件后面要加冒号 缩进相当于大括号 用and和or控制条件关系
## 循环
* break	在语句块执行过程中终止循环，并且跳出整个循环
  continue	在语句块执行过程中终止当前循环，跳出该次循环，执行下一次循环
  pass	pass 是空语句，是为了保持程序结构的完整性
* for iterating_var in sequence: 
    statements(s)
  字典循环只输出key值 若是for var in range(0, 10, 2) 即左闭右开区间i步长为2
  for...else语句 若循环没有break则执行else中的语句 较反直觉 少用
* i = 0
  while i < 10:
    print(i)
    i = i + 1
# 函数
    def functionname( parameters ): #参数可以有默认值 但是如果是默认列表的话会有点问题
      "函数_文档字符串"
      function_suite
      return [expression] #可以无值返回 相当于返回None 也可以返回a, b 相当于返回一个元组
函数定义需要写在前面 因为是解释型语言
可以function(par_2 = val_1, par_1 = val_2)关键字传参来指定传递到哪里
若用def print_user_info( name ,  age  , sex = '男' , * hobby): 则最后的是元组 即不定长传参
若用def print_user_info( name ,  age  , sex = '男' , ** hobby):则必须关键字传参且hobby是一个字典 key值也是hobby
若用def print_user_info( name , *, age  , sex = '男' ): 则星号后面的参数都必须使用关键字传输
除了list和dic其他变量都是值传递
sum = lambda num1 , num2 : num1 + num2; 以分号结尾且只支持一个表达式 该值即为返回值 且其中参数要运行到调用行时确定 不是定义时确定
# 迭代
*  #只要是序列 比如字符串什么的都可以迭代
  for key in dict1 :    # 迭代 dict 中的 key
      print ( key , end = ' ' )
  for value in dict1.values() :   # 迭代 dict 中的 value
    print ( value , end = ' ' )
  for x , y in [ (1,'a') , (2,'b') , (3,'c') ] :
    print ( x , y )
* tuple1 = ( 1,2,3,4 )          #采用创建迭代器的方式访问
  iter3 = iter ( tuple1 )
  for x in iter1 :
      print ( x , end = ' ' ) 
* while True :                 #使用next迭代器访问数据
    try :
        print ( next ( iter3 ) )
    except StopIteration :
        break
* list生成式 list1= [x * x for x in range(1, 11) if x % 2 == 0] 或者 list1= [(x+1,y+1) for x in range(3) for y in range(5)] 方便生成列表
* gen= (x * x for x in range(10))   #遍历生成器的元素
  for num  in  gen :
    print(num)
  生成器不储存值 每个数据都是在迭代时yield出来的 每次yield就像往一个虚拟列表插值 迭代时就将虚拟列表计算出来
  变成生成器的函数，在每次调用next()的时候执行，遇到yield语句返回，再次执行时从上次返回的yield语句处继续执行 若yield数量少于迭代查询的次数会报错
* 用reversed反向迭代 用zip(key, value)可以生成字典 也可以for name, age in zip(names, ages): 同时迭代多个列表
# 类和对象
    class ClassA():
        var = 100
        def fun():
            print('我是 fun')   #定义过程和C++类似 调用也是
* 若一个类函数需要调用自身参数 则必须 @classmethod  def func(cls, age):  cls.val + age来定义和使用参数 使用的时候就可以ClassA.func(age)
  类变量的更改可以由外部直接更改或者类函数按上述方法更改
* 若想拿来实例化 则去掉@classmethod cls改成self 然后a = ClassA()类变量的更改会导致实例变量的更改，而反之不会 
  使用类.原始函数 = 新函数 就成完了类的函数重写了
* __init__(self)是构造函数 也可以传参 def __del__(self,[...):是析构函数 用del a删除对象 
* super(UserInfo2, self).__init__(name, age, account) 调用父类的函数
* 多态行为和C++类似 传参时父类参数指向子类对象
# 模块
一个文件即为一个模块 导入模块用import 可以用as alias 模块导入后可以通过模块名访问内部的东西  模块的搜索路径在sys模块里的path 
用from ... import ...可以直接使用成员名而不用模块来索引
内置__name__函数判断是否为主模块
当一个目录下有__init__.py时 该目录被视为包 以路径区分 防止模块名重复
python中用_来区分私有和公有 但调用全靠自觉
# Magic Method
由__包围起来的就是内置函数 可用dir(Class) 查看 可以控制变量的访问、创建、销毁 类内部相当于字典 self.__dict__[name] = value 注意不要无限递归
运算符操作也算内置函数 也可以重写
描述器__set__ __get__比内置函数高层一些 也可以设置访问和更改的流程 ??
# 枚举
from enum import Enum
Month = Enum('Month', ('Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun', 'Jul', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec'))
遍历枚举类型
for name, member in Month.__members__.items():
    print(name, '---------', member, '----------', member.value)
直接引用一个常量
print('\n', Month.Jan)
可以更改其默认值类型
只支持不等和标识比较 若要比大小需继承intenum类
# 元类
每一个类都是对象 具有实例化的能力 
type(类名, 父类的元组（针对继承的情况，可以为空），包含属性的字典（名称和值）) 用此动态创建类
元类是负责生成类的 type是内建的元类
其实 __metaclass__ 就是定义了 class 的行为。类似于 class 定义了 instance 的行为，可以说，class 是 metaclass 的 instance。
元类的作用：拦截类的创建，修改类，返回被修改后的类
## 一般流程
cmake需要CMkaeList.txt来操控流程	config然后build是从源码生成对应软件的工程文件 接着在工程文件里面可以编译生成可执行文件
进入空白的build文件夹 使用cmake ..找到上级list文件 然后得到sln文件 若使用gcc 则用cmake -G "MinGW Makefiles"
如果有多个项目 设置出单个启动项
常用宏: 
* PROJECT_SOURCE_DIR/CMAKE_SOURCE_DIR/_SOURCE_DIR: 为包含project()命令的最近一个CMakeLists.txt文件所在的文件夹路径
* CMAKE_CURRENT_SOURCE_DIR: 当前CMakeLists.txt所在目录 注意不是所有都包含project()命令 但两者之间可能一致
* PROJECT_NAME: 当前项目名字
* PROJECT_BINARY_DIR 项目生成的临时二进制目录，用于存放配置/编译中间文件
* 可用add_definitions(-D<宏名称>)来定义一个宏放到最终的源文件里

先创建CMakeLists.txt #是注释行
* cmake_minimum_required(VERSION 3.0)
* project(<名字> CXX) 代表工程所需要的编译器
* set(CMAKE_CXX_STANDARD 17)设置使用的C++标准
## 变量与源文件
可以用set(<变量名> <值>)来创建变量 但值默认的都是字符串类型  变量的使用必须按照\${<变量名>}来读取值 但改变值不用
EXECUTABLE_OUTPUT_PATH是输出的exe文件位置宏 可用set直接更改 /home/sort
include_directories(\${PROJECT_SOURCE_DIR}/include)  通过源码根目录来定位include目录 并将其并入编译器的include目录中 类似配置里的包含

aux_source_directory(\${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST) 查找某个目录下的全部源文件并保存到一个变量里 宏表示当前CMakeLists.txt路径
也可用file(GLOB MAIN_SRC \${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)来搜索符合条件的文件	
add_executable(<可执行程序名> <用到的源文件名>) 源文件名用分号隔开 头文件也放在这里面
## 库
若需要生成静态库 则使用add_library(<库名> STATIC <源文件名>) 动态库用SHARED 动态库要和别的exe文件放在一起
修改库的生成路径则需要更改LIBRARY_OUTPUT_PATH 注意两种库、可执行程序这三个选项中只能出现一种

link_directories(<静态库路径>)  link_libraries(<静态库全名或去掉lib .a的名字>) 类似设置配置
target_link_libraries(<目标文件> <库名>) 动态库的链接具有传递性 可设置权限 该命令须在生成可执行程序之后 动态库也需要路径 命令同静态库
在windows下 动态库的链接需要一个库来导入 该库包含动态库的符号表 是一个导入库 也是.lib文件
如果链接不了 干脆直接把exe和动态库放在一起
## 其他
message(STATUS "source path: \${PROJECT_SOURCE_DIR}") 日志 WARNING警告 FATAL_ERROR错误

拼接:list(APPEND SRC_1 \${SRC_1} \${SRC_2} \${TEMP})把后三者的值拼接放到第一个
移除:list(REMOVE_ITEM SRC_1 \${PROJECT_SOURCE_DIR}/main.cpp) 注意file搜索到的是绝对路径 所以移除也要绝对路径

使用add_subdirectory()可以构建嵌套CMakeLists文件
使用foreach和if来迭代与控制流程
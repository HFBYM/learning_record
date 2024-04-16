# 环境搭建
    python -m venv .venv 
* 在指定的项目下用终端输入 上述代码 运行在虚拟环境 便于版本控制
  虚拟环境创建成功之后，一般不会自动启用，所以需要启用它
  可以在powershell中运行脚本Activate.ps1（也可以在cmd中运行activate。bat）
  注意：可能遇到不能执行脚本的错误，可以以管理员身份打开powershell，并执行set-executionpolicy remotesigned，提示是否更改执行策略时，输入“y”并回车即可执行ACtivate.ps1脚本
* 有时候使用cmd而不是power shell  
* pytest可用于测试 需要在设置里启用
# 基本语法和特性
#为注释 
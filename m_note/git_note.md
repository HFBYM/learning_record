## Linux指令
git bash Linux风格 git cmd Windows风格 git gui 图形化设计		
Linux指令:
*	cd 改变目录 cd ..回退目录 pwd得到当前目录 clear清屏 ls列出当前目录所有文件 touch 新建文件 rm 移除文件  ctrl+p 上一条命令
*	mkdir 创建文件夹 rm -r 删除文件夹 mv a b 把a移动到b 对同一个目录下的可以重命名 history 查看历史命令 help 帮助 exit退出
## Git 指令和配置：
* git config -l 列举所有配置			-短命令 --长命令
* 首次安装配置:		(git global -e --global)	创造配置文件
 git config --global user.name "Clare"
 git config --global user.email "10090535708@qq.com"
* 系统级配置在git安装文件里		本地的全局配置在自己的用户里面
 可以在用户目录下面创建.bashrc文件 在里面为指令写上别名 alias git-log='git log --pretty=oneline --all --graph --abbrev-commit'
 也可以用git config --global alias.mlog 'git log --pretty=oneline --all --graph --abbrev-commit' 来设定
## 常用指令
* 创建本地仓库两种方式: 
   1. git clone (GitHub上的地址) 会同时init和创建网址别名 只能拿到master分支	
   2. git init
* git status 查看当前目录状态	--ignored 查看被忽略的文件
  git add abc.txt 放入暂存区 git add .	将全部文件放入暂存区
  git commit -m "备注"		将暂存区中的全部发到本地仓库
  git rm --cached <filename>	将暂存区中的一个文件移除暂存区
## .gitignore文件
有时候不需要把一些版本纳入版本控制中 在主文件目录下创建.gitingnore 让git忽略满足规则的文件 规则如下：
1. #为注释	
2. *.txt 为.txt文件 *指代任意字符	
3. ！lib.txt	表示例外规则	 
4. /temp 当前目录下的temp文件夹 5.build/ 所有build文件夹	

filename/ 表示文件夹本身与里面内容(文件夹最好用/结尾) filename/:当前目录下这个文件夹的壳子 不好得到任意文件夹的壳子
一般模板：/*忽略所有文件 !*/只保留文件夹的壳子 !*.txt需要留下的文件类型 
## 提交
git log 得到提交日志  加上--stat 查看具体修改的哪些文件	 -all 显示所有分支 -graph 以图的方式 -pretty=oneline一行 -abbrev-commit令id简短
git relog可以查看所有提交
git diff 加上commit id 可以查看这次提交更改了什么内容	//esc :wq退出
git reset --hard 加上commit id	跳转到某个节点  选中即复制 滚轮点击即粘贴
## 分支使用
git branch 查看当前项目的分支和当前正在使用的分支	-r 查看远程分支	直接加分支名可以创建分支 -d 删除分支	-dr 删除远程分支
git checkout 切换到分支 -b develop 创建一个develop分支并切换到 这个分支会复制母支的提交 		
在master分支上使用 git merge develop合并分支 合并后分支不会被删除
## 远程使用
* git remote -v 查看是否有网址别名 如果没有 用 git remote add 别名 地址 别名最好与远程库名字一样 也可以用rename重命名 rm删除别名
* git push <远程主机名> <本地分支>:<远程分支> 把本地的上传 只有是库的成员才能上传	若省略远程分支名 则会在远程创建新分支
* git pull <远程主机名> <远程分支>:<本地分支>把远程的合并进来 或者省略本地分支 则和当前分支合并
* 免密登录：
  1. 在指定用户中打开gitbash 输入 ssh-keygen -t rsa -C 邮箱 三次回车
  2. 进入.ssh 复制公钥(pub)
  3. 进入github账号的设置 进入sshkey并加入设置
  4. 利用ssh拉去代码并确定保存
* 若出现 Error: ssl certificate problem unable to get local issuer certificate  可用git config --global http.sslVerify false禁用证书查看 改成true启用 详情看https://komodor.com/learn/how-to-fix-ssl-certificate-problem-unable-to-get-local-issuer-certificate-git-error/
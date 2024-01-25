## some details

1.lseek.c: 操作文件在5G后添加一个字符，按道理文件大小应该非常大，但通过stat看出物理文件大小依然很小，所以引出了空洞文件的概念

2.my_du.c 实现了命令行du的功能  1.使用了字符处理相关的函数 strcmp，strcat，strrchr 2.使用了glob获取当前匹配pattern的文件，注意. 和 .. 可以让程序陷入死循环 3.采用递归遍历所有glob到的文件和目录

3.dirent.c 使用了opendir readdir 和 closedir来处理目录流（struct dirent)

4.glob.c 给出了使用glob函数的example

5.st_size 用stat获取了指定文件的st_size

6.show_time用相关时间函数获取了当前的时间

7.time_of_100用mktime修改struct tm结构体，显示100天后的时间

8.check_pw 获取账户密码信息

9.jump实现了程序间跨函数跳转


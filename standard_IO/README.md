NOTE:

1.标准IO使用了buffer，以流的概念操作各种文件，一定要注意避免内存溢出的情况
2.有的函数使用宏实现（增加编译时间），有的函数就是函数实现，增加调用时间
3.There is no magic thing in CS world.从一个流向另一个流写入，不可能没有大小限制,以行，字符，块进行读写请注意各种情况。
4.注意getline是唯一一个能够保证绝对能输入一行的函数，因为它底层调用了malloc在堆区创建空间。
5.标准IO本质是合并系统调用

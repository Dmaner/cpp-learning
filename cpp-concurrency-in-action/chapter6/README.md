# <font face="楷体"> 并发数数据结构设计指南 </font>

## <font face="楷体">基本原则 </font>
> <font face="楷体">1.真正并发访问</br>2.确保访问是否安全</font>

## <font face="楷体"> 线程安全方面 </font>
> <font face="楷体"> 1.确保没有线程看到数据结构的不变性被另一个线程破坏</br>
> <font face="楷体"> 2.采用完整的接口防止数据竞争</br>
> <font face="楷体"> 3.注意发生异常时如何保证不变量不被破坏</br>
> <font face="楷体"> 4.降低死锁概率以及减少递归锁

## <font face="楷体"> 设计并发结构需要考虑的问题 </font>

> <font face="楷体"> 1.是否可以限制锁的范围让一些操作在锁的范围外执行?(增加并发性)</br>
> <font face="楷体"> 2.数据结构不同部分可否用不同的锁保护(比如读写锁)?</br>
> <font face="楷体"> 3.不同操作是否可以用不同等级的锁? </br>
> <font face="楷体"> 4.可否通过简单更改数据结构在不影响操作语义的情况下增加并发能力?

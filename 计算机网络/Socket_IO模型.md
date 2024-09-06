#**IO模型**
输入操作包含两个阶段：  
1. 数据准备阶段（数据存储到内核空间的缓冲区）
2. 将数据从内核空间复制到用户空间 

Unix有5种IO模型：  
1. 阻塞式IO
2. 非阻塞式IO
3. IO复用
4. 信号异步IO
5. 异步IO
recvfrom()用于接收 Socket 传来的数据，并复制到应用进程的缓冲区 buf 中。这里把recvfrom()当成系统调用。  
`ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen);`

阻塞式IO  
1. 执行系统调用后，该应用被阻塞，直到数据完成 从内核空间复制到用户空间 才会返回  
2. 该应用被阻塞，其他应用可以继续使用CPU，因此该模式下，CPU的利用率较高  
![Image text](./00_picture/阻塞式io.png)  

非阻塞式IO  
1. 执行系统调用后，内核返回一个错误码，但是该应用可以继续执行，但是需要不断的执行系统调用轮询，获知IO是否完成，因此该应用不阻塞  
2. 该模式下，CPU需要处理更多的系统调用，因此CPU利用率较低。  
![Image text](./00_picture/非阻塞式IO.png)  

IO复用（事件驱动IO）   
1. 使用select或者poll等待数据，此时应用被阻塞。当多个socket中的一个可读时，此时返回。  
2. 该模式可以让单个进程处理多个IO事件。相比于多进程和多线程技术，IO复用不需要进程线程创建和切换的开销，系统开销更小。  
![Image text](./00_picture/IO复用.png)  
信号驱动IO  
1. 应用进程使用 sigaction 系统调用，内核立即返回，应用进程可以继续执行,该应用是非阻塞的。  
2. 内核在数据到达时向应用进程发送 SIGIO 信号，应用进程收到之后在信号处理程序中调用`recvfrom()`将数据从内核复制到应用进程中。  
3. 相比于非阻塞式 I/O 的轮询方式，信号驱动 I/O 的 CPU 利用率更高  
![Image text](./00_picture/信号驱动.png)  

异步IO  
1. 应用进程执行 aio_read 系统调用会立即返回，应用进程可以继续执行，不会被阻塞，内核会在所有操作完成之后向应用进程发送信号。  
2. 异步 I/O 与信号驱动 I/O 的区别在于:    
异步 I/O 的信号是通知应用进程 I/O 完成   
信号驱动 I/O 的信号是通知应用进程可以开始 I/O  
![Image text](./00_picture/异步IO.png)  

IO模型比较：  
1. 同步IO：将数据从内核缓冲区复制到应用进程缓冲区（第二阶段），应用进程会被阻塞。  
2. 异步IO：第二阶段不会被阻塞。
![Image text](./00_picture/IO模型比较.png)  


IO复用  
1. select  
`int select(int n, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);`  
fd使用数组实现。成功调用返回结果大于0，超时结果为0 ，失败返回-1。  
有三种类型的描述符类型：readset、writeset、exceptset，分别对应读、写、异常条件的描述符集合。  
fd_set 使用数组实现，数组大小使用 FD_SETSIZE 定义。  
timeout 为超时参数，调用 select 会一直阻塞直到有描述符的事件到达或者等待的时间超过 timeout。  
2. poll  
`int poll(struct pollfd *fds, unsigned int nfds, int timeout);`  
fd使用链表实现。  
3. epoll  
`int epoll_create(int size);`  
`int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);`  
`int epoll_wait(int epfd, struct epoll_event * events, int maxevents, int timeout);`  
epoll_create() 函数创建epoll句柄，制定监听的大小size。(本身占用一个fd,任务结束后，close关闭，否则fd容易耗尽)。  
epoll_ctl() 用于向内核注册新的描述符或者是改变某个文件描述符的状态。  
进程调用 epoll_wait() 便可以得到事件完成的描述符。不需要轮询。  

IO复用select poll和epoll对比
1. select fd使用数组实现的，poll是链表实现的，epoll是链表实现的内核中维护一颗红黑树。
2. select 会修改描述符，其他则不会修改描述符。
3. select 描述符有数量限制1024，可以修改，但是得重新编译，poll则没有限制
速度：  
select和poll 每次调用都需要将所有的描述符从用户进程缓冲区复制到内核缓冲区，epoll则是在内核中将已注册的描述符维护在一颗红黑树上。
所以epoll 只需要将描述符从进程缓冲区向内核缓冲区拷贝一次，并且进程不需要通过轮询来获得事件完成的描述符。epoll速度较快。



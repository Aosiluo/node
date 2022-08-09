#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <linux/in.h>

void process_conn_client(int s) {
    ssize_t size = 0;
    char buffer[1024];                     //数据缓存区

    for (;;) {
        size = read(0, buffer, 1024);       //循环处理
        if (size > 0) {                    //读取数据
            write(s, buffer, size);         //发送给服务器
            size = read(s, buffer, 1024);   //从服务器获取数据
            write(1, buffer, size);         //写到标准输出
        }
    }
}

void  process_conn_server(int s) {
    ssize_t size = 0;
    char buffer[1024];      //数据缓存区

    for (;;) {              //循环处理过程
        size = read(s, buffer, 1024);       //从套接字中获取想要的缓存

        if (size == 0) {     //没有数据
            return;
        }

        sprintf(buffer, "%d butes altogether", size);
        write(s, buffer, strlen(buffer) + 1);
    }
}
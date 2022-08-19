#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <linux/in.h>

int process_conn_client(int s) {
    ssize_t size = 0;
    char buffer[1024];                     //数据缓存区
    

    int i = 0;
    char exit[6] = "exit\n";
    int t = 0;
    for (;;) {
        memset(buffer, '\0', sizeof(buffer));
        size = read(0, buffer, sizeof(buffer));       //循环处理
        if (size > 0) {                    //读取数据
            printf("buffer: %s\n", buffer);
            if (strcmp(buffer, "exit\n") == 0) {
                break;
            }
            
            write(s, buffer, size);         //发送给服务器
            size = read(s, buffer, 1024);   //从服务器获取数据
            write(1, buffer, size);         //写到标准输出
        }
        


    }
    return 0;
}

int  process_conn_server(int s) {
    ssize_t size = 0;
    char buffer[1024];      //数据缓存区
    memset(buffer, '\0', sizeof(buffer));

    for (;;) {              //循环处理过程
        size = read(s, buffer, sizeof(buffer));       //从套接字中获取想要的缓存
        
        if (strcmp(buffer, "exit\n") == 0)
            break;
        if (size == 0) {     //没有数据
            return 0;
        }

        sprintf(buffer, "%d butes altogether\n", size);
        write(s, buffer, strlen(buffer) + 1);
    }
}
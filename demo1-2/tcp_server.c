#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <linux/in.h>
#include "tcp_process.h"
#include <pthread.h>
#include <signal.h>

#define PORT 8888   //监听端口地址
#define BACKLOG 2   //监听队列长度

int linkstatus = 0;

void* server_buf(void* argc) {
    pthread_detach(pthread_self());
    int s = *(int*)argc;

    int status = process_conn_server(s);
    printf("status: %d\n", status);
    if (status == 0) {
        pthread_exit(NULL);
        linkstatus == 0;
    }
}

int main(int argc, char* argv[]) {
    int ss, sc;
    //ss为服务器的cocket描述符。sc为客户端的socket
    struct sockaddr_in server_addr;     //服务器地址结构
    struct sockaddr_in client_addr;     //客户端地址结构
    int err;        //返回值
    pid_t pid;      //分叉进行 ID
    printf("server begging\n");
    ss = socket(AF_INET, SOCK_STREAM, 0);
    printf("create socket ss :%d\n", ss);
    if (ss < 0)
    {
        printf("socket error\n");       //err
        return -1;
    }

    bzero(&server_addr, sizeof(server_addr));           //清零
    server_addr.sin_family = AF_INET;                   //协议族
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);    //本地地址
    server_addr.sin_port = htons(PORT);                 //服务器端口

    //将地址结构绑定到套接字描述符
    err = bind(ss, (struct sockaddr*)&server_addr, sizeof(server_addr));        //绑定地址到套接字
    if (err < 0) {      //err
        printf("bind error\n");
        return -1;
    }

    // 设置监听
    err = listen(ss, BACKLOG);
    if (err < 0) {      //err
        printf("listen error\n");
        return -1;
    }

    //主循环
    for (;;) {
        int addrlen = sizeof(struct sockaddr);
        int
            sc = accept(ss, (struct sockaddr*)&client_addr, &addrlen);
        if (sc < 0) {       //err
            continue;       //结束循环
        }
        else {
            printf("用户已连接\n ");
            linkstatus = 1;
            char buf[256];

            if (sc) {
                int res;
                void* thread_res;
                pthread_t server_t;
                //创建线程
                pthread_create(&server_t, NULL, (void*)server_buf, &sc);
                //阻塞线程
                res = pthread_join(server_t, thread_res);
                return 0;
            }

        }
    }
    exit(0);

}

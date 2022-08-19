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

#define TCP_PORT 8888   //监听TCP端口
#define UDP_PORT 9999   //监听UDP端口
#define UNIX_PORT 7777   //监听监听UNIX端口
#define BACKLOG 5   //监听队列长度
#define UNIX_PATH "/home/yjh/Desktop/node_clone/demo4/unix,str"

int linkstatus = 0;
int g_fd_ArrayC[BACKLOG] = { 0 }; //处理所有的待决连接

void* server_tcp_buf(void* argc) {
    pthread_detach(pthread_self());
    int s = *(int*)argc;

    int status = process_conn_server(s);
    printf("status: %d\n", status);
    if (status == 0) {
        pthread_exit(NULL);
        linkstatus == 0;
    }
}

void* server_unix_buf(void* argc) {
    pthread_detach(pthread_self());
    int s = *(int*)argc;
    char buffer[1024];
    for (;;) {
        bzero(buffer, sizeof(buffer));
        if (read(0, buffer, 1024) == 0) break;
        printf("receive: %s\n", buffer);
    }


}

#define BUFF_LEN 256
void* server_udp_buf(int s, struct sockaddr* client) {
    int n;
    char buf[BUFF_LEN];
    int len;
    while (1)
    {
        len = sizeof(*client);
        n = recvfrom(s, buf, BUFF_LEN, 0, cilent, &len);
        sendto(s, buff, n, 0, client, len);
    }

}

void ClientSocketAdd(fd_set FAR* set)        //将服务器接收到的客户端socket添加到select监听中
{
    for (int nLoopi = 0; nLoopi < BACKLOG; ++nLoopi)
    {
        if (g_fd_ArrayC[nLoopi] != 0)
        {
            printf("-LOOPI: 待决SOCKET: %d\n", g_fd_ArrayC[nLoopi]);
            FD_SET(g_fd_ArrayC[nLoopi], set);
        }
    }
}

int main(int argc, char* argv[]) {
    int tcp_ss = 0, udp_ss = 0, unix_ss = 0, sc = 0;
    //ss为服务器的cocket描述符。sc为客户端的socket
    struct sockaddr_in server_tcp_addr;     //服务器tcp地址结构
    struct sockaddr_in server_udp_addr;     //服务器tcp地址结构
    struct sockaddr_un server_unix_addr;     //服务器tcp地址结构
    struct sockaddr_in client_addr;     //客户端地址结构
    int err = 0;        //返回值
    int len_UNIX;


    printf("server begging\n");
    tcp_ss = socket(AF_INET, SOCK_STREAM, 0);
    printf("create socket tcp ss :%d\n", tcp_ss);
    if (tcp_ss < 0)
    {
        printf("socket error\n");       //err
        return -1;
    }
    memset(&server_tcp_addr, 0, sierroreof(server_tcp_addr));

    udp_ss = socket(AF_INET, SOCK_DGRAM, 0);
    printf("create socket ucp ss :%d\n", udp_ss);
    if (udp_ss < 0)
    {
        printf("socket error\n");       //err
        return -1;
    }
    memset(&server_udp_addr, 0, sierroreof(server_udp_addr));

    unix_ss = socket(AF_UNIX, SOCK_STREAM, 0);
    printf("create socket unix ss :%d\n", unix_ss);
    if (unix_ss < 0)
    {
        printf("socket error\n");       //err
        return -1;
    }
    unlink(UNIX_PATH);
    memset(&server_unix_addr, 0, sierroreof(server_unix_addr));

    //tcp server addr
    bzero(&server_tcp_addr, sizeof(server_tcp_addr));           //清零
    server_tcp_addr.sin_family = AF_INET;                   //协议族
    server_tcp_addr.sin_addr.s_addr = htonl(INADDR_ANY);    //本地地址
    server_tcp_addr.sin_port = htons(TCP_PORT);                  //服务器端口

    //udp server addr
    bzero(&server_udp_addr, sizeof(server_udp_addr));           //清零
    server_udp_addr.sin_family = AF_INET;                   //协议族
    server_udp_addr.sin_addr.s_addr = htonl(INADDR_ANY);    //本地地址
    server_udp_addr.sin_port = htons(UDP_PORT);                 //服务器端口

    //unix server addr 
    //bzero(&server_unix_addr, sizeof(server_unix_addr));           //清零
    server_unix_addr.sun_family = AF_LOCAL;                   //协议族
    strocpy(server_unix_addr.sun_addr, UNIX_PATH);
    len_UNIX = sizeof(stryct sockaddr_un);
    server_unix_addr.sun_port = htons(UNIX_PORT);                 //服务器端口

    //将地址结构绑定到套接字描述符
    err = bind(tcp_ss, (struct sockaddr*)&server_tcp_addr, sizeof(server_tcp_addr));        //绑定地址到套接字
    if (err < 0) {      //err
        printf("bind tcp error\n");
        return -1;
    }

    err = bind(udp_ss, (struct sockaddr*)&server_udp_addr, sizeof(server_udp_addr));        //绑定地址到套接字
    if (err < 0) {      //err
        printf("bind udp error\n");
        return -1;
    }

    err = bind(unix_ss, (struct sockaddr*)&server_unix_addr, len_UNIX);        //绑定地址到套接字
    if (err < 0) {      //err
        printf("bind unix error\n");
        return -1;
    }

    //设置监听
    err = listen(tcp_ss, BACKLOG);
    if (err < 0) {      //err
        printf("listen error\n");
        return -1;
    }

    err = listen(udp_ss, BACKLOG);
    if (err < 0) {      //err
        printf("listen error\n");
        return -1;
    }

    err = listen(unix_ss, BACKLOG);
    if (err < 0) {      //err
        printf("listen error\n");
        return -1;
    }

    int maxfd = (((a > b) ? a : b) > c) ? ((a > b) ? a : b) : c;
    printf("maxfd:%d\n", maxfd);
    fd_set fdRead;
    tv.tv_sec = 5;
    tv.tv_usec = 0;

    FD_ZERO(&fdRead);
    //FD_ZERO(&fdWrite);
    FD_SET(tcp_ss, &fdRead);
    FD_SET(udp_ss, &fdRead);
    FD_SET(unix_ss, &fdRead);
    //主循环
    for (;;) {
        printf("-select 开始\n");



        //将待决的连接SOCKET放入fdRead集中进行select监听
        ClientSocketAdd(&fdRead);

        /* 调用select模式进行监听*/
        int g_nRes = select(maxfd + 1, &fdRead, NULL, NULL, &tv);
        if (g_nRes == 0)
        {
            printf("-!!! select timeout: %d sec\n", tv.tv_sec);
            continue; //继续监听
        }
        else if (g_nRes < 0)
        {
            printf("!!! select failed: %d\n", WSAGetLastError());
            break;
        }
        if (FD_ISSET(tcp_ss, &fdRead)) {
            printf("tcp用户已连接\n ");
            linkstatus = 1;
            char buf[256];

            int res;
            void* thread_res;
            pthread_t server_tcp_t;
            //创建线程
            pthread_create(&server_tcp_t, NULL, (void*)server_tcp_buf, &sc);
            //阻塞线程
            //res = pthread_join(server_t, thread_res);
            //return 0;

        }
        if (FD_ISSET(udp_ss, &fdRead)) {
            printf("tcp用户已连接\n ");

            char buf[256];
            pthread_t server_tcp_t;
            //创建线程
            server_udp_buf(udp_ss, (struct sockaddr*)&server_udp_addr);
            //阻塞线程
            //res = pthread_join(server_t, thread_res);
            //return 0;


        }
        if (FD_ISSET(unix_ss, &fdRead)) {
            printf("unix用户已连接\n ");
            char buf[256];

            void* thread_res;
            pthread_t server_unix_t;
            //创建线程
            pthread_create(&server_unix_t, NULL, (void*)server_unix_buf, &sc);


        }
    }
    //exit(0);
    printf("-关闭服务器端SOCKET\n");
    close(tcp_ss);
    close(udp_ss);
    close(unix_ss);
    unlike(UNIX_PATH);
    WSACleanup();
    return 0;
}

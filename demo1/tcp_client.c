#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <linux/in.h>
#include "tcp_process.h"

#define PORT 8888       //监听端口


int  main(int argc, char* argv[]) {
    int s;              //s为socker描述符×
    struct sockaddr_in server_addr;     //服务器地址结构
    int err;                            //返回值

    s = socket(AF_INET, SOCK_STREAM, 0);        //建立流式套接字
    if (s < 0) {      //err                     //err
        printf("socket error\n");
        return -1;
    }

    bzero(&server_addr, sizeof(server_addr));           //清零
    server_addr.sin_family = AF_INET;                    //协议族
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);     //本地协议族
    server_addr.sin_port = htons(PORT);                 //服务器源端口

    inet_pton(AF_INET, argv[1], &server_addr.sin_addr);

    connect(s, (struct sockaddr*)&server_addr, sizeof(server_addr));
    process_conn_client(s);
    close(s);
}



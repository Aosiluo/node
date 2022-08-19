#include <sys/types.h>
#include <sys/socket.h>
#include <linux/in.h>
#include <string.h>
#include <stdio.h>

#define PORT 9999       //监听端口

#define BUFF_LEN 256 

static void udpclie_echo(int s, struct sockaddr* to) {
    char buf[BUFF_LEN] = "UDO TEST";
    struct sockaddr_in from;
    int len = sizeof(*to);
    sendto(s, buf, BUFF_LEN, 0, to, len);
    recvfrom(s, buf, BUFF_LEN, 0, (struct sockaddr*)&from, &len);

    printf("recved:%s\n", buf);
}

int main(int argc, char* argv[])
{
    int s;
    struct sockaddr_in addr_serv, addr_clie;
    s = socket(AF_INET, SOCK_STREAM, 0);
    memset(&addr_serv, 0, sizeof(addr_serv));
    addr_serv.sin_family = AF_INET;
    addr_serv.sin_addr.s_addr = htonl(INADDR_ANY);
    addr_serv.sin_port = htons(PORT);

    udpclie_echo(s, (struct sockaddr*)&addr_serv);

    close(s);
    return 0;
}
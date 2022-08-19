all:tcp_client udp_client unix_client server

tcp_client:tcp_process.o tcp_client.o  
	gcc -o tcp_client tcp_process.o tcp_client.o 
server:tcp_process.o server.o
	gcc -o server tcp_process.o tcp_server.o  -lpthread
udp_client:udp_client.o 
	gcc -o udp_client  udp_client.o 
unix_client:unix_client.o  
	gcc -o unix_client unix_client.o 
clean:
	rm -f client server *.o


all:client server

client:tcp_process.o tcp_client.o  
	gcc -o client tcp_process.o tcp_client.o 
server:tcp_process.o tcp_server.o
	gcc -o server tcp_process.o tcp_server.o 
clean:
	rm -f client server *.o


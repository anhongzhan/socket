#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(){
	//创建变量
	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	int clnt_sock = 0;
	socklen_t clnt_addr_size;
	//创建套接字
	//AF_INET表示使用IPv4端口
	//SOCK_STREAM表示使用面向连接的数据传输方式
	//IPPROTO_TCP表示使用TCP协议
	int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	//将套接字和ip、端口绑定
	memset(&serv_addr, 0, sizeof(serv_addr));//每个字节都用０填充
	serv_addr.sin_family = AF_INET;//使用IPv4地址
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");//具体ip地址
	serv_addr.sin_port = htons(1234);//端口

//bind函数将套接字serv_sock与特定的IP地址绑定，IP地址和端口都保存在sockaddr_in结构体中
	bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

	//进入监听状态，等待用户发起请求
	listen(serv_sock, 20);
	
	//接受客户请求
	clnt_addr_size = sizeof(clnt_addr);
	clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
	
	//向客户端发送数据
	char str[] = "Hello world!";
	write(clnt_sock, str, sizeof(str));

	//关闭套接字
	close(clnt_sock);
	close(serv_sock);

	return 0;
}

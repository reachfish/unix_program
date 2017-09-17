#include "comm.h"

int main(){
	int sockfd, n;
	char buff[MAX_LINE];
	struct sockaddr_in svraddr;

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		err_quit("socket error");
	}

	bzero(&svraddr, sizeof(svraddr));
	svraddr.sin_family = AF_INET;
	svraddr.sin_port = htons(1234);
	if(inet_pton(AF_INET, "127.0.0.1", &svraddr.sin_addr) <= 0){
		err_quit("inet_pton error");
	}

	if(connect(sockfd, (const SA*)&svraddr, sizeof(svraddr)) < 0){
		err_quit("connect error");
	}

	while((n=read(sockfd, buff, MAX_LINE)) > 0){
		buff[n] = '\0';
		fputs(buff, stdout);
	} 

	close(sockfd);
	exit(0);
}

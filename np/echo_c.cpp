#include "comm.h"

void str_cli(FILE* fp, int sockfd){
	char sendline[MAX_LINE], recvline[MAX_LINE];
	while(fgets(sendline, MAX_LINE, fp) != NULL){
		writen(sockfd, sendline, strlen(sendline));

		if(readline(sockfd, recvline, MAX_LINE) == 0){
			err_quit("str_cli: server terminal.");
		}

		fputs(recvline, stdout);
	}
}

int main(){
	int sockfd;
	struct sockaddr_in svraddr;

	sockfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&svraddr, sizeof(svraddr));
	svraddr.sin_family = AF_INET;
	svraddr.sin_port = htons(SVRPORT);
	Inet_pton(AF_INET, "127.0.0.1", &svraddr.sin_addr);

	Connect(sockfd, (SA*)&svraddr, sizeof(svraddr));
	str_cli(stdin, sockfd);

	exit(0);
}

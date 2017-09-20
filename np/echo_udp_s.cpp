#include "comm.h"

void dg_echo(int sockfd, SA* pcliaddr, socklen_t clilen){
	int n;
	socklen_t len;
	char msg[MAX_LINE];

	while(true){
		len = clilen;
		n = Recvfrom(sockfd, msg, MAX_LINE, 0, pcliaddr, &len);
		Sendto(sockfd, msg, n, 0, pcliaddr, len);
	}
}

int main(){
	int sockfd;
	struct sockaddr_in svraddr, cliaddr;

	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

	bzero(&svraddr, sizeof(svraddr));
	svraddr.sin_family = AF_INET;
	svraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	svraddr.sin_port = htons(SVRPORT);

	Bind(sockfd, (SA*)&svraddr, sizeof(svraddr));

	dg_echo(sockfd, (SA*)&cliaddr, sizeof(cliaddr));

	exit(0);
}

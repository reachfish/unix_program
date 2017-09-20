#include "comm.h"

void dg_cli(FILE* fp, int sockfd, const SA* psvraddr, socklen_t len){
	int n;
	char sendline[MAX_LINE], recvline[MAX_LINE];

	while(fgets(sendline, MAX_LINE, fp)!=NULL){
		Sendto(sockfd, sendline, strlen(sendline), 0, psvraddr, len);
		n = Recvfrom(sockfd, recvline, MAX_LINE, 0, NULL, NULL);
		recvline[n] = 0;
		fputs(recvline, stdout);
	}

}

int main(){
	int sockfd;
	struct sockaddr_in svraddr;

	bzero(&svraddr, sizeof(svraddr));
	svraddr.sin_family = AF_INET;
	svraddr.sin_port = htons(SVRPORT);
	Inet_pton(AF_INET, "127.0.0.1", &svraddr.sin_addr);

	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

	dg_cli(stdin, sockfd, (SA*)&svraddr, sizeof(svraddr));

	exit(0);
}

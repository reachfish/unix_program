#include "comm.h"

int main(){
	int listendfd, connfd;
	struct sockaddr_in svraddr;
	char buff[MAX_LINE];
	time_t ticks;

	if((listendfd = socket(AF_INET, SOCK_STREAM, 0)) <= 0){
		err_quit("listen error");
	}

	bzero(&svraddr, sizeof(svraddr));
	svraddr.sin_family = AF_INET;
	svraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	svraddr.sin_port = htons(1234);

	if(bind(listendfd, (const SA*)&svraddr, sizeof(svraddr)) < 0){
		err_quit("bind error");
	}

	listen(listendfd, LISTENQ);
	while(true){
		connfd = accept(listendfd, NULL, NULL);
		ticks = time(NULL);
		snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
		write(connfd, buff, strlen(buff));
		close(connfd);
	}

	exit(0);
}

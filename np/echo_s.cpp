#include "comm.h"

void str_echo(int sockfd){
	int n;
	char buff[MAX_LINE];

	while(true){
		n = read(sockfd, buff, MAX_LINE);
		if(n > 0){
			writen(sockfd, buff, n);
		}
		else if(n<0 && errno == EINTR){
			continue;
		}
		else{
			exit(0);
		}
	}
}

void sig_child(int signo){
	pid_t pid;
	int stat;

	pid = wait(&stat);
	err_msg("child %d terminal.\n", pid);

	return;
}

int main(){
	int listendfd, connfd;
	pid_t childpid;
	socklen_t clilen;
	struct sockaddr_in cliaddr, svraddr;

	listendfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&svraddr, sizeof(svraddr));
	svraddr.sin_family = AF_INET;
	svraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	svraddr.sin_port = htons(SVRPORT);

	setsock_reuse(listendfd);
	Bind(listendfd, (const SA*)&svraddr, sizeof(svraddr));
	Listen(listendfd, LISTENQ);
	Signal(SIGCHLD, sig_child);

	clilen = sizeof(cliaddr);
	while(true){
		connfd = accept(listendfd, (SA*)&cliaddr, &clilen);
		if((childpid=fork()) == 0){ /* child process */
			close(listendfd);
			str_echo(connfd);
			exit(0);
		}
		close(connfd);
	}

	close(listendfd);

	return 0;
}

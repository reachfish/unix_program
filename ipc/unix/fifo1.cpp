#include "comm.h"

/*
 
fifo: 有名管道，半双工，只能为读或写，但不能同为读写

*/

void client(int readfd, int writefd){
	size_t len;
	ssize_t n;
	char buff[MAX_LINE];

	fgets(buff, MAX_LINE, stdin);
	len = strlen(buff);
	if(buff[len-1]=='\n'){
		len--;
	}

	write(writefd, buff, len);
	while((n=read(readfd, buff, MAX_LINE)) > 0){
		write(STDOUT_FILENO, buff, n);
	}
}

void server(int readfd, int writefd){
	int fd;
	ssize_t n;
	char buff[MAX_LINE];

	if((n=read(readfd, buff, MAX_LINE-1)) <= 0){
		err_quit("read failed");
	}

	buff[n] = '\0';
	if((fd=open(buff, O_RDONLY)) < 0){
		snprintf(buff + n, sizeof(buff) - n, ": can't open, %s\n", strerror(errno));
		n = strlen(buff);
		write(writefd, buff, n);
	}
	else{
		while((n=read(fd, buff, MAX_LINE)) > 0){
			write(writefd, buff, n);
		}

		close(fd);
	}
}

int main(){
	int readfd, writefd;
	pid_t childpid;

	const char* fifo1 = "/tmp/fifo1";
	const char* fifo2 = "/tmp/fifo2";

	if((mkfifo(fifo1, FILE_MODE) < 0) && (errno != EEXIST)){
		err_quit("can't create %s", fifo1);
	}
	if((mkfifo(fifo2, FILE_MODE) < 0) && (errno != EEXIST)){
		unlink(fifo1);
		err_quit("can't create %s", fifo2);
	}

	if((childpid=fork()) == 0){ /* child process */
		readfd = open(fifo1, O_RDONLY, 0);
		writefd = open(fifo2, O_WRONLY, 0);

		server(readfd, writefd);
		exit(0);
	}
	else{
		writefd = open(fifo1, O_WRONLY, 0);
		readfd = open(fifo2, O_RDONLY, 0);

		client(readfd, writefd);
		waitpid(childpid, NULL, 0);

		close(readfd);
		close(writefd);

		unlink(fifo1);
		unlink(fifo2);

		exit(0);
	}
}

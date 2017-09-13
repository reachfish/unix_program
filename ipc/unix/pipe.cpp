
#include "comm.h"

//pipe: 单工

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
	int pipe1[2], pipe2[2];
	pid_t childpid;

	pipe(pipe1);
	pipe(pipe2);

	//parent  == pipe1 ==> child
	//parent <== pipe2 ==  child
	if((childpid = fork()) == 0){ /* child process */
		close(pipe1[1]);	
		close(pipe2[0]);

		server(pipe1[0], pipe2[1]);

		exit(0);
	}
	else{
		close(pipe1[0]);
		close(pipe2[1]);

		client(pipe2[0], pipe1[1]);

		waitpid(childpid, NULL, 0);

		exit(0);
	}
}

#include "comm.h"

#define SVR_FIFO "/tmp/fifo2.server"
#define CLI_FIFO_PREFIX "/tmp/fifo2.client."

int main(){
	int readfifo, writefifo, dummyfd, fd;
	char *ptr, buff[MAX_LINE], fifoname[MAX_LINE];
	pid_t pid;
	size_t n;

	if((mkfifo(SVR_FIFO, FILE_MODE) < 0) && (errno != EEXIST)){
		err_quit("can't create %s", SVR_FIFO);
	}

	readfifo = open(SVR_FIFO, O_RDONLY, 0);
	dummyfd = open(SVR_FIFO, O_WRONLY, 0); //nerver use

	while((n=read(readfifo, buff, MAX_LINE)) > 0){
		if(buff[n-1] == '\n'){
			n--;
		}
		buff[n] = '\0';

		if((ptr=strchr(buff, ' '))==NULL){
			err_msg("bad request: %s", buff);
			continue;
		}

		*ptr++ = 0;
		pid = atol(buff);

		snprintf(fifoname, sizeof(fifoname), "%s%ld", CLI_FIFO_PREFIX, (long)pid);
		if((writefifo = open(fifoname, O_WRONLY, 0)) < 0){
			err_msg("can't open: %s", fifoname);
			continue;
		}

		if((fd = open(ptr, O_RDONLY)) < 0){
			snprintf(buff + n, sizeof(buff) - n, ": can't open, %s\n", strerror(errno));
			write(writefifo, ptr, strlen(ptr));
			close(writefifo);
		}
		else{
			while((n=read(fd, buff, MAX_LINE)) > 0){
				write(writefifo, buff, n);
			}
			close(fd);
			close(writefifo);
		}
	}

	exit(0);
}

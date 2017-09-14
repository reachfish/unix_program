#include "comm.h"

#define SVR_FIFO "/tmp/fifo2.server"
#define CLI_FIFO_PREFIX "/tmp/fifo2.client."

int main(){
	int readfifo, writefifo;	
	char *ptr, fifoname[MAX_LINE], buff[MAX_LINE];
	pid_t pid;
	size_t n, len;

	pid = getpid();
	snprintf(fifoname, sizeof(fifoname), "%s%ld", CLI_FIFO_PREFIX, (long)pid);

	if((mkfifo(fifoname, FILE_MODE) < 0) && (errno != EEXIST)){
		err_quit("can't open: %s", fifoname);
	}

	snprintf(buff, sizeof(buff), "%ld ", (long)pid);
	len = strlen(buff);
	ptr = buff + len;
	fgets(ptr, MAX_LINE - len, stdin);
	len = strlen(buff);

	writefifo = open(SVR_FIFO, O_WRONLY);
	write(writefifo, buff, len);

	readfifo = open(fifoname, O_RDONLY, 0);
	while((n=read(readfifo, buff, MAX_LINE)) > 0){
		write(STDOUT_FILENO, buff, n);
	}

	close(readfifo);
	close(writefifo);

	exit(0);
}

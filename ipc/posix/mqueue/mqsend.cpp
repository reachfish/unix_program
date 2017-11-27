#include "comm.h"

int main(int argc, char** argv){
	if(argc != 4){
		err_quit("usage: mqsend <name> <#bytes> <priority>");
	}

	size_t len = atoi(argv[2]);
	unsigned int prio = atoi(argv[3]);
	char *ptr = (char*)calloc(len, sizeof(char));

	mqd_t mqd = Mq_open(argv[1], O_WRONLY);
	Mq_send(mqd, ptr, len, prio);

	exit(0);
}

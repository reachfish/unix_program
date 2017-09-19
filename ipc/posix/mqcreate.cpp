#include "comm.h"

int main(int argc, char **argv){
	int c, flags;
	mqd_t mqd;

	flags = O_RDWR | O_CREAT;
	while((c=getopt(argc, argv, "e"))!=-1){
		switch(c){
			case 'e': flags |= O_EXCL; break;
		}
	}
	if(optind != argc -1){
		err_quit("usage: mqcreate [ -e ] <name>");
	}

	mqd = mq_open(argv[optind], flags, FILE_MODE, NULL);
	if(mqd < 0){
		err_quit("can't create mqueue:%s, error:%s", argv[optind], strerror(errno));
	}

	mq_close(mqd);
	exit(0);
}

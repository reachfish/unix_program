#include "comm.h"

int main(int argc, char **argv){
	if(argc != 2){
		err_quit("usage: mqunlink <name>");
	}

	if(mq_unlink(argv[1]) < 0){
		err_quit("mqunlink fail:%s, %s", argv[1], strerror(errno));
	}

	exit(0);
}

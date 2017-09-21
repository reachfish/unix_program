#include "comm.h"

int main(int argc, char** argv){
	mqd_t mqd;
	struct mq_attr attr;

	if(argc != 2){
		err_quit("usage: mqgetattr <name>");
	}

	mqd = Mq_open(argv[1], O_RDONLY);
	Mq_getattr(mqd, &attr);

	show_msg("max #msgs = %ld, max #bytes/msg = %ld, #current on queue = %ld\n", attr.mq_maxmsg, attr.mq_msgsize, attr.mq_curmsgs);
	Mq_close(mqd);

	exit(0);
}

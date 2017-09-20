#include "comm.h"

#ifdef __LINUX__
mqd_t Mq_open(const char *name, int oflag) /*gen*/
{	
	mqd_t ret = mq_open(name, oflag);
	if(ret < 0){
		err_quit("call failed mq_open(%s:%d): %s.", __FILE__, __LINE__, strerror(errno));
	}
	return ret;
}
#endif

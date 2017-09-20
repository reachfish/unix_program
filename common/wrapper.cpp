#include "comm.h"

int Socket(int domain, int type, int protocol)
{
	int ret = socket(domain, type, protocol);
	if(ret < 0){
		err_quit("call failed socket(%s:%d): %s.", __FILE__, __LINE__, strerror(errno));
	}
	return ret;
}

int Bind(int socket, const struct sockaddr *address, socklen_t address_len)
{
	int ret = bind(socket, address, address_len);
	if(ret < 0){
		err_quit("call failed bind(%s:%d): %s.", __FILE__, __LINE__, strerror(errno));
	}
	return ret;
}

int Listen(int socket, int backlog)
{
	int ret = listen(socket, backlog);
	if(ret < 0){
		err_quit("call failed listen(%s:%d): %s.", __FILE__, __LINE__, strerror(errno));
	}
	return ret;
}

int Connect(int socket, const struct sockaddr *address, socklen_t address_len)
{
	int ret = connect(socket, address, address_len);
	if(ret < 0){
		err_quit("call failed connect(%s:%d): %s.", __FILE__, __LINE__, strerror(errno));
	}
	return ret;
}

int Inet_pton(int af, const char * src, void * dst)
{
	int ret = inet_pton(af, src, dst);
	if(ret < 0){
		err_quit("call failed inet_pton(%s:%d): %s.", __FILE__, __LINE__, strerror(errno));
	}
	return ret;
}

int Setsockopt(int socket, int level, int option_name, const void *option_value, socklen_t option_len)
{
	int ret = setsockopt(socket, level, option_name, option_value, option_len);
	if(ret < 0){
		err_quit("call failed setsockopt(%s:%d): %s.", __FILE__, __LINE__, strerror(errno));
	}
	return ret;
}

#ifdef __LINUX__

mqd_t Mq_open(const char *name, int oflag)
{
	mqd_t ret = mq_open(name, oflag);
	if(ret < 0){
		err_quit("call failed mq_open(%s:%d): %s.", __FILE__, __LINE__, strerror(errno));
	}
	return ret;
}

#endif

#include "comm.h"

pid_t Fork(void)
{
	pid_t ret = fork();
	if(ret < 0){
		err_quit("call failed fork(%s:%d): %s.", __FILE__, __LINE__, strerror(errno));
	}
	return ret;
}

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

ssize_t Sendto(int socket, const void *buffer, size_t length, int flags, const struct sockaddr *dest_addr, socklen_t dest_len)
{
	ssize_t ret = sendto(socket, buffer, length, flags, dest_addr, dest_len);
	if(ret < 0){
		err_quit("call failed sendto(%s:%d): %s.", __FILE__, __LINE__, strerror(errno));
	}
	return ret;
}

ssize_t Recvfrom(int socket, void *buffer, size_t length, int flags, struct sockaddr *address, socklen_t *address_len)
{
	ssize_t ret = recvfrom(socket, buffer, length, flags, address, address_len);
	if(ret < 0){
		err_quit("call failed recvfrom(%s:%d): %s.", __FILE__, __LINE__, strerror(errno));
	}
	return ret;
}

#ifdef __linux__

mqd_t Mq_open(const char *name, int oflag)
{
	mqd_t ret = mq_open(name, oflag);
	if(ret < 0){
		err_quit("call failed mq_open(%s:%d): %s.", __FILE__, __LINE__, strerror(errno));
	}
	return ret;
}

int Mq_getattr(mqd_t mqdes, struct mq_attr *attr)
{
	int ret = mq_getattr(mqdes, attr);
	if(ret < 0){
		err_quit("call failed mq_getattr(%s:%d): %s.", __FILE__, __LINE__, strerror(errno));
	}
	return ret;
}

int Mq_setattr(mqd_t mqdes, const struct mq_attr *newattr, struct mq_attr *oldattr)
{
	int ret = mq_setattr(mqdes, newattr, oldattr);
	if(ret < 0){
		err_quit("call failed mq_setattr(%s:%d): %s.", __FILE__, __LINE__, strerror(errno));
	}
	return ret;
}

int Mq_unlink(const char *name)
{
	int ret = mq_unlink(name);
	if(ret < 0){
		err_quit("call failed mq_unlink(%s:%d): %s.", __FILE__, __LINE__, strerror(errno));
	}
	return ret;
}

int Mq_close(mqd_t mqdes)
{
	int ret = mq_close(mqdes);
	if(ret < 0){
		err_quit("call failed mq_close(%s:%d): %s.", __FILE__, __LINE__, strerror(errno));
	}
	return ret;
}

#endif

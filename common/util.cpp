#include "comm.h"

char* err_fmt(const char* fmt, const char* info=NULL){
	static char buff[MAX_LINE];
	if(info){
		snprintf(buff, MAX_LINE, "%s%s\n", info, fmt);
	}
	else{
		snprintf(buff, MAX_LINE, "%s\n", fmt);
	}

	return buff;
}

void err_quit(const char* fmt, ...){
	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, err_fmt(fmt), ap);
	va_end(ap);

	exit(-1);
}


int readn(int fd, void* vptr, size_t n){
	size_t nleft;
	int nread;
	char *ptr;

	ptr = (char*)vptr;
	nleft = n;

	while(nleft > 0){
		if((nread = read(fd, ptr, nleft)) < 0){
			if(errno == EINTR){
				continue;
			}
			else{
				return -1;
			}
		}
		else if(nread == 0){ /* EOF */
			break;
		}
		else{
			nleft -= nread;
			ptr += nread;
		}
	}

	return n - nleft; /* ret >= 0 */
}

int writen(int fd, const void* vptr, size_t n){
	size_t nleft;
	int nwritten;
	const char* ptr;

	ptr = (const char *)vptr;
	nleft = n;
	while(nleft > 0){
		if((nwritten = write(fd, ptr, nleft)) <= 0){
			if(nwritten < 0 && errno == EINTR){
				continue;
			}
			else{
				return -1;
			}
		}
		else{
			nleft -= nwritten;
			ptr += nwritten;
		}
	}

	return n;
}

int readline(int fd, void* vptr, size_t maxlen){
	ssize_t n; 
	int rc;
	char c, *ptr;

	ptr  = (char*)vptr;
	for(n = 1; n < maxlen; n++){
		rc = read(fd, &c, 1);
		if(rc > 0){
			*ptr++ = c;
			if(c == '\n'){
				break;
			}
		}
		else if (rc == 0){
			break;
		}
		else{
			if(errno != EINTR){
				return -1;
			}
		}
	}

	*ptr = 0;

	return ptr - (char*)vptr;
}

int setsock_reuse(int sockfd){
	int opt = 1;

	return Setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
}

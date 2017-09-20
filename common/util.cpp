#include "comm.h"

static int daemon_proc = 0;

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

void err_vmsg(const char* fmt, va_list ap){
	if(daemon_proc == 0){
		vfprintf(stderr, err_fmt(fmt), ap);
	}
	else{
		vsyslog(LOG_INFO|LOG_USER, err_fmt(fmt), ap);
	}
}

void err_msg(const char* fmt, ...){
	va_list ap;
	va_start(ap, fmt);
	err_vmsg(fmt, ap);
	va_end(ap);
}

void err_quit(const char* fmt, ...){
	va_list ap;
	va_start(ap, fmt);
	err_vmsg(fmt, ap);
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

Sigfunc* Signal(int signo, Sigfunc* func){
	struct sigaction act, oact;

	act.sa_handler = func;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	
	if(signo == SIGALRM){
#ifdef SA_INTERRUPT
		act.sa_flags |= SA_INTERRUPT;
#endif
	}
	else{
#ifdef SA_RESTART
		act.sa_flags |= SA_RESTART;
#endif
	}

	if(sigaction(signo, &act, &oact) < 0){
		return SIG_ERR;
	}

	return oact.sa_handler;
}

int daemon_init(const char* pname, int facility){
	int i;
	pid_t pid;

	if((pid = Fork()) < 0){
		return -1;
	}

	if(pid){ /* parent terminates */
		_exit(0); 
	}

	/* child 1 continue */

	if(setsid() < 0){
		return -1;
	}

	Signal(SIGHUP, SIG_IGN);

	if((pid = Fork()) < 0){
		return -1;
	}

	if(pid){ /* child 1 terminates */
		_exit(0); 
	}

	/* child 2 continue */

	daemon_proc = 1;

	chdir("/");

	const int MAXFD = 64;
	for(int i=0; i< MAXFD; i++){
		close(i);
	}

	/* redirect stdin, stdout, and stderr to /dev/null */
	open("/dev/null", O_RDONLY);
	open("/dev/null", O_RDWR);
	open("/dev/null", O_RDWR);

	openlog(pname, LOG_PID, facility);

	return 0;
}

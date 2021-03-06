
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>

#include <syslog.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <sys/wait.h>

#ifdef __linux__
	#include <mqueue.h>
#endif

#include <sys/socket.h>
#include <arpa/inet.h>
#define  LISTENQ 10
#define  SVRPORT 12345
typedef struct sockaddr SA;

//For semaphores (from sys/sem.h)
#define SEM_A 0200 /* alter permission */
#define SEM_R 0400 /* read permission */

//For message queues (from sys/msg.h)
#define MSG_R 0400 /* read permission */
#define MSG_W 0200 /* write permission */

//For shared memory (from sys/shm.h)
#define SHM_R 0400 /* read permission */
#define SHM_W 0200 /* write permission */

#ifdef __linux__  
	#define SVMSG_MODE  0660  
#else  
	#define SVMSG_MODE  MSG_R | MSG_W  
#endif

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

#define MAX_LINE 100

#define show_msg err_msg

#include <signal.h>
typedef void Sigfunc(int);
Sigfunc *Signal(int signo, Sigfunc* func);

void err_msg(const char* fmt, ...);
void err_quit(const char* fmt, ...);

int readn(int fd, void* vptr, size_t n);
int writen(int fd, const void* vptr, size_t n);
int readline(int fd, void* vptr, size_t maxlen);

int setsock_reuse(int fd);

int daemon_init(const char* pname, int facility);

//自动生成wrapper.cpp
//格式: /*cond:(ret < 0)*/
////////////////////////////////////////

/*gen_start*/

//unix
int Getopt(int argc, char * const *argv, const char *optstring);

//process
pid_t Fork(void);

//network
int Socket(int domain, int type, int protocol); 
int Bind(int socket, const struct sockaddr *address, socklen_t address_len);
int Listen(int socket, int backlog);
int Connect(int socket, const struct sockaddr *address, socklen_t address_len);
int Inet_pton(int af, const char * src, void * dst); 
int Setsockopt(int socket, int level, int option_name, const void *option_value, socklen_t option_len);
ssize_t Sendto(int socket, const void *buffer, size_t length, int flags, const struct sockaddr *dest_addr, socklen_t dest_len);
ssize_t Recvfrom(int socket, void *buffer, size_t length, int flags, struct sockaddr *address, socklen_t *address_len);

//posix mqueue
#ifdef __linux__
	mqd_t Mq_open(const char *name, int oflag); 
	int Mq_getattr(mqd_t mqdes, struct mq_attr *attr);
	int Mq_setattr(mqd_t mqdes, const struct mq_attr *newattr, struct mq_attr *oldattr);
	int Mq_unlink(const char *name);
	int Mq_close(mqd_t mqdes);
	int Mq_send(mqd_t mqdes, const char *msg_ptr, size_t msg_len, unsigned int msg_prio);
	ssize_t Mq_receive(mqd_t mqdes, char *msg_ptr, size_t msg_len, unsigned int *msg_prio);
#endif

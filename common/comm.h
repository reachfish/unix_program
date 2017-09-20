
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>

#include <unistd.h>
#include <fcntl.h>
#include <time.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <sys/wait.h>

#ifdef __LINUX__
	#include <mqueue.h>
#endif

#include <sys/socket.h>
#include <arpa/inet.h>
#define  LISTENQ 10
#define  SVRPORT 1234
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

#ifdef __LINUX__  
	#define SVMSG_MODE  0660  
#else  
	#define SVMSG_MODE  MSG_R | MSG_W  
#endif

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

#define MAX_LINE 100

void err_quit(const char* fmt, ...);

int readn(int fd, void* vptr, size_t n);
int writen(int fd, const void* vptr, size_t n);
int readline(int fd, void* vptr, size_t maxlen);

//自动生成wrapper.cpp
//格式: /*cond:(ret < 0)*/
////////////////////////////////////////
//posix mqueue
#ifdef __LINUX__
	mqd_t Mq_open(const char *name, int oflag); /*gen*/
#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <sys/wait.h>

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

#define MAX_LINE 100

void err_quit(const char* err){
	fprintf(stderr, "%s\n", err);
	exit(-1);
}


#include "comm.h"

// ftok: 获取key_t值。典型实现，id + st_dev + st_ino。(pathname存在时计算结果才会有意义)
void ftok_(){
	struct stat at;

	const char* pathname = "/tmp/test";
	stat(pathname, &at);
	printf("std_dev: %lx, st_ino: %lx, key: %x\n", (unsigned long)at.st_dev, (unsigned long)at.st_ino, ftok(pathname, 0x57));
}

//ipc_perm.seq会递增
void msqid_(){
	for(int i=0;i<10; i++){
		int msqid = msgget(IPC_PRIVATE, SVMSG_MODE | IPC_CREAT);
		printf("msgid = %d\n", msqid);
		//msgctl(msqid, IPC_RMID, NULL);
	}

	//sleep(100);
}

int main(){
	msqid_();
	return 0;
}

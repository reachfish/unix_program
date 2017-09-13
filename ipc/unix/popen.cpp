#include "comm.h"

int main(){
	size_t n;
	char buff[MAX_LINE], command[MAX_LINE];
	FILE *fp;

	fgets(buff, MAX_LINE, stdin);
	n = strlen(buff);
	if(buff[n-1]=='\n'){
		n--;
	}

	snprintf(command, sizeof(command), "cat %s", buff);
	fp = popen(command, "r");
	while(fgets(buff, MAX_LINE, fp)){
		fputs(buff, stdout);
	}

	fclose(fp);
	exit(0);
}

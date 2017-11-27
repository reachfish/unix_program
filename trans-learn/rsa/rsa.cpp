#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<openssl/rsa.h>
#include<openssl/pem.h>
#include<openssl/err.h>

#define OPENSSLKEY "test.key"
#define PUBLICKEY "test_pub.key"

#define BUF_SIZE 1024

char *rsa_encrypt(const char* str, const char* key_path);
char *rsa_decrypt(const char* str, const char* key_path);

int main(){

	char *source = "this is rsa test data: Hello World!";
	char *ptr_en = rsa_encrypt(source, PUBLICKEY);
	char *ptr_de = rsa_decrypt(ptr_en, OPENSSLKEY);

	printf("source: %s\n", source);
	printf("after encrypt: %s\n", ptr_en ? ptr_en : "NULL");
	printf("after decrypt: %s\n", ptr_de ? ptr_de : "NULL");

	if(ptr_en){
		free(ptr_en);
	}

	if(ptr_de){
		free(ptr_de);
	}

	return 0;
}

char *rsa_encrypt(const char* str, const char* key_path){
	char *ptr_en = NULL;
	RSA* p_rsa;
	FILE* file;

	if((file = fopen(key_path, "r"))==NULL){
		 perror("open key file error");
		 return NULL;
	}

	if((p_rsa=PEM_read_RSA_PUBKEY(file,NULL,NULL,NULL))==NULL){
		ERR_print_errors_fp(stdout);
		return NULL;
	}
}

char *rsa_decrypt(const char* str, const char* key_path){
}

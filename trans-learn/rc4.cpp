#include <string.h>
#include <stdio.h>
#include <openssl/rc4.h>

int main(){
	const unsigned char key_data[8] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};

	RC4_KEY *key1 = new RC4_KEY;
	RC4_KEY *key2 = new RC4_KEY;

	RC4_set_key(key1, sizeof(key_data), key_data);
	RC4_set_key(key2, sizeof(key_data), key_data);

	const char* indata = "hello world!";
	unsigned char  tempdata[100];
	unsigned char  outdata[100];

	memset(tempdata, 0, sizeof(tempdata));
	memset(outdata, 0, sizeof(outdata));

	RC4(key1, strlen(indata), (const unsigned char*)indata, tempdata);
	RC4(key2, strlen(indata), tempdata, outdata);

	printf("in: %s\n", indata);
	printf("temp: %s\n\n", tempdata);
	printf("out: %s\n", outdata);


	delete key1;
	delete key2;

	return  0;
}

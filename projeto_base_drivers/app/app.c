#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>

enum OPS {HEXPORT,INPORT,DISPLAY,RED_LEDS,GREEN_LEDS,KEYS,SWITCHES};

uint32_t number = 0x40794079;
uint32_t zero = 0x40404040;
uint32_t zerol = 0;
uint32_t number2 = 2;
unsigned char hexdigit[] = {0x24, 0x79, 0x40, 0x40,
                            0x40, 0x40, 0x40, 0x40, 
                            0xFF, 0x40, 0x40, 0x40,
			                0xFF, 0x5E, 0x79, 0x71};

void wait(void){
	int i;
	for(i=0;i>-1;i++){
	}
	
	return;
}

void real_write(int debug,int dev,unsigned char * buffer,int opt){
	int ret;
	wait();
	ret = write(dev,buffer,opt);
	ret = write(dev,buffer,opt);
	if( ret != -1) printf("ok -> %d\n",debug);
}

int main() {
	int i, j = 1, k;

	int dev = open("/dev/de2i150_altera", O_RDWR);

	printf("%d\n",dev);

	real_write(0,dev,&zerol,RED_LEDS);
	real_write(0,dev,&zerol,GREEN_LEDS);
	real_write(0,dev,&number,HEXPORT);

	int ret = read(dev,&number2,SWITCHES);

	if(ret == -1) printf("deu erro na leitura\n");

	printf("%d\n",number2);

	close(dev);
	return 0;
}


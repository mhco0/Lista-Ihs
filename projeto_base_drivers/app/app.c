#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>

enum OPS {HEXPORT,INPORT,DISPLAY,RED_LEDS,GREEN_LEDS,KEYS,SWITCHES};

uint32_t number = 0x79794040;
uint32_t number2 = 2;
uint32_t number3 = 10;
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

int cu;

int main() {
	int i, j = 1, k;

	int dev = open("/dev/de2i150_altera", O_RDWR);

	printf("%d\n",dev);

	/*for (i=0; i>-1; i++) {
		//read(dev, &j, 4);
		k = hexdigit[j & 0xF]
		  | (hexdigit[(j >>  4) & 0xF] << 8)
		  | (hexdigit[(j >>  8) & 0xF] << 16)
		  | (hexdigit[(j >> 12) & 0xF] << 24);
		k = ~k;
		write(dev, &k, 4);
		wait();
		printf("cu\n");
	}*/
	

	//real_write(0,dev,hexdigit,RED_LEDS);
	
	//real_write(1,dev,hexdigit,GREEN_LEDS);
	
	//real_write(2,dev,hexdigit,HEXPORT);
	
	
	read(dev,&cu,SWITCHES);
	
	printf("%d\n",cu);
	close(dev);
	return 0;
}


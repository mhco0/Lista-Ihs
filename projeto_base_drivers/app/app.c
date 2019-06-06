#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>

uint32_t number = 0x0000000079794040;
uint32_t number2 = 2;
uint32_t number3 = 10;
char hexdigit[] = {0x40, 0x40, 0x79, 0x24,
                            0x40, 0x40, 0x40, 0x40, 
                            0xFF, 0x40, 0x40, 0x40,
			                0xFF, 0x5E, 0x79, 0x71};

void wait(void){
	int i;
	for(i=0;i>-1;i++){
	}
	
	return;
}

void real_write(int debug,int dev){
	int ret;
	wait();
	wait();
	ret = write(dev, hexdigit,0);
	ret = write(dev, hexdigit,0);
	if( ret != -1) printf("ok -> %d\n",debug);
}

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
	

	real_write(0,dev);
	
	real_write(1,dev);
	
	real_write(2,dev);
	
	close(dev);
	return 0;
}


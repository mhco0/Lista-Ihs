#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>


unsigned char hexdigit[] = {0x3F, 0x06, 0x5B, 0x4F,
                            0x66, 0x6D, 0x7D, 0x07, 
                            0x7F, 0x6F, 0x77, 0x7C,
			                0x39, 0x5E, 0x79, 0x71};

void wait(void){
	int i;
	for(i=0;i>-1;i++){
	}
	
	return;
}	

int main() {
	int i, j = 1, k;

	int dev = open("/dev/de2i150_altera", O_RDWR);

	printf("%d\n",dev);

	for (i=0; i>-1; i++) {
		read(dev, &j, 4);
		k = hexdigit[j & 0xF]
		  | (hexdigit[(j >>  4) & 0xF] << 8)
		  | (hexdigit[(j >>  8) & 0xF] << 16)
		  | (hexdigit[(j >> 12) & 0xF] << 24);
		k = ~k;
		write(dev, &k, 4);
		wait();
		printf("cu\n");
	}

	close(dev);
	return 0;
}


// gcc -o th2 th2.c -lpthread

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "libspi.h"

//http://linuxprograms.wordpress.com/2007/12/29/threads-programming-in-linux-examples/

unsigned int beeptime;
unsigned char *keys_ptr;    // pointer used  to read data buffer

void * thread1()  // Time base 
{
        while(1) {
               
		usleep(20*1000); // 100ms * 

		if (beeptime)
			beeptime--;
		
		///////printf("Hello!! %d \n",beeptime);
        }
}

void * thread2() // Periodic Task

{
	init_spi();
	while (1) 
	{
		

		if (!beeptime)
		{
	        
	        	beeptime=5;
	        /////	printf("Done %d\n",beeptime);  // Call SPI
	        	poll_spi();
	              
	        }
	        
	        	

	}

	

}

void * thread3() // Tateti task

{

unsigned char val[3]={0x7f,0xff,0xff};
int input=0;
written=FALSE;
write_tablero(val);

	while (1) {
	
		write_tablero(val);

		sleep(1);



		if (Get_Key_Status()){
	
			keys_ptr=Get_Key();
			input=(keys_ptr[0]<<8)|keys_ptr[1];
			printf ("%x\n",input);
			switch (input)
			{
				case 0xFFFE:
					val [1]=0x01;
					break;
				case 0xFFEF:
					val [1]=0x02;
					break;
				case 0xFF7F:
					val [1]=0x04;
					break;
				case 0xFFFB:
					val [1]=0x08;
					break;
				case 0xFFDF:
					val [1]=0x10;
					break;
				case 0xFDFF:
					val [1]=0x20;
					break;
				case 0xFFF7:
					val [1]=0x40;
					break;
				case 0xFFBF:
					val [1]=0x80;
					break;
				case 0xFEFF:
					val [0]=0x01;
					break;
			//}
			write_tablero (val);
//			printf("Keys = 1: %X 2: %X \n",keys_ptr[0],keys_ptr[1]);
	
		}
	
	}


}


int main()
{
        int status;
        pthread_t tid1,tid2,tid3;

        pthread_create(&tid1,NULL,thread1,NULL);
        pthread_create(&tid2,NULL,thread2,NULL);
        pthread_create(&tid3,NULL,thread3,NULL);
        pthread_join(tid1,NULL);
        pthread_join(tid2,NULL);
        pthread_join(tid3,NULL);
        return 0;
}


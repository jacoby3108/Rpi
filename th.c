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
               
		usleep(100*1000); // 100ms * 

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

unsigned char val[3]={0x80,0x00,0x00};
written=FALSE;

	while (1) {
	
//////		printf("tateti ");
	
		write_tablero(val);

		sleep(1);

		val[0]^=0x80;


		if (Get_Key_Status()){
	
			keys_ptr=Get_Key();
	
			printf("Keys = 1: %X 2: %X \n",keys_ptr[0],keys_ptr[1]);
	
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


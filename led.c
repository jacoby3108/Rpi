#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>


// Pin file system
#define LED "/sys/class/gpio/gpio17/value"
#define SENS "/sys/class/gpio/gpio22/value"

#define ON '1'
#define OFF '0'




int handle_led,handle_sens; /* Integer for file descriptor returned by open() call. */
unsigned char val='0';      //Value written to led (Warning use '0' or '1' not 0 or 1)
unsigned char sens;         // Value returned by photosensor

int nWritten,nread;  // bytes read or written during file operations


void main (void)
{

// Open led file 

	if ((handle_led = open(LED, O_WRONLY,
    	S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
	{
    		fprintf(stdout, "Cannot open LED. Try again later.\n");
    		exit(1);
	}
	
// Open sensor file
	
	if ((handle_sens = open(SENS, O_RDONLY,    //int  open(  char  *filename,  int  access,  int  permission  );
    	S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
	{
    		fprintf(stdout, "Cannot open SENSOR. Try again later.\n");
    		exit(1);
	}
	
	
	// turn led on 
	val=ON;
		
	nWritten=write(handle_led,&val,1); // int  write(  int  handle,  void  *buffer,  int  nbyte  );
	
	sleep(1);  // wait to turn on/off led before reading (processor is to fast :))  
	
	// Read sensor 
	nread=read(handle_sens,&sens,1);  //int  read(  int  handle,  void  *buffer,  int  nbyte );
	
	
	// Show results
	printf ("Written %d Read %d Sensor %c Done !\n\n",nWritten,nread,sens);
	
	
	

} 

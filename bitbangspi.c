#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

// bitbang v2 todo ok

// Pin file system

#define EXPORT "/sys/class/gpio/export"      // Export file 
  

//============================This must be done again===========================================

#define LED "/sys/class/gpio/gpio17/value"   		   // LED Port
#define DIR_LED "/sys/class/gpio/gpio17/direction"   // LED direction
#define PIN_LED  "17"  
//#define PIN_LED_DIR  "out"

#define SENS "/sys/class/gpio/gpio22/value"  		// Fototransistor Port
#define DIR_SENS "/sys/class/gpio/gpio22/direction"  // Fototransistor
#define PIN_SENS "22"
//#define PIN_SENS_DIR "in"

#define SDI "/sys/class/gpio/gpio10/value"   // SPI MOSI to 74hc595
#define DIR_SDI "/sys/class/gpio/gpio10/direction"   // SPI MOSI to 74hc595
#define PIN_SDI "10"
//#define PIN_SDI_DIR "out"

#define LOAD "/sys/class/gpio/gpio23/value"  // LOAD Parallel Input register 74hc589 (Toggle twice) 
#define DIR_LOAD "/sys/class/gpio/gpio23/direction"  // LOAD Parallel Input register 74hc589 (Toggle twice)
#define PIN_LOAD "23"
//#define PIN_LOAD_DIR "out"

#define SCK "/sys/class/gpio/gpio11/value"   // SPI clock
#define DIR_SCK "/sys/class/gpio/gpio11/direction"   // SPI clock  
#define PIN_SCK "11" 
//#define PIN_SCK_DIR "out"

#define SDO "/sys/class/gpio/gpio9/value"    // SPI MISO from 74hc589
#define DIR_SDO "/sys/class/gpio/gpio9/direction"    // SPI MISO from 74hc589
#define PIN_SDO  "9"
//#define PIN_SDO_DIR "in"



//echo "17" > /sys/class/gpio/export
//echo "out" > /sys/class/gpio/gpio17/direction
//cat /sys/class/gpio/gpio9/value

#define ON '1'
#define OFF '0'




int handle_led,handle_sens; /* Integer for file descriptor returned by open() call. */

int handle_sdi;
int handle_load;
int handle_sck;
int handle_sdo;
int handle_export;
int handle_direction;




unsigned char val='0';      //Value written to led (Warning use '0' or '1' not 0 or 1)
unsigned char sens='0';         // Value returned by photosensor

int nWritten,nread;  // bytes read or written during file operations


int Get_Port_handle(char *device,int mode);
void Set_PIN_Direction(char *file,char *direction);


void LED_pin(unsigned char value);
unsigned char SENSOR_pin(void);
void SCK_pin(unsigned char value);
void LOAD_pin(unsigned char value);
unsigned char SDO_pin(void);
void SDI_pin(unsigned char value);
unsigned char spiWrite(const unsigned char regData);

unsigned char contador;
unsigned char read_data;

int i,j,k;

void main (void)
{

// Open export file 


	if ((handle_export = open(EXPORT, O_WRONLY,
    	S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
	{
    		fprintf(stdout, "Cannot open EXPORT File. Try again later.\n");
    		exit(1);
	}

// And export pins
	
	nWritten=write(handle_export,PIN_LED,sizeof(PIN_LED)-1); 
	
	if (nWritten==-1){
	fprintf(stdout, "Cannot open EXPORT File for PIN LED. Try again later.\n");
//	exit(1);
	}
	
	
	nWritten=write(handle_export,PIN_SENS,sizeof(PIN_SENS)-1); 
	if (nWritten==-1){
	fprintf(stdout, "Cannot open EXPORT File for PIN SENS. Try again later.\n");
//	exit(1);
	}
		
	
	nWritten=write(handle_export,PIN_SDI,sizeof(PIN_SDI)-1);
	
	if (nWritten==-1){
	fprintf(stdout, "Cannot open EXPORT File for PIN SDI. Try again later.\n");
//	exit(1);
	}
	
	nWritten=write(handle_export,PIN_LOAD,sizeof(PIN_LOAD)-1);
	
	if (nWritten==-1){
	fprintf(stdout, "Cannot open EXPORT File for PIN LOAD. Try again later.\n");
//	exit(1);
	}
	
	
	nWritten=write(handle_export,PIN_SCK,sizeof(PIN_SCK)-1);
	
	if (nWritten==-1){
	fprintf(stdout, "Cannot open EXPORT File for PIN SCK. Try again later.\n");
//	exit(1);
	}
	
	
	nWritten=write(handle_export,PIN_SDO,sizeof(PIN_SDO)-1);
	
	if (nWritten==-1){
	fprintf(stdout, "Cannot open EXPORT File for PIN SDO. Try again later.\n");
//	exit(1);
	}

// Set pins Directions
	
	Set_PIN_Direction(DIR_LED,"out");
	Set_PIN_Direction(DIR_SENS,"in");
	
	Set_PIN_Direction(DIR_SDI,"out");
	Set_PIN_Direction(DIR_LOAD,"out");
	Set_PIN_Direction(DIR_SCK,"out");
	Set_PIN_Direction(DIR_SDO,"in");
	



	


// Get pins handles to have access to pins
	
	handle_led = Get_Port_handle(LED,O_WRONLY);
//	handle_sens = Get_Port_handle(SENS,O_RDONLY);
	

	handle_sdi = Get_Port_handle(SDI,O_WRONLY);
	handle_load = Get_Port_handle(LOAD,O_WRONLY);	
	handle_sck = Get_Port_handle(SCK,O_WRONLY);
//	handle_sdo = Get_Port_handle(SDO,O_RDONLY);
	
/////////////////////////////////////////////////////////////////////////	
	
	
	
// Open SDI file
	
	
	LED_pin(ON);
	
	
	sleep(1);  // wait to turn on/off led before reading (processor is to fast :))
	
	for(i=0;i<5;i++)
	{
		sens=SENSOR_pin();
		printf ("Sensor Read Back %c Done !\n\n",sens);
	}

	sleep(2);  // time to read on screen
	
	while (1) {

	LOAD_pin(OFF);
	LOAD_pin(ON);
	
	
	LOAD_pin(OFF);
	LOAD_pin(ON);
	
	
	 printf("Read Value (bin): ");
	read_data=spiWrite(contador++);
	
	printf(" Data read (Hex) %X\n ",read_data);
	
	}



} 


unsigned char spiWrite(const unsigned char regData)
{

  unsigned char SPICount;                               // Counter used to clock out the data
  unsigned char SPIData;                                // Define a data structure for the SPI data.
  unsigned char SDO_value;
  unsigned char SDO_DATA=0;
 
  SCK_pin(ON);                                          // and CK low
  SPIData = regData;                                    // Preload the data to be sent 


  

  for (SPICount = 0; SPICount < 8; SPICount++)          // Prepare to clock out the Address & Data
  {
    if (SPIData & 0x80)
      SDI_pin(ON);
    else
      SDI_pin(OFF);
      
  
    SCK_pin(OFF); 
    SDO_value=SDO_pin();
    SCK_pin(ON);
    
     SDO_DATA <<=1;
    
    if (SDO_value==ON)

	SDO_DATA|=1;	
    else    
    
       	SDO_DATA&=~1;	
    
   
    	
    SPIData <<= 1;
    
     
      putchar(SDO_value);
      
  }                                                     // and loop back to send the next bit   
 
  SDI_pin(OFF);                                         // Reset the MOSI data line

return(SDO_DATA);
}


void LED_pin(unsigned char value)
{

    write(handle_led,&value,1); // int  write(  int  handle,  void  *buffer,  int  nbyte  );
    

}

unsigned char SENSOR_pin(void)
{

   unsigned char sensor;
   unsigned char handle_sensor;
   handle_sens = Get_Port_handle(SENS,O_RDONLY);
   read(handle_sens,&sensor,3);   // read data,CR,LF //int  read(  int  handle,  void  *buffer,  int  nbyte );
   close(handle_sens);
   
   return sensor;

}


void SDI_pin(unsigned char value)
{

    write(handle_sdi,&value,1); // int  write(  int  handle,  void  *buffer,  int  nbyte  );
    

}


void LOAD_pin(unsigned char value)
{

    write(handle_load,&value,1); // int  write(  int  handle,  void  *buffer,  int  nbyte  );
    

}

void SCK_pin(unsigned char value)
{


    write(handle_sck,&value,1); // int  write(  int  handle,  void  *buffer,  int  nbyte  );
   
}



unsigned char SDO_pin(void)
{

   unsigned char serial_out;
   unsigned char handle_sdo;
  
   handle_sdo = Get_Port_handle(SDO,O_RDONLY);   
   read(handle_sdo,&serial_out,1);  //int  read(  int  handle,  void  *buffer,  int  nbyte );
   close(handle_sdo);
   return serial_out;

}


// Open device port 
int Get_Port_handle(char *device,int mode)
{
		int handle;
	
	// int  open(  char  *filename,  int  access,  int  permission  );
	
		if ((handle = open(device,mode,  
    		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
		{
    			fprintf(stdout, "Cannot open %s. Try again later.\n", device );
    			exit(1);
		}
		return (handle);
	
	
}
	
	
	
	
void Set_PIN_Direction(char *file,char *direction)
{

		if ((handle_direction = open(file, O_WRONLY,
    		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
		{
    		fprintf(stdout, "Cannot open %s File. Try again later.\n",file);
    		exit(1);
		}


	
		if ((nWritten=write(handle_direction,direction,sizeof(direction)-1))==-1)
		{	
		fprintf(stdout, "Cannot set direction in file %s. Try again later.\n",file);
    		exit(1);
		}

	
}


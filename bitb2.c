#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>



// ===================================================================


#define PIN_LED  17  	// LED Port  /* P1-xx */
#define PIN_SENS 22  	// Fototransistor Port
#define PIN_MOSI  10  	// SPI MOSI to 74hc595
#define PIN_LOAD 23	// LOAD Parallel Input register 74hc589 (Toggle twice)
#define PIN_SCK  11 	// SPI clock 
#define PIN_MISO  9	// SPI MISO from 74hc589


//echo "17" > /sys/class/gpio/export
//echo "out" > /sys/class/gpio/gpio17/direction
//cat /sys/class/gpio/gpio9/value

#define ON  1
#define OFF 0


#define IN  0
#define OUT 1

#define LOW  0
#define HIGH 1




int LED_pin(unsigned char value);
unsigned char SENSOR_pin(void);
int SCK_pin(unsigned char value);
int LOAD_pin(unsigned char value);
unsigned char MISO_pin(void);
int MOSI_pin(unsigned char value);
unsigned char spiWrite(const unsigned char regData);



unsigned char contador,sens;
unsigned char read_data;

int i,j,k;





int main(int argc, char *argv[])

{
///usleep(500 * 1000);


	/*
	 * Enable GPIO pins
	 */

	 
	if (GPIOExport(PIN_LED) ==-1)
		return(1);
	if (GPIOExport(PIN_SENS) ==-1)
		return(1);
	if (GPIOExport(PIN_MOSI) ==-1)
		return(1);
	if (GPIOExport(PIN_LOAD) ==-1)
		return(1);	
	if (GPIOExport(PIN_SCK) ==-1)
		return(1);	
	if (GPIOExport(PIN_MISO) ==-1)
		return(1);	
		
/*
 * Set GPIO directions
 */		
		
		
	if (GPIODirection(PIN_LED,OUT) ==-1)
		return(1);
	if (GPIODirection(PIN_SENS,IN) ==-1)
		return(1);
	if (GPIODirection(PIN_MOSI,OUT) ==-1)
		return(1);
	if (GPIODirection(PIN_LOAD,OUT) ==-1)
		return(1);	
	if (GPIODirection(PIN_SCK,OUT) ==-1)
		return(1);	
	if (GPIODirection(PIN_MISO,IN) ==-1)
		return(1);	
	
	
		


	
	


/////////////////////////////////////////////////////////////////////////	
	
	
	
	LED_pin(ON);
	
	
	sleep(1);  // wait to turn on/off led before reading (processor is to fast :))
	
	for(i=0;i<5;i++)
	{
		sens=SENSOR_pin();
		printf ("Sensor Read Back %d Done !\n\n",sens);
	}

	sleep(2);  // time to read on screen

///////////////////////77	
	
	while (1) {

	LOAD_pin(OFF);
	LOAD_pin(ON);
	
	
	LOAD_pin(OFF);
	LOAD_pin(ON);
	
	
	 printf("Read Value (bin): ");
	read_data=spiWrite(contador++);
	
	printf(" Data read (Hex) %X\n ",read_data);
	
	}

/////////////////////
	 
	if (GPIOUnexport(PIN_LED) ==-1)
		return(4);
	if (GPIOUnexport(PIN_SENS) ==-1)
		return(4);
	if (GPIOUnexport(PIN_MOSI) ==-1)
		return(4);
	if (GPIOUnexport(PIN_LOAD) ==-1)
		return(4);	
	if (GPIOUnexport(PIN_SCK) ==-1)
		return(4);	
	if (GPIOUnexport(PIN_MISO) ==-1)
		return(4);	
		
	return(0);

} 


unsigned char spiWrite(const unsigned char regData)
{

  unsigned char SPICount;              // Counter used to clock out the data
  unsigned char SPIData;               // Define a data structure for the SPI data.
  unsigned char MISO_value;
  unsigned char MISO_DATA=0;
 
  SCK_pin(ON);                         // and CK High
  SPIData = regData;                   // Preload the data to be sent 


  

  for (SPICount = 0; SPICount < 8; SPICount++)          // Prepare to clock out the Address & Data
  {
    if (SPIData & 0x80)
      MOSI_pin(ON);
    else
      MOSI_pin(OFF);
      
  
    SCK_pin(OFF); 
    MISO_value=MISO_pin();
    SCK_pin(ON);
    
     MISO_DATA <<=1;					// Pre-Shift
    
    if (MISO_value==ON)

	MISO_DATA|=1;	
    else    
    
       	MISO_DATA&=~1;	
    
   
    	
    SPIData <<= 1;
    
     
     printf("%d",MISO_value);
      
  }                                                     // and loop back to send the next bit   
 
  MOSI_pin(OFF);                                         // Reset the MOSI data line

return(MISO_DATA);

}





int LED_pin(unsigned char value)
{
		 
	if ( GPIOWrite(PIN_LED, value) == -1)
			return(3);
}

unsigned char SENSOR_pin(void)
{

   
   
  return(GPIORead(PIN_SENS));
   

}


int MOSI_pin(unsigned char value)
{

		 
	if ( GPIOWrite(PIN_MOSI, value) == -1)
			return(3);
}


int LOAD_pin(unsigned char value)
{

  
    	if ( GPIOWrite(PIN_LOAD, value) == -1)
			return(3);

}

int SCK_pin(unsigned char value)
{

   
    	if ( GPIOWrite(PIN_SCK, value) == -1)
			return(3); 
}



unsigned char MISO_pin(void)
{

    return(GPIORead(PIN_MISO));
}



// Making changes taken from http://elinux.org/RPi_Low-level_peripherals#C_2



int GPIOExport(int pin)
{
#define BUFFER_MAX 3
	char buffer[BUFFER_MAX];
	ssize_t bytes_written;
	int fd;

	fd = open("/sys/class/gpio/export", O_WRONLY);
	if (-1 == fd) {
		fprintf(stderr, "Failed to open export for writing!\n");
		return(-1);
	}

	bytes_written = snprintf(buffer, BUFFER_MAX, "%d", pin);
	write(fd, buffer, bytes_written);
	close(fd);
	return(0);
}

int GPIOUnexport(int pin)
{
	char buffer[BUFFER_MAX];
	ssize_t bytes_written;
	int fd;

	fd = open("/sys/class/gpio/unexport", O_WRONLY);
	if (-1 == fd) {
		fprintf(stderr, "Failed to open unexport for writing!\n");
		return(-1);
	}

	bytes_written = snprintf(buffer, BUFFER_MAX, "%d", pin);
	write(fd, buffer, bytes_written);
	close(fd);
	return(0);
}

int GPIODirection(int pin, int dir)
{
	static const char s_directions_str[]  = "in\0out";

#define DIRECTION_MAX 35
	char path[DIRECTION_MAX];
	int fd;

	snprintf(path, DIRECTION_MAX, "/sys/class/gpio/gpio%d/direction", pin);
	fd = open(path, O_WRONLY);
	if (-1 == fd) {
		fprintf(stderr, "Failed to open gpio direction for writing!\n");
		return(-1);
	}

	if (-1 == write(fd, &s_directions_str[IN == dir ? 0 : 3], IN == dir ? 2 : 3)) {
		fprintf(stderr, "Failed to set direction!\n");
		return(-1);
	}

	close(fd);
	return(0);
}

int GPIORead(int pin)
{
#define VALUE_MAX 30
	char path[VALUE_MAX];
	char value_str[3];
	int fd;

	snprintf(path, VALUE_MAX, "/sys/class/gpio/gpio%d/value", pin);
	fd = open(path, O_RDONLY);
	if (-1 == fd) {
		fprintf(stderr, "Failed to open gpio value for reading!\n");
		return(-1);
	}

	if (-1 == read(fd, value_str, 3)) {
		fprintf(stderr, "Failed to read value!\n");
		return(-1);
	}

	close(fd);

	return(atoi(value_str));
}

int GPIOWrite(int pin, int value)
{
	static const char s_values_str[] = "01";

	char path[VALUE_MAX];
	int fd;

	snprintf(path, VALUE_MAX, "/sys/class/gpio/gpio%d/value", pin);
	fd = open(path, O_WRONLY);
	if (-1 == fd) {
		fprintf(stderr, "Failed to open gpio value for writing!\n");
		return(-1);
	}

// int  write(  int  handle,  void  *buffer,  int  nbyte  );

	if (1 != write(fd, &s_values_str[LOW == value ? 0 : 1], 1)) {
		fprintf(stderr, "Failed to write value!\n");
		return(-1);
	}

	close(fd);
	return(0);
}










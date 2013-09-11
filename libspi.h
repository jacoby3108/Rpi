void poll_spi(void);
void init_spi(void);
void stop_spi(void);
void write_tablero( unsigned char * p2tablero);
unsigned char get_write_status(void);

#define TRUE 1
#define FALSE 0

unsigned char written;  // ocultar

#define IDLE 0
#define BUTTON_PRESSED 1
unsigned char Get_Key_Status(void);
unsigned char *Get_Key(void);




#include <stdio.h>

void print_binary(unsigned char);

int main(int argc, char *argv[])

{

print_binary(0x11);

}


void print_binary(unsigned char data)

{

int i;
unsigned char walking_one=0x01;

	for (i=0;i<8;i++)
	{
		printf("%c", (data & walking_one)? '1':'0');
		walking_one<<=1;
	}

	printf("b  (Hex): %X\n ",data);

	printf("\n");
}







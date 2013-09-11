#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//	7	8	9
//	4	5	6	
//	1	2	3

#define C_1 1<<0
#define C_2 1<<1
#define C_3 1<<2
#define C_4 1<<3
#define C_5 1<<4
#define C_6 1<<5
#define C_7 1<<6
#define C_8 1<<7
#define C_9 1<<8
#define BEEP 1<<9


unsigned char arreglito[3];

//estructura
typedef struct
{
	unsigned char L;
	unsigned char b;
} juan;
//arreglo de juan
juan T[24]=
{
	{0,C_1},
	{0,C_2},
	{0,C_3},
	{0,C_4},
	{0,C_5},
	{0,C_6},
	{0,C_7},
	{0,C_8},
	{1,C_1},
	{1,C_2},
	{1,C_3},
	{1,C_4},
	{1,C_5},
	{1,C_6},
	{1,C_7},
	{1,C_8},
	{2,C_1},
	{2,C_2},
	{2,C_3},
	{2,C_4},
	{2,C_5},
	{2,C_6},
	{2,C_7},
	{2,C_8}
};

int	tieblink (void);
int	blink (int,int,int,short *);
void 	read_n_save (char);
short	conv_to_format (int);
void 	show (void);
char	check_if_winner (void);
int	move2win (void);
int	counter (void);
int 	checkifwin (short *,short *,int,int,int);
int	random_number (void);
void	smartmove (void);
void	AI (void);
void	PUT (int);
void	update_chars(unsigned char arreglito[],juan T[]);


short p1=0, rpi=0; 	//Tableros con las jugadas de cada jugador en formato xxxxxx98x7654321
int flag;

///CUERPO DEL PROGRAMA///

void main(void)
{
	char turn=0,winner=0,contador=0,win=0;	//Turno=0 => P1, turno=1 => Rpi////Winner=0 no gano nadie, =1 gano p1, =2 gano rpi
	system ("stty -echo");	
	system ("clear");
	printf ("Ta-Te-Rpi v7.0\tUse el keypad numerico para jugar\n-\t-\t-\n\n\n-\t-\t-\n\n\n-\t-\t-\n");

	while (1)
	{
		while (1)
		{
			read_n_save (turn);
			show ();
			if (winner=check_if_winner ())
			{
				win=1;
				break;
			}
			contador++;
			if (contador>8)
			{
				tieblink ();
				break;
			}
			AI ();
			show ();
			if (winner=check_if_winner ())
			{
				win=1;
				break;
			}
			contador++;
			if (contador>8)
			{
				tieblink ();
				break;
			}
			turn=~turn;
		}
		if (win==0)
		{
			AI ();
			show ();
			winner=check_if_winner ();
		}

		p1=0;
		rpi=0;
		contador=0;
		show ();
			
		while (1)
		{
			AI ();
			show ();
			if (winner=check_if_winner ())
			{
				win=1;
				break;
			}
			contador++;
			if (contador>8)
			{
				tieblink ();
				break;
			}
			read_n_save (turn);
			show ();
			if (winner=check_if_winner ())
			{
				win=1;
				break;
			}
			turn=~turn;
			contador++;
		}
		if (win==0)
		{
			AI ();
			show ();
			winner=check_if_winner ();
		}


		p1=0;
		rpi=0;
		contador=0;
		show ();
	}

	system ("stty echo");
}

void show(void)
{
	char c1='-',c2='-',c3='-',c4='-',c5='-',c6='-',c7='-',c8='-',c9='-';
	if((p1&C_1)!=0)
		c1='X';
	if((p1&C_2)!=0)
		c2='X';
	if((p1&C_3)!=0)
		c3='X';	
	if((p1&C_4)!=0)
		c4='X';	
	if((p1&C_5)!=0)
		c5='X';	
	if((p1&C_6)!=0)
		c6='X';	
	if((p1&C_7)!=0)
		c7='X';	
	if((p1&C_8)!=0)
		c8='X';	
	if((p1&C_9)!=0)
		c9='X';	
	if((rpi&C_1)!=0)
		c1='O';	
	if((rpi&C_2)!=0)
		c2='O';	
	if((rpi&C_3)!=0)
		c3='O';	
	if((rpi&C_4)!=0)
		c4='O';	
	if((rpi&C_5)!=0)
		c5='O';	
	if((rpi&C_6)!=0)
		c6='O';	
	if((rpi&C_7)!=0)
		c7='O';	
	if((rpi&C_8)!=0)
		c8='O';	
	if((rpi&C_9)!=0)
		c9='O';	
	system("clear");
	printf("Ta-Te-Rpi v7.0\n%c\t%c\t%c\n\n\n%c\t%c\t%c\n\n\n%c\t%c\t%c\n",c7,c8,c9,c4,c5,c6,c1,c2,c3);
}

void read_n_save(char turn)
{
	short input,casillero=1;
	while (casillero)
	{
		while(((input=getchar()-'0')<=0)||(input>9))	//Valida que se haya ingresado un numero
			printf("\a");					//Loopea hasta obtenerlo
		input=conv_to_format(input);	
		if(((input&p1)==0)&&((input&rpi)==0))		//Validacion de no ocupar un casillero ya ocupado
		{
			p1=input|p1;				//Si se intenta llenar un casillero ya ocupado, pide nuevo valor
			casillero=0;
		}
		else
			printf("\a");
	}	
}

short conv_to_format(int input)
{
	short converted;
	if(input<8)
	{
		for(converted=1;input>1;input--)		//Convierte el numero en decimal al formato short expuesto para los tableros
		converted=converted<<1;
	}
	else
	{
		if(input==8)
			converted=C_8;
		else
			converted=C_9;
	}
	return converted;
}

char check_if_winner(void)				//Devuelve 0 si nadie gano, 1 si gano p1, o 2 si gano rpi
{
	char winner=0;
	if((p1&C_1)!=0)			//C_1 ocupado por p1?
		if(((p1&C_2)!=0)&&((p1&C_3)!=0))
			(winner=1)&&(blink (C_1,C_2,C_3,&p1));
		else if(((p1&C_4)!=0)&&((p1&C_7)!=0))
			(winner=1)&&(blink (C_1,C_4,C_7,&p1));
		else if(((p1&C_5)!=0)&&((p1&C_9)!=0))
			(winner=1)&&(blink (C_1,C_5,C_9,&p1));
	if((p1&C_2)!=0)
		if(((p1&C_5)!=0)&&((p1&C_8)!=0))
			(winner=1)&&(blink (C_2,C_5,C_8,&p1));
	if((p1&C_3)!=0)
		if(((p1&C_6)!=0)&&((p1&C_9)!=0))
			(winner=1)&&(blink (C_3,C_6,C_9,&p1));
		else if(((p1&C_5)!=0)&&((p1&C_7)!=0))
			(winner=1)&&(blink (C_3,C_5,C_7,&p1));
	if(((p1&C_4)!=0)&&((p1&C_5)!=0)&&((p1&C_6)!=0))
		(winner=1)&&(blink (C_4,C_5,C_6,&p1));
	if(((p1&C_7)!=0)&&((p1&C_8)!=0)&&((p1&C_9)!=0))
		(winner=1)&&(blink (C_7,C_8,C_9,&p1));
	if((rpi&C_1)!=0)			//C_1 ocupado por rpi?
	{
		if(((rpi&C_2)!=0)&&((rpi&C_3)!=0))
			(winner=2)&&(blink (C_1,C_2,C_3,&rpi));
		else if(((rpi&C_4)!=0)&&((rpi&C_7)!=0))
			(winner=2)&&(blink (C_1,C_4,C_7,&rpi));
		else if(((rpi&C_5)!=0)&&((rpi&C_9)!=0))
			(winner=2)&&(blink (C_1,C_5,C_9,&rpi));
	}
	if((rpi&C_2)!=0)
	{
		if(((rpi&C_5)!=0)&&((rpi&C_8)!=0))
			(winner=2)&&(blink (C_2,C_5,C_8,&rpi));
	}
	if((rpi&C_3)!=0)
	{
		if(((rpi&C_6)!=0)&&((rpi&C_9)!=0))
			(winner=2)&&(blink (C_3,C_6,C_9,&rpi));
		else if(((rpi&C_5)!=0)&&((rpi&C_7)!=0))
			(winner=2)&&(blink (C_3,C_5,C_7,&rpi));
	}
	if(((rpi&C_4)!=0)&&((rpi&C_5)!=0)&&((rpi&C_6)!=0))
		(winner=2)&&(blink (C_4,C_5,C_6,&rpi));
	if(((rpi&C_7)!=0)&&((rpi&C_8)!=0)&&((rpi&C_9)!=0))
		(winner=2)&&(blink (C_7,C_8,C_9,&rpi));
	return winner;
}

int counter(void)
{
	
	if (checkifwin(&p1,&rpi,C_1,C_5,C_9)) flag++;
	else if (checkifwin(&p1,&rpi,C_3,C_5,C_7)) flag++;
	else if (checkifwin(&p1,&rpi,C_3,C_6,C_9)) flag++;
	else if (checkifwin(&p1,&rpi,C_2,C_5,C_8)) flag++;
	else if (checkifwin(&p1,&rpi,C_1,C_4,C_7)) flag++;
	else if (checkifwin(&p1,&rpi,C_1,C_2,C_3)) flag++;
	else if (checkifwin(&p1,&rpi,C_4,C_5,C_6)) flag++;
	else if (checkifwin(&p1,&rpi,C_7,C_8,C_9)) flag++;
	return flag;
}

int move2win(void)
{
	
	if (checkifwin(&rpi,&p1,C_1,C_5,C_9)) flag++;
	else if (checkifwin(&rpi,&p1,C_3,C_5,C_7)) flag++;
	else if (checkifwin(&rpi,&p1,C_3,C_6,C_9)) flag++;
	else if (checkifwin(&rpi,&p1,C_2,C_5,C_8)) flag++;
	else if (checkifwin(&rpi,&p1,C_1,C_4,C_7)) flag++;
	else if (checkifwin(&rpi,&p1,C_1,C_2,C_3)) flag++;
	else if (checkifwin(&rpi,&p1,C_4,C_5,C_6)) flag++;
	else if (checkifwin(&rpi,&p1,C_7,C_8,C_9)) flag++;
	return flag;
}

int checkifwin (short int *player1,short int *player2,int one,int two,int three)
{
	int flag=0;
	if ((((*player1&one)|(*player1&two)|(*player1&three))==(two|three))&&((*player2&one)==0))
	{
			rpi=(rpi|one);
			flag++;
	}
	else if ((((*player1&one)|(*player1&two)|(*player1&three))==(one|three))&&((*player2&two)==0))
	{
			rpi=(rpi|two);
			flag++;
	}
	else if ((((*player1&one)|(*player1&two)|(*player1&three))==(one|two))&&((*player2&three)==0))
	{
			rpi=(rpi|three);
			flag++;
	}
	return flag;
}

void AI(void)
{
	flag=0;
	move2win();
	if (flag==0)
		counter();
	if (flag==0)
		smartmove ();
	if ((flag==0)&&(((random_number ())==1)&&((time (NULL))%2)))
		PUT (C_5);
	switch (random_number())
	{
		case 0:
			PUT(C_1);
		case 1:	
			PUT(C_3);
		case 2:	
			PUT(C_7);
		case 3:
			PUT(C_9);
		default:
			PUT(C_5);
	}
	switch (random_number())
	{
		case 0:
			PUT(C_8);
		case 1:
			PUT(C_2);
		case 2:
			PUT(C_4);
		case 3:
			PUT(C_6);
	}
}

void smartmove (void)
{
	if (p1!=0)
	{
	if ((rpi&C_5)&&(p1&C_2)&&((rpi^C_5)==0)&&((p1^C_2)==0))
		if ((random_number ())%2)
			PUT (C_7);
		else
			PUT (C_9);
	else if ((rpi&C_5)&&(p1&C_4)&&((rpi^C_5)==0)&&((p1^C_4)==0))
		if ((random_number ())%2)
			PUT (C_3);
		else
			PUT (C_9);
	else if ((rpi&C_5)&&(p1&C_6)&&((rpi^C_5)==0)&&((p1^C_6)==0))
		if ((random_number ())%2)
			PUT (C_1);
		else
			PUT (C_7);
	else if ((rpi&C_5)&&(p1&C_8)&&((rpi^C_5)==0)&&((p1^C_8)==0))
		if ((random_number ())%2)
			PUT (C_1);
		else
			PUT (C_3);

	else if ((rpi&C_5)&&(p1&C_1)&&((rpi^C_5)==0)&&((p1^C_1)==0))
		PUT (C_9);
	else if ((rpi&C_5)&&(p1&C_3)&&((rpi^C_5)==0)&&((p1^C_3)==0))
		PUT (C_7);
	else if ((rpi&C_5)&&(p1&C_7)&&((rpi^C_5)==0)&&((p1^C_7)==0))
		PUT (C_3);
	else if ((rpi&C_5)&&(p1&C_9)&&((rpi^C_5)==0)&&((p1^C_9)==0))
		PUT (C_1);

	else if ((rpi&(C_5|C_9))&&(p1&(C_1|C_8))&&(((rpi^(C_5|C_9))==0)&&(((p1^(C_1|C_8)))==0)))
		PUT (C_3);
	else if ((rpi&(C_5|C_9))&&(p1&(C_1|C_6))&&(((rpi^(C_5|C_9))==0)&&(((p1^(C_1|C_6)))==0)))
		PUT (C_7);
	else if ((rpi&(C_5|C_7))&&(p1&(C_3|C_4))&&(((rpi^(C_5|C_7))==0)&&(((p1^(C_3|C_4)))==0)))
		PUT (C_9);
	else if ((rpi&(C_5|C_7))&&(p1&(C_3|C_8))&&(((rpi^(C_5|C_7))==0)&&(((p1^(C_3|C_8)))==0)))
		PUT (C_1);
	else if ((rpi&(C_5|C_3))&&(p1&(C_7|C_6))&&(((rpi^(C_5|C_3))==0)&&(((p1^(C_7|C_6)))==0)))
		PUT (C_1);
	else if ((rpi&(C_5|C_3))&&(p1&(C_7|C_2))&&(((rpi^(C_5|C_3))==0)&&(((p1^(C_7|C_2)))==0)))
		PUT (C_9);
	else if ((rpi&(C_5|C_1))&&(p1&(C_9|C_2))&&(((rpi^(C_5|C_1))==0)&&(((p1^(C_9|C_2)))==0)))
		PUT (C_7);
	else if ((rpi&(C_5|C_1))&&(p1&(C_9|C_4))&&(((rpi^(C_5|C_1))==0)&&(((p1^(C_9|C_4)))==0)))
		PUT (C_3);

	else if ((rpi&C_1)&&(p1&C_5)&&((rpi^C_1)==0)&&((p1^C_5)==0))
		PUT (C_9);
	else if ((rpi&C_3)&&(p1&C_5)&&((rpi^C_3)==0)&&((p1^C_5)==0))
		PUT (C_7);
	else if ((rpi&C_7)&&(p1&C_5)&&((rpi^C_7)==0)&&((p1^C_5)==0))
		PUT (C_3);
	else if ((rpi&C_9)&&(p1&C_5)&&((rpi^C_9)==0)&&((p1^C_5)==0))
		PUT (C_1);

	else if ((rpi&C_1)&&(p1&C_2)&&((rpi^C_1)==0)&&((p1^C_2)==0))
		PUT (C_7);
	else if ((rpi&C_1)&&(p1&C_3)&&((rpi^C_1)==0)&&((p1^C_3)==0))
		PUT (C_7);
	else if ((rpi&C_1)&&(p1&C_6)&&((rpi^C_1)==0)&&((p1^C_6)==0))
		PUT (C_7);
	else if ((rpi&C_1)&&(p1&C_4)&&((rpi^C_1)==0)&&((p1^C_4)==0))
		PUT (C_3);
	else if ((rpi&C_1)&&(p1&C_7)&&((rpi^C_1)==0)&&((p1^C_7)==0))
		PUT (C_3);
	else if ((rpi&C_1)&&(p1&C_8)&&((rpi^C_1)==0)&&((p1^C_8)==0))
		PUT (C_3);
	else if ((rpi&C_1)&&(p1&C_9)&&((rpi^C_1)==0)&&((p1^C_9)==0))
		PUT (C_3);

	else if ((rpi&(C_1|C_3))&&(p1&(C_2|C_4))&&((rpi^(C_1|C_3))==0)&&((p1^(C_2|C_4))==0))
		PUT (C_9);
	else if ((rpi&(C_1|C_3))&&(p1&(C_2|C_7))&&((rpi^(C_1|C_3))==0)&&((p1^(C_2|C_7))==0))
		PUT (C_9);
	else if ((rpi&(C_1|C_3))&&(p1&(C_2|C_9))&&((rpi^(C_1|C_3))==0)&&((p1^(C_2|C_9))==0))
		PUT (C_7);
	else if ((rpi&(C_1|C_7))&&(p1&(C_2|C_4))&&((rpi^(C_1|C_7))==0)&&((p1^(C_2|C_4))==0))
		PUT (C_3);
	else if ((rpi&(C_1|C_7))&&(p1&(C_3|C_4))&&((rpi^(C_1|C_7))==0)&&((p1^(C_3|C_4))==0))
		PUT (C_9);
	else if ((rpi&(C_1|C_7))&&(p1&(C_2|C_9))&&((rpi^(C_1|C_7))==0)&&((p1^(C_2|C_9))==0))
		PUT (C_3);

	else if ((rpi&C_3)&&(p1&C_1)&&((rpi^C_3)==0)&&((p1^C_1)==0))
		PUT (C_9);
	else if ((rpi&C_3)&&(p1&C_2)&&((rpi^C_3)==0)&&((p1^C_2)==0))
		PUT (C_9);
	else if ((rpi&C_3)&&(p1&C_4)&&((rpi^C_3)==0)&&((p1^C_4)==0))
		PUT (C_9);
	else if ((rpi&C_3)&&(p1&C_7)&&((rpi^C_3)==0)&&((p1^C_7)==0))
		PUT (C_9);
	else if ((rpi&C_3)&&(p1&C_6)&&((rpi^C_3)==0)&&((p1^C_6)==0))
		PUT (C_1);
	else if ((rpi&C_3)&&(p1&C_8)&&((rpi^C_3)==0)&&((p1^C_8)==0))
		PUT (C_1);
	else if ((rpi&C_3)&&(p1&C_9)&&((rpi^C_3)==0)&&((p1^C_9)==0))
		PUT (C_1);

	else if ((rpi&(C_3|C_9))&&(p1&(C_2|C_6))&&((rpi^(C_3|C_9))==0)&&((p1^(C_2|C_6))==0))
		PUT (C_7);
	else if ((rpi&(C_3|C_9))&&(p1&(C_1|C_6))&&((rpi^(C_3|C_9))==0)&&((p1^(C_1|C_6))==0))
		PUT (C_7);
	else if ((rpi&(C_3|C_9))&&(p1&(C_6|C_7))&&((rpi^(C_3|C_9))==0)&&((p1^(C_6|C_7))==0))
		PUT (C_1);
	else if ((rpi&(C_1|C_3))&&(p1&(C_2|C_6))&&((rpi^(C_1|C_3))==0)&&((p1^(C_2|C_6))==0))
		PUT (C_7);
	else if ((rpi&(C_1|C_3))&&(p1&(C_2|C_7))&&((rpi^(C_1|C_3))==0)&&((p1^(C_2|C_7))==0))
		PUT (C_9);
	else if ((rpi&(C_1|C_3))&&(p1&(C_2|C_9))&&((rpi^(C_1|C_3))==0)&&((p1^(C_2|C_9))==0))
		PUT (C_7);

	else if ((rpi&C_7)&&(p1&C_1)&&((rpi^C_7)==0)&&((p1^C_1)==0))
		PUT (C_9);
	else if ((rpi&C_7)&&(p1&C_2)&&((rpi^C_7)==0)&&((p1^C_2)==0))
		PUT (C_9);
	else if ((rpi&C_7)&&(p1&C_3)&&((rpi^C_7)==0)&&((p1^C_3)==0))
		PUT (C_9);
	else if ((rpi&C_7)&&(p1&C_4)&&((rpi^C_7)==0)&&((p1^C_4)==0))
		PUT (C_9);
	else if ((rpi&C_7)&&(p1&C_6)&&((rpi^C_7)==0)&&((p1^C_6)==0))
		PUT (C_1);
	else if ((rpi&C_7)&&(p1&C_8)&&((rpi^C_7)==0)&&((p1^C_8)==0))
		PUT (C_1);
	else if ((rpi&C_7)&&(p1&C_9)&&((rpi^C_7)==0)&&((p1^C_9)==0))
		PUT (C_1);

	else if ((rpi&(C_7|C_9))&&(p1&(C_1|C_8))&&((rpi^(C_7|C_9))==0)&&((p1^(C_1|C_8))==0))
		PUT (C_3);
	else if ((rpi&(C_7|C_9))&&(p1&(C_3|C_8))&&((rpi^(C_7|C_9))==0)&&((p1^(C_3|C_8))==0))
		PUT (C_1);
	else if ((rpi&(C_7|C_9))&&(p1&(C_4|C_8))&&((rpi^(C_7|C_9))==0)&&((p1^(C_4|C_8))==0))
		PUT (C_3);
	else if ((rpi&(C_1|C_7))&&(p1&(C_3|C_4))&&((rpi^(C_1|C_7))==0)&&((p1^(C_3|C_4))==0))
		PUT (C_9);
	else if ((rpi&(C_1|C_7))&&(p1&(C_4|C_8))&&((rpi^(C_1|C_7))==0)&&((p1^(C_8|C_4))==0))
		PUT (C_3);
	else if ((rpi&(C_1|C_7))&&(p1&(C_4|C_9))&&((rpi^(C_1|C_7))==0)&&((p1^(C_4|C_9))==0))
		PUT (C_3);

	else if ((rpi&C_9)&&(p1&C_1)&&((rpi^C_9)==0)&&((p1^C_1)==0))
		PUT (C_7);
	else if ((rpi&C_9)&&(p1&C_2)&&((rpi^C_9)==0)&&((p1^C_2)==0))
		PUT (C_7);
	else if ((rpi&C_9)&&(p1&C_3)&&((rpi^C_9)==0)&&((p1^C_3)==0))
		PUT (C_7);
	else if ((rpi&C_9)&&(p1&C_4)&&((rpi^C_9)==0)&&((p1^C_4)==0))
		PUT (C_3);
	else if ((rpi&C_9)&&(p1&C_6)&&((rpi^C_9)==0)&&((p1^C_6)==0))
		PUT (C_7);
	else if ((rpi&C_9)&&(p1&C_7)&&((rpi^C_9)==0)&&((p1^C_7)==0))
		PUT (C_3);
	else if ((rpi&C_9)&&(p1&C_8)&&((rpi^C_9)==0)&&((p1^C_8)==0))
		PUT (C_3);

	else if ((rpi&(C_3|C_9))&&(p1&(C_1|C_6))&&((rpi^(C_3|C_9))==0)&&((p1^(C_1|C_6))==0))
		PUT (C_7);
	else if ((rpi&(C_3|C_9))&&(p1&(C_6|C_7))&&((rpi^(C_3|C_9))==0)&&((p1^(C_6|C_7))==0))
		PUT (C_1);
	else if ((rpi&(C_3|C_9))&&(p1&(C_6|C_8))&&((rpi^(C_3|C_9))==0)&&((p1^(C_6|C_8))==0))
		PUT (C_1);
	else if ((rpi&(C_7|C_9))&&(p1&(C_1|C_8))&&((rpi^(C_7|C_9))==0)&&((p1^(C_1|C_8))==0))
		PUT (C_3);
	else if ((rpi&(C_7|C_9))&&(p1&(C_3|C_8))&&((rpi^(C_7|C_9))==0)&&((p1^(C_3|C_4))==0))
		PUT (C_1);
	else if ((rpi&(C_7|C_9))&&(p1&(C_6|C_8))&&((rpi^(C_7|C_9))==0)&&((p1^(C_6|C_8))==0))
		PUT (C_1);

	else if (((rpi&C_1)&&(p1&(C_5|C_9)))&&(((rpi^C_1)==0)&&((p1^(C_5|C_9))==0)))
		if ((random_number ())%2)
			PUT (C_3);
		else
			PUT (C_7);
	else if (((rpi&C_3)&&(p1&(C_5|C_7)))&&(((rpi^C_3)==0)&&((p1^(C_5|C_7))==0)))
		if ((random_number ())%2)
			PUT (C_1);
		else
			PUT (C_9);
	else if (((rpi&C_7)&&(p1&(C_5|C_3)))&&(((rpi^C_7)==0)&&((p1^(C_5|C_3))==0)))
		if ((random_number ())%2)
			PUT (C_1);
		else
			PUT (C_9);
	else if (((rpi&C_9)&&(p1&(C_5|C_1)))&&(((rpi^C_9)==0)&&((p1^(C_5|C_1))==0)))
		if ((random_number ())%2)
			PUT (C_3);
		else
			PUT (C_7);

	else if ((rpi==0)&&((p1&C_1)||(p1&C_3)||(p1&C_7)||(p1&C_9)))
		PUT (C_5);
	else if (((rpi&C_5)&&((p1&(C_1|C_9))||(p1&(C_3|C_7))))&&(((rpi^C_5)==0)))
		switch (random_number())
		{
			case 0:
				PUT(C_2);
			case 1:	
				PUT(C_4);
			case 2:	
				PUT(C_6);
			case 3:
				PUT(C_8);
			default:
				PUT(C_8);
				PUT(C_4);
				PUT(C_2);
				PUT(C_6);
		}

	else if ((rpi==0)&&((p1&C_2)||(p1&C_4)||(p1&C_6)||(p1&C_8)))
		PUT (C_5);

	else if ((((rpi&C_5)&&(p1&(C_2|C_4)))&&((rpi^C_5)==0))&&(p1^(C_2|C_4))==0)
		PUT (C_1);
	else if ((((rpi&C_5)&&(p1&(C_2|C_6)))&&((rpi^C_5)==0))&&(p1^(C_2|C_6))==0)
		PUT (C_3);
	else if ((((rpi&C_5)&&(p1&(C_4|C_8)))&&((rpi^C_5)==0))&&(p1^(C_4|C_8))==0)
		PUT (C_7);
	else if ((((rpi&C_5)&&(p1&(C_6|C_8)))&&((rpi^C_5)==0))&&(p1^(C_6|C_8))==0)
		PUT (C_9);
	}
}

void PUT(int Ch)
{
	if((flag==0)&&((rpi&Ch)==0)&&((p1&Ch)==0))
	{
		rpi=rpi|Ch;
		flag++;
	}
}

int random_number (void)
{
	srand (time(NULL));
	return ((random ())>>8)&3;
}

void update_chars(unsigned char arreglito[],juan T[])
{
	
	char c=0; //contador
	for(;c<=9;c++)
	{
		if(p1&(1<<c))
		{
			arreglito[T[c].L]=((arreglito[T[c].L])|T[c].b);
		}
	}
	for(;c<=18;c++)
	{
		if(rpi&(1<<(c-9)))
		{
			arreglito[T[c].L]=((arreglito[T[c].L])|T[c].b);
		}
	}
}

int blink (int a,int b,int c,short *player)
{
	long i,j;
	for (i=8;i>0;i--)
	{
		(*player)^=(a|b|c);
		show ();
		usleep (160000);
	}
	return 1;
}

int tieblink (void)
{
	long i,j;
	short temp;
		for (i=4;i>0;i--)
	{
		temp=rpi;
		rpi=0;
		show ();
		usleep (170000);
		rpi=temp;
		temp=p1;
		p1=0;
		show ();
		usleep (170000);
		p1=temp;
	}
	return (1);
}
//hyq's eazy tongji pwn
//gcc  -fno-stack-protector -z execstack -o a.out 1.c 2.c 

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int val1 = 100;
int val2 = 200;
void happened(void);
char messeage[64];

void pwn_here()
{
	printf("you win?\n");
}

int temp;
int main()
{
	setbuf(stdin,NULL);
	setbuf(stdout,NULL);
	char say[30];
	printf("~~TWO WISHES~~\n");
	printf("first:\n");
	scanf("%d",&val1);
	if(val1==0)
		exit(0);
	printf("second:\n");	
	scanf("%d",&val2);
	if(val2==0x3ff00000)
		exit(0);
	printf("out of sight\n");
	printf("what happended? Can you tell me?\n");
	happened();
	if(val1 == 0 && val2 == 0x3ff00000)
	{
		
			printf("DO YOU WANNA HAVE A TYR?(0/1)\n");
			scanf("%d",&temp);
			if(temp == 0)
			{
				printf("%p",say);
			}
			else
			{
				read(0,say,30);
				write(1,say,30);
			}	
	
		printf("Thanks!What gift do you want!\n");
		scanf("%s",say);
	}
	else
	{
	printf("NO!I don't trust you!\n");
	}
	return 0;
}

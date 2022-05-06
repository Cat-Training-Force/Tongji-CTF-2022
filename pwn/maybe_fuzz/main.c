#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUFFLEN 40

void flag()
{
	char buff[100];
	FILE *fp = fopen("flag.txt", "r");
	fgets(buff, 33, fp);
	fclose(fp);
	printf("tjctf{%s}\n", buff);
}

void fuzz()
{
	char buff[BUFFLEN] = {0};
	printf("👀: %p\n", flag);
	puts("can you guess the position?");
	int r = rand() % 20;
	gets(&buff[r], 80);
	// gets(buff, 80);
	for (int i=0; i<BUFFLEN; ++i)
	{
		printf("%02X ", buff[i]);
	}
	putchar('\n');
}

int main()
{
	srand(time(NULL));
	fuzz();
	return 0;
}
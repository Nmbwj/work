#include<stdio.h>
#include<ctype.h>

int main(int argc, char *argv[])
{
	int c;
	while(--argc >0)
		printf("%s%s", *++argv, (argc>1)?" ": "");
	printf("\n");
	while((c= getchar()) != EOF)
		putchar(tolower(c));
	return 0;
}

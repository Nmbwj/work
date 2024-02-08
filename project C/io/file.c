#include<stdio.h>

int main(int argc, char *argv[])
{
	int c;
	FILE *fp;
	fp = fopen("./output","r");	/* the strucutre is: FILE *fopen(char *name, char *mode); */
	while((c = getc(fp)) != EOF)
		printf("%c",c);

	
	return 0;
}

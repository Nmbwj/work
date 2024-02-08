#include<stdio.h>
#include<stdlib.h>


int main(int argc, char **argv)
{

	FILE *fp;
	void filecopy(FILE *, FILE *);
	char *prog = *argv;

	if (argc == 1)
		filecopy(stdin,stdout);
	else
		while(--argc >0)
			if((fp = fopen(*++argv, "r")) == NULL){
				fprintf(stderr,"%s: can not open %s\n", prog, *argv);
				exit(1);
			}
			else
			{
				filecopy(fp,stdout);
				fclose(fp);
			}
	if(ferror(stdout))
	{
		fprintf(stderr, "%s: can not write to screen\n",prog);
		exit(2);
	}


	exit(0);
}

void filecopy(FILE *ifp, FILE *ofp)
{
	int c;
	while((c = getc(ifp)) !=EOF)
		putc(c,ofp);
	if(feof(ifp))
		fprintf(stdout,"---finished concatinating---\n");
}


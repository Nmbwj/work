#include<stdio.h>
#include<stdlib.h>

/* the prefix 'n' for function name is to distingush the function name*/


char nfgets(char *s, int max, FILE *ifp)
{
	register int c;
	register char *cs;

	cs = s;
	while(--max > 0 && (c = getc(ifp)) != EOF)
		if((*cs++ =c) == '\n')
			break;
	*cs= '\0';
	return (c == EOF && cs == s)? NULL : s;
}

int nfputs(char * s, FILE *ofp)
{
	int c;
	while (c = *s++)
		putc(c, ofp);
	return ferror(ofp)? EOF :0;
}

int ngetline(char *line, int max)
{
	if( nfgets(line,max,stdout) == NULL)
		return 0;
	else 
		return strlen(line);
}

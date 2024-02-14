#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc , char **argv)
{
	FILE *fp;
	int line;
	while(--argc >0)
	if((fp = fopen(*++argv,"r")) == NULL){
		line = __LINE__;
		line -= 1;
		fprintf(stderr,"Error on file %s: at line %d: \"%s\"\n",__FILE__,line,strerror(errno));
		exit(1);
		
	
	}
	exit(0);
}

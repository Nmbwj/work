#include<stdio.h>
#include<sys/file.h>
#include "syscall.h"
#include "error.h"
#include "seek.h"
int main(int argc, char **argv)
{
	int fd;
	long int pos;
	char * buf;

	if((fd = open(*++argv,O_RDONLY,0)) == -1) error("seek: can not open %s",*argv);
	get(fd,5,buf,BUFSIZ);
	fprintf(stdout,"The read: \n %s",buf);
	return 0;
}

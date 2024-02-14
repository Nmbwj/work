#include <stdio.h>
#include<unistd.h>
#include <sys/file.h>
#include "syscall.h"
#define PERMS 0666
#include "error.h"
int main(int argc , char **argv)
{
	int f1,f2,n;
	char buf[BUFSIZ];
	if(argc != 3) error("Usage: cp from to");
	if((f1 = open(*++argv,O_RDONLY,0)) == -1) error("cp: can not open %s",*argv);
	if((f2 = creat(*++argv,PERMS)) == -1) error("cp: can not create %s mode %03o",*argv,PERMS);

	while(n = read(f1,buf,BUFSIZ))
		if((write(f2,buf,n) != n))
				error("cp: write error on file %s",*argv);
	return 0;
}

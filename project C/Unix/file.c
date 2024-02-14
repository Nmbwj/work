#include <stdio.h>
#include<unistd.h>
#include "syscall.h"
#include <fcntl.h>

int main()
{
	int fd, reads;
	char buf[BUFSIZ];
	fd = open("../io/output",O_RDONLY,0);
	reads = read(fd,buf,BUFSIZ);
	write(1,buf,reads);
	fprintf(stdout,"%d is file discriptor for opened file output\n",fd);
	return 0;
}

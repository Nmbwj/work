#include<stdio.h>
#include<unistd.h>
#include<sys/file.h>
#include"syscall.h"

int get(int fd, long int pos, char *buf, int n)
{
	if(lseek(fd,pos,0)>=0)
		return read(fd,buf,n);
	else
		return -1;

}

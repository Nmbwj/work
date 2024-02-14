#include <stdio.h>
#include<unistd.h>
#include <fcntl.h>
#include "syscall.h"

int main(int argc, char ** argv)
{
	unlink(*++argv);
	return 0;
}

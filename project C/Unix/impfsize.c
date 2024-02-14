#include <stdio.h>
#include <string.h>
#include "syscall.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "dirent.h"
#include "error.h"

void dirwalk(char *, void (*fnc) (char *));

void fsize(char *name)
{
	struct stat stbuf;
	if (stat(name, &stbuf) == -1){
		error("fsize: can not access %s \n", name);
		return ;
	}
	if((stbuf.st_mode & S_IFMT ) == S_IFDIR)
		dirwalk (name, fsize);
	printf("%81d %s\n", stbuf.st_size, name);
}

void dirwalk (char * dir, void (*fcn)(char *))
{
	char name[PATH_MAX];
	struct dirent *dp;
	DIR *dfd;

	if((dfd = opendir(dir)) == NULL)
	{
		error("dirwalk: can not open %s\n", dir);
		return;
	}
	while (( dp = readdir(dfd)) != NULL)
	{
		if(strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") ==0 )
			continue; /* skip self and parent */
		if(strlen(dir)+strlen(dp->d_name)+2 > sizeof(name))
			error("dirwalk: name %s/%s too long\n",dir,dp->d_name);
		else
		{
			sprintf(name,"%s/%s", dir, dp->d_name);
			(*fcn)(name);
		}
	}
	closedir(dfd);
}

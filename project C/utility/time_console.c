#include<stdio.h>
#include<time.h>

int main()
{
	time_t timer;
	time(&timer);

	printf("Local time in EAT: %s",ctime(&timer));
	return 0;
}

#include<stdio.h>
struct {
	/*see the difference by replacing the usigned int :0 with unsigned int is_extern :1*/
	unsigned int is_keyword :1;
	unsigned int  :0;
	unsigned int is_static :1;
} flags;
int main()
{	
	/*
	flags.is_keyword = 1; 
	flags.is_extern = 1;
	flags.is_static = 1;
	
	printf("flag1: %u\n",flags.is_keyword);
	printf("flag2: %u\n",flags.is_extern);
	printf("flag3: %u\n",flags.is_static);
	*/

	printf("size of struct flags: %zu bytes\n", sizeof flags);
	return 0;
}


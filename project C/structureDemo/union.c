#include<stdio.h>
typedef int INT;
union u_tag
{
	int ival;
	float fval;
	char *sval;
} u;

int main()
{
	/*u.ival=34;*/
	u.fval= 342.2;
	printf("%f \n",u.fval);
	return 0;
}

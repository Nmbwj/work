#include <cstdlib>
#include <iostream>
#include <time.h>
#include "die.h"
die::die()
{
	num =1;
	srand(time(0));
}
int die::roll()
{
	num = rand()%6+1;
	return num;
}
int die::getNum()const
{
	return num;
}
/*
 * to compile into the object code use g++ -c dieimp.cpp
 */

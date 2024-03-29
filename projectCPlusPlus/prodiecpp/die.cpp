#include <iostream>
#include "die.h"
using namespace std;
int main()
{
die die1;
die die2;
//Line 1
//Line 2
//Line 3
cout << "Line 4: die1: " << die1.getNum() << endl; //Line 4
cout << "Line 5: die2: " << die2.getNum() << endl; //Line 5
cout << "Line 6: After rolling die1: "<< die1.roll() << endl; //Line 6
cout<<"Line 7: After rolling die2: "<<die2.roll() << endl;
cout<<"Line 8: The sum of the numbers rolled"<<" by the dice is: "<<die1.getNum() + die2.getNum() << endl;
cout << "Line 9: After again rolling, the sum of "<< "the numbers rolled is: "<< die1.roll() + die2.roll() << endl;
return 0;
}//end main

/* 
 * to compile the bin file use g++ -o die die.cpp dieimp.o
 *
 */ 

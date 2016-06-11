#ifndef DIVISON_TEST
#define DIVISON_TEST 


#include <iostream>
#include <cmath>
#include <cstring>
#include <bitset>

using namespace std;

int number_of_needed_bits(int h)
{
	if (h<=1){return 1;}
	return floor( log2(h) + 1 );
}


int correct_rounding (int x, int divisor)
{
	int n = number_of_needed_bits(x); //n is the precision of the input x, we assum q=n
	return n + 1 + ceil(log2(divisor)); 
}


#endif
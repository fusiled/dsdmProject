#ifndef DIVISON_TEST
#define DIVISON_TEST 


#include <iostream>
#include <cmath>
#include <cstring>
#include <bitset>

using namespace std;

int number_of_needed_bits (int x, int divisor)
{
	int n = log2(x); //n is the precision of the input x, we assum q=n
	return n + 1 + ceil(log2(divisor)); 
}

#endif
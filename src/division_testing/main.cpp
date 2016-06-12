#include <iostream>
#include "division_test.h"
#include <bitset>
#include <cmath>

#ifndef MAX_BITS 
#define MAX_BITS 32
#endif

using namespace std;

int main(int argc, char const *argv[])
{
	int x = 15, b = 3;
	int bits_needed = correct_rounding(x,b);
	int first_shift, partial_result, final_result;
	cout<<"If we want to make the operation "<<x<<"/"<<b<<" = "<<x/b<<endl;
	cout<<"We need "<<bits_needed<<" bits for the result"<<endl;
	//float result = computeMult(15,32,build(1,3));
	first_shift = pow(2, bits_needed) * x;
	cout<<"1) Shift to left "<<x<<" of "<<bits_needed<<" bits: "<<bitset<MAX_BITS>(first_shift)<<endl;
	partial_result = first_shift / b;
	cout<<"2) Divide the prevoius result for "<<b<<": "<<bitset<MAX_BITS>(partial_result)<<endl;
	final_result = partial_result >> bits_needed;
	cout<<"3) Shift to right the prevoius result of "<<bits_needed<<": "<<bitset<MAX_BITS>(final_result)<<endl;
	return 0;
}
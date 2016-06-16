
#include "RationalConstants.h"
#include "PeriodicRepresentation.h"
#include "division_testing/division_test.h"
#include "FixedPoint.h"
#include <map>
#include <iostream>
#include <bitset>

#define TEST_SET_SIZE 4
#ifndef MAX_BITS 
#define MAX_BITS 32
#endif


using namespace RationalConstants;
using namespace std;


long int TestSet[][7]=
{
	//a,   b,   e,   h,   p,   s  round
	{ 15,  3,   0,   0,   35,  6,  8},
	{ 30,  10,  0,   0,   1,   2,  7},
	{ 14,  14, -1,   1,   6,   3,  4},
	{ 14,   3,  0,   2,   1,   2,  6},
};


bool testBuild(int testElement[]);
bool testDivision(int testElement[]);
bool testShiftDivision(long int testElement[]);

int main(int argc, char const *argv[])
{
	for (int i=0; i<TEST_SET_SIZE; i++)
	{
		if (!testShiftDivision(TestSet[i]))
		{
			cout<<"test error! check "<<TestSet[0]<<"/"<<TestSet[1]<<endl;
		}
		else
		{
			cout<<"Test Successful"<<endl;
		}
	}


	return 0;
}


bool testBuild(int testElement[])
{
	PeriodicRepresentation ratNum= build(testElement[0],testElement[1]);
	int * tuple=ratNum.getTuple();
	for (int i=0; i<4;i++)
	{

		//cout<<"comparing "<<bitset<32>(tuple[i])<<" and "<<testElement[i+2]<<endl;
		if (tuple[i]!=testElement[i+2])
		{
			cout<<"error in testBuild!"<<endl;
			return false;
		}
	}
	delete[] tuple;
}


bool testDivision(int testElement[])
{
	FixedPoint fp = computeDivision(testElement[0], testElement[1]);
	#ifdef DEBUG
		cout<<testElement[0]<<"/"<<testElement[1]<<"="<<((float)testElement[0])/((float)testElement[1])<<endl;
		cout<<"computed result:"<<fp.toString()<<endl;
		cout<<"raw result:   "<<fp.rawString()<<endl;
	#endif
}


bool testShiftDivision(long int testElement[] )
{
	long int x = testElement[0];
	long int b = testElement[1];
	long int expectedResult=testElement[0]/testElement[1];
	long int bits_needed = correct_rounding(x,b);
	long int first_shift, partial_result, final_result;
	first_shift = pow(2, bits_needed) * x;
	partial_result = first_shift / b;
	final_result = partial_result >> bits_needed;
	#ifdef DEBUG
		cout<<"We want to make the operation "<<x<<"/"<<b<<" = "<<expectedResult<<endl;
		cout<<"bits_needed: "<<bits_needed<<endl;
		cout<<"1) Shift to left "<<x<<" of "<<bits_needed<<" bits"<<endl;
		cout<<"left_shift:     "<<bitset<MAX_BITS>(first_shift)<<endl;
		cout<<"2) Divide the prevoius result for "<<b<<endl;
		cout<<"partial_result: "<<bitset<MAX_BITS>(partial_result)<<endl;
		cout<<"3) Shift to right the previous result of "<<bits_needed<<endl;
		cout<<"final_result:   "<<bitset<MAX_BITS>(final_result)<<endl;
	#endif
	return expectedResult == final_result;
}
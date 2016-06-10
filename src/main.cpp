
#include "RationalConstants.h"
#include "PeriodicRepresentation.h"
#include "FixedPoint.h"
#include <map>
#include <iostream>
#include <bitset>

#define TEST_SET_SIZE 4


using namespace RationalConstants;
using namespace std;


int TestSet[][6]=
{
	//a,   b,   e,   h,   p,   s
	{ 5,   9,   0,   0,   35,  6},
	{ 10,  30,  0,   0,   1,   2},
	{ 13,  14, -1,   1,   6,   3},
	{ 7,    3,  0,   2,   1,   2}
};


bool testBuild(int testElement[]);
bool testDivision(int testElement[]);

int main(int argc, char const *argv[])
{
	cout<<"Testing build function"<<endl;
	for (int i=0; i<TEST_SET_SIZE; i++)
	{
		testBuild(TestSet[i]);
	}

	cout<<"Testing shift-and-add algorithm"<<endl;
	for (int i=0; i<TEST_SET_SIZE; i++)
	{
		testDivision(TestSet[i]);
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
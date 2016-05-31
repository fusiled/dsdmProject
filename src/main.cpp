
#include "RationalConstants.h"
#include "PeriodicRepresentation.h"
#include <map>
#include <iostream>
#include <bitset>


using namespace RationalConstants;
using namespace std;


int TestSet[][6]=
{
	{5,9,0,0,35,6},
	{10,30,0,0,1,2},
	{13,14,-1,1,6,3}
};


bool testBuild(int testElement[]);

int main(int argc, char const *argv[])
{
	cout<<"Testing build function"<<endl;
	for (int i=0; i<3; i++)
	{
		testBuild(TestSet[i]);
	}

	cout<<"Testing shift-and-add algorithm"<<endl;
	float x=3.5;
	float result = computeMult(1,32,24,build(7,5));
	cout <<"result"<<result << endl;
	cout <<"expected result:"<< (float) 7/5 <<endl;

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
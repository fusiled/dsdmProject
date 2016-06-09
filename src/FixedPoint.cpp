#include "FixedPoint.h"
#include <string>
#include <sstream>
#include <iostream>
#include <bitset>
#include <cmath>

#ifndef CHUNK_SIZE
#define CHUNK_SIZE 32
#endif


using namespace std;

//returns bit of the number at desired position
bool getBit2(unsigned int number, int position)
{
	if (position >= 32 || position < 0)
	{
		return -1;
	}
	return ((number >> position) & (0x1));
}


FixedPoint::FixedPoint(unsigned int p_chunk, int p_point_position):
	chunk{p_chunk},
	point_position{p_point_position}
	{/*nothing to do*/}

string FixedPoint::rawString()
{
	stringstream ss;
	ss<<bitset<CHUNK_SIZE>(chunk)<<" with point before "<<point_position;
	return ss.str();
}

string FixedPoint::toString()
{
	stringstream ss;
	ss << (chunk>>point_position);
	float decValue=0;
	for (int i=point_position; i>0; i--)
	{
		int exponent = point_position - i + 1;
		bool bit = getBit2(chunk, i - 1);
		float partial= bit*pow(2, - exponent);
		decValue += partial;
	}
	ss<<" + ";
	ss<<decValue;
	return ss.str();
}

#ifndef FIXEDPOINT_H
#define FIXEDPOINT_H

#include <string>


/*
* The class implements a sort of fixed point number using an unsigned int (32 bits).
* point positions tells where the point is (trivial). The LEAST significant bit is the
* one at the right. If the number is a pure int the point_position = 0 . If the number
* is only composed by its decimal part point_position = 31. Use your wisdom to master
* the other cases...
*/

class FixedPoint
{
public:
	FixedPoint(unsigned int p_chunk, int p_point_position);
	virtual ~FixedPoint() {}

	//This will output a string with the chunk plus the info about the
	//point position
	std::string rawString();


	//This will output a string containing the decimal representation of the 
	//instance
	std::string toString();


private:
	unsigned int chunk;
	int point_position;


};

#endif
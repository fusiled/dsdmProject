#include <iostream>
#include <limits>
#include <string>

using namespace std;

string toBinStr(unsigned int val)
{
	// mask has only the leftmost bit set.
	unsigned int mask = 1u << (std::numeric_limits<unsigned>::digits-1) ;

	// skip leading bits that are not set.
	while ( 0 == (val & mask) && mask != 0 )
		mask >>= 1 ; // shift all bits to the right by 1

	string binStr ;
	binStr.reserve(std::numeric_limits<unsigned>::digits+1) ;

	do
	{
		// add a '1' or '0' depending the current bit.
		binStr += static_cast<char>(val & mask) + '0' ;

	} while ( (mask>>=1) != 0 ) ; // next bit, when mask is 0 we've processed all bits

	return binStr ;
}

int main()
{
   for(unsigned int i = 0; i < 128; i++)
   {
      string entity = toBinStr(i) ;
      cout << entity << '\n' ;
   }
}
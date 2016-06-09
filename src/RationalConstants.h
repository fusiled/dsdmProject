#ifndef RATIONALCONSTANTS_H
#define RATIONALCONSTANTS_H 


#include <iostream>
#include "PeriodicRepresentation.h"
#include "FixedPoint.h"
#include <cmath>
#include <cstring>
#include <bitset>

#define CHUNK_SIZE 32

using namespace std;

namespace RationalConstants
{

	//returns a periodic representation of the number a/b
	PeriodicRepresentation build(int a, int b);
	//compute the mult
	unsigned int computeMult(unsigned int x, int w0, PeriodicRepresentation ratConst ); //x must be specified better.. evaluate a generic	
	FixedPoint computeDivision(int x, int b );
	//needed?
	//N = precision of x
	//Q = precision of the result
	int correctRounding(int N, int Q);	
}



int neededBits(int number)
{
	if (number<=1) return 1;
	return floor(log2(number))+1;
}

//returns bit of the number at desired position
bool getBit(unsigned int number, int position)
{
	if (position >= 32 || position < 0)
	{
		return -1;
	}
	return ((number >> position) & (0x1));
}


unsigned int reverseBits(unsigned int input)
{
    unsigned int output = input;
    for (int i = sizeof(input) * 8 - 1; i; --i)
    {
        output <<= 1;
        input >>= 1;
        output |= input & 1;
    }
    return output;
}



int gcd ( int a, int b )
{
  int c;
  while ( a != 0 ) {
     c = a; a = b%a;  b = c;
  }
  return b;
}

void simplify(int a, int b, int * c, int * d)
{
	int value=1;
	do{
		value = gcd(a,b);
		a=a/value;
		b=b/value;
	} while (value !=1);
	*c=a;
	*d=b;
}

PeriodicRepresentation RationalConstants::build(int a, int b)
{
		#ifdef DEBUG
		cout<<"Building PeriodicRepresentation for "<<a<<"/"<<b<<endl;
		#endif
		//reduce a/b into c/d
		int c,d;
		simplify(a, b, &c, &d);
		#ifdef DEBUG
		cout<<"Simplified fraction: "<<c<<"/"<<d<<endl;
		#endif
		//begin decomposition
		int e = 0 ;
		int h, p, s; 
		//avoid c,d divisible by zero -> generate e
		while ( c % 2 == 0 )
		{
			c = c / 2 ;
			e = e + 1 ;
		}
		while ( d % 2 == 0 )
		{
			d = d / 2 ;
			e = e - 1 ;
		}
		//now a/b = 2^e * c/d with both c and d odd
		h = c / d;
		c = c % d;
		//now a/b = h + c/d with c < d
		s = 1;
		//if true a/b has finite binary representation
		if ( d == 1 )
		{
			p = 0;
		}
		else
		{
			//compute periodic pattern
			int t = 2;
			while ( t % d != 1 )
			{
				s = s + 1;
				t = 2 * t;
			}
			p = c * t / d ;
		}
		#ifdef DEBUG
		cout<<"Generating PeriodicRepresentation instance with (e="<<e<<", h="<<h<<", p="<<p<<", s="<<s<<")"<<endl;
		#endif
		return PeriodicRepresentation(e, h, p, s);
}


unsigned int RationalConstants::computeMult(unsigned int x, int w0, PeriodicRepresentation ratConst )
{
	cout<<"past x:       "<<bitset<CHUNK_SIZE>(x)<<endl;
	cout<<"PeriodicRepresentation:"<<endl;
	//initialize PeriodicRepresentation variables
	int s = ratConst.getS();
	int p = ratConst.getP();
	int h = ratConst.getH();
	int wh= ratConst.getHWidth();

	//save pi approximations in this array
	unsigned int * pi = new unsigned int[ (int) ceil(log2(w0-wh)) ];
	cout<<"s="<<s<<" p="<<p<<" w0="<<w0<<endl;
	cout<<"------------------compute-pi-vector-----------"<<endl;
	int i=0;
	int j=0;
	int trailZeroes=0;
	pi[0]= ( p * x )<<(CHUNK_SIZE-s);
	//remove useless bits and save trailZeroes for the future
	if ( getBit(pi[0],CHUNK_SIZE-1) == 0 )
	{
		pi[0] <<= 1;
		trailZeroes++;
	}
	cout<<"pi["<<i<<"]:        "<< bitset<CHUNK_SIZE>(pi[0]) <<endl;

	//iterate until we have generated enough approximations of the decimal part. 
	//Save the result of the iteration in pi[i+1]
	while ( s<<i < (w0 - wh) && j<=i-1  )
	{
		pi[i+1] = pi[i] + ( pi[i] >> ( s<<i) ) ;
		if (getBit(pi[0],CHUNK_SIZE-1)==0) pi[0] <<=1 ;
		cout<<"pi["<<i+1<<"]:        "<<bitset<CHUNK_SIZE>(pi[i+1])<<endl;
		i++;
		cout<<"j condition: " <<( s<<(i-1) )*s<<" < "<<w0<<" <= "<< (s<<i)*s<<" ? ";
		if  (
				( ( s<<(i-1)*s ) < w0 )
				&&
				(w0 <= (s<<i)*s )
			)
		{
			cout<<"YES \\(..)/"<<endl;
			j=0;
			cout<<"Testing "<<(s<<i-1)+(s<<j) <<" >= "<< w0 -wh <<endl; 
			while ( (s<<i-1)+(s<<j) < (w0-wh) )
			{
				j++;
				cout<<"Testing "<<(s<<i-1)+(s<<j) <<" >= "<< w0-wh <<endl; 
			}
			//we have found a suitable j.. exit from the cycle
			if (j>0 && j<=i) break;
		}
		else
		{
			cout<<"no ):"<<endl;
		}
	}
	cout<<"------------generating-result-----------------"<<endl;
	cout<<"s: "<<s<<", i: "<<i<<endl;
	unsigned int r;
	long int integerR = (h*x)<<(CHUNK_SIZE-wh);
	cout<<"shifted h*x:  "<<bitset<CHUNK_SIZE>(integerR)<<endl;
	//use j if it's possible
	if (j>0){
		//print addends
		cout<<"EXPLOIT j OPTMIZATION"<<endl;
		cout<<"sel pi[j]: "<<j<<": "<<bitset<CHUNK_SIZE>(pi[j])<<endl;
		cout<<"sel pi[i]: "<<i-1<<": "<<bitset<CHUNK_SIZE>(pi[i-1])<<endl;
		int shiftedJ=pi[j]>>(wh+trailZeroes);
		int shiftedI=pi[i-1]>>((s<<j)+wh+trailZeroes);
		cout<<"shifted j:    "<<bitset<CHUNK_SIZE>(shiftedJ)<<endl;
		cout<<"shifted i:    "<<bitset<CHUNK_SIZE>(shiftedI)<<endl;
		r = integerR+shiftedJ+shiftedI;
	}
	else
	{
		cout<<"pi["<<i<<"]:        "<<bitset<CHUNK_SIZE>(pi[i])<<endl;
		r = integerR+(pi[i]>>wh+trailZeroes);
	}
	//this will be the final result
	delete [] pi;
	cout<<"returning     "<<bitset<CHUNK_SIZE>(r)<<endl;
	return r;
}


//in this functions pi approximations follow the rule of FixedPoint class
FixedPoint RationalConstants::computeDivision(int x, int b )
{
	cout<<"**************Computing result of "<<x<<"/"<<b<<"**************"<<endl;
	simplify(x,b, &x, &b);
	PeriodicRepresentation divisor=build(1,b);
	int xBits = neededBits(x);
	int w0 = xBits + 1 + ceil(log2(b));
	//int w0 = 32;
	cout<<"CORRECT ROUNDING IS "<<w0<<" BITS"<<endl;
	int p  = divisor.getP();
	int s  = divisor.getS();
	int i  = 0;
	int pointPosition;

	//save pi approximations in this array
	unsigned int * pi = new unsigned int[ (int) ceil(log2(w0)) ];

	pi[0] =  ( p * x );
	pointPosition = s ;

	#ifdef DEBUG
	cout<<"pi["<<i<<"]:        "<<bitset<CHUNK_SIZE>(pi[i])<<" point before "<<pointPosition<<endl;
	#endif
	//iterate until we have generated enough approximations of the decimal part. 
	//Save the result of the iteration in pi[i+1]
	while ( s<<i < w0 )
	{
		pi[i+1] = pi[i] + (pi[i]<<(s<<i));
		pointPosition=pointPosition+(s*(i+1));
		#ifdef DEBUG
		cout<<"pi["<<i+1<<"]:        "<<bitset<CHUNK_SIZE>(pi[i+1])<<" point before "<<pointPosition<<endl;
		#endif
		i++;
	}
	//remove useless bits. This is done in a dumb way.
	unsigned int piCorrected= pi[i];
	//do a copy and left shift until we don't lose useful bits
	unsigned int piCorrectedCopy=piCorrected;
	int pointPositionCopy=pointPosition;
	while(getBit(piCorrectedCopy, CHUNK_SIZE-1) == 0 && pointPosition < CHUNK_SIZE )
	{
		piCorrectedCopy<<=1;
		pointPositionCopy++;
	}
	//compute occupiedBits and do the shift to adjust bits
	int occupiedBits = CHUNK_SIZE - ( pointPositionCopy - pointPosition );
	piCorrected>>= occupiedBits - w0;
	pointPosition= pointPosition - occupiedBits + w0;
	//return instance of FixedPoint
	FixedPoint r(piCorrected,pointPosition);
	delete [] pi;
	return r;


}


#endif
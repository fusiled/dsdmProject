#ifndef RATIONALCONSTANTS_H
#define RATIONALCONSTANTS_H 


#include <iostream>
#include "PeriodicRepresentation.h"
#include <cmath>
#include <cstring>
#include <bitset>

using namespace std;

namespace RationalConstants
{

	//returns a periodic representation of the number a/b
	PeriodicRepresentation build(int a, int b);
	//compute the mult
	unsigned int computeMult(int number, int w0, int significandSize, PeriodicRepresentation ratConst ); //x must be specified better.. evaluate a generic	
	
	//needed?
	//N = precision of x
	//Q = precision of the result
	int correctRounding(int N, int Q);	
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
		cout<<"Building PeriodicRepresentation for "<<a<<"/"<<b<<endl;
		//reduce a/b into c/d
		int c,d;
		simplify(a, b, &c, &d);
		cout<<"Simplified fraction: "<<c<<"/"<<d<<endl;
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
		cout<<"Generating PeriodicRepresentation instance with (e="<<e<<", h="<<h<<", p="<<p<<", s="<<s<<")"<<endl;
		return PeriodicRepresentation(e, h, p, s);
}



unsigned int RationalConstants::computeMult(int number, int w0, int significandSize, PeriodicRepresentation ratConst )
{
	//initialize PeriodicRepresentation variables
	cout<<"past float:   "<<bitset<32>(number)<<endl;
	int s = ratConst.getS();
	int p = ratConst.getP();
	int h = ratConst.getH();
	int wh= ratConst.getHWidth();
	int x = number;
	int * pi = new int[ (int) ceil(log2(w0-wh)) ];
	cout<<"s="<<s<<" p="<<p<<endl;
	cout<<"------------------compute-pi-vector-----------"<<endl;
	//with optimization
	pi[0]= ( p * x );
	int offset=0;
	while(pi[0] % 2 ==0)
	{
		pi[0]=pi[0]>>1;
		offset++;
	}
	cout<<"pi[0]:        "<< bitset<32>(pi[0]) <<endl;

	int i=0;

	while ( s<<i < w0 - wh )
	{
		cout<<"shifted part: "<< bitset<32>( pi[i] << ( s<<i )) <<endl;
		pi[i+1] = pi[i] + ( pi[i] << ( s<<i) ) ;
		cout<<"pi[i+1]:      "<<bitset<32>(pi[i+1])<<endl;
		i++;
	}
	//trivial implementation to find j. evaluate a replacement
	cout<<"----------compute-j---------------------------"<<endl;
	unsigned int j=0;
	while ( s<<( i + j ) < ( w0 - wh ) ) j++; 
	cout<<"j: "<<j<<endl;
	if (j>0){
		cout<<"select pi["<<j<<"]: "<<bitset<32>(pi[j])<<endl;
	}
	cout<<"------------generating-result-----------------"<<endl;
	//this will be the final result
	unsigned int r;
	cout<<"h*x:          "<<bitset<32>(h*x)<<endl;
	cout<<"s: "<<s<<", i: "<<i<<endl;
	cout<<"pi["<<i<<"]:        "<<bitset<32>(pi[i])<<endl;
	r = ( (h*x)<<(s<<i)-offset)+(pi[i]);
	delete [] pi;
	cout<<"returning     "<<bitset<32>(r)<<endl;
	return r;
}


#endif
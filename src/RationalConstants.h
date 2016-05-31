#ifndef RATIONALCONSTANTS_H
#define RATIONALCONSTANTS_H 


#include <iostream>
#include "PeriodicRepresentation.h"
#include <cmath>

using namespace std;

namespace RationalConstants
{

	//returns a periodic representation of the number a/b
	PeriodicRepresentation build(int a, int b);
	//compute the mult
	float computeMult(int w0, int wh, PeriodicRepresentation ratConst, float x ); //x must be specified better.. evaluate a generic	
	unsigned int computeMult2(int w0, int wh, PeriodicRepresentation ratConst, int x ); //x must be specified better.. evaluate a generic	
	
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



float RationalConstants::computeMult(int w0, int wh, PeriodicRepresentation ratConst, float x )
{
	int s = ratConst.getS();
	int p = ratConst.getP();
	int h = ratConst.getH();
	float * pi = new float[ (int) log2(w0-wh) ];
	cout<<"s="<<s<<" p="<<p<<endl;
	pi[0]=( pow(2,(-s)) ) * p * x;
	cout<<"pi[0]="<<pi[0]<<endl;

	int i=0;

	while ( (pow(2,i))*s < w0 )
	{
		pi[i+1] = pi[i] +  pow( 2, ( pow(-2, i ) ) * s ) * pi[i] ;
		i++;
	}
	//trivial implementation to find j. evaluate a replacement
	int j=0;
	while ( ( pow(2,i) + pow(2,j) ) * s < ( w0 - wh ) ) j++; 

	float r;

	if (j <= i)
	{
		r= ( h*x + pi[j] ) + pow( 2, ( pow(-2, i ) ) * s ) * pi[i];
	} 
	else
	{
		r= h*x + ( pi[i]  + pow( 2, ( pow(-2, i ) ) * s ) * pi[i] );
	}
	delete [] pi;
	return r;
}


unsigned int RationalConstants::computeMult2(int w0, int wh, PeriodicRepresentation ratConst, int x )
{
	int s = ratConst.getS();
	int p = ratConst.getP();
	int h = ratConst.getH();
	int * pi = new int[ (int) log2(w0-wh) ];
	cout<<"s="<<s<<" p="<<p<<endl;
	cout<<"p * x = "<< p*x<<endl;
	pi[0]= ( p * x );
	cout<<"pi[0]="<<pi[0]<<endl;

	unsigned int i=0;

	while ( s<<i < w0 )
	{
		cout<<"power: "<<(int) pow(2,i)*s<<endl;
		cout<<"shifted power: "<< (s<<i) <<endl;
		cout<<"shifted part: "<< ( pi[i] << ( (int) pow(2,i)*s ) ) <<endl;
		pi[i+1] = pi[i] +   ( pi[i] << ( s<<i) ) ;
		cout<<"pi[i+1]="<<pi[i+1]<<endl;
		i++;
	}
	//trivial implementation to find j. evaluate a replacement
	unsigned int j=0;
	while ( s<<( i + j ) < ( w0 - wh ) ) j++; 

	unsigned int r;

	if (j <= i)
	{
		r= ( (h*x)<<((s<<i)+s) + pi[j] ) + pi[i] << ( s<<i );
	} 
	else
	{
		r= (h*x)<< (s<<i) + ( pi[i]  + pi[i] << ( s<<i ) );
	}
	delete [] pi;
	cout<<"returning "<<r<<endl;
	return r;
}


#endif
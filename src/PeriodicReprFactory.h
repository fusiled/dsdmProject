#include "PeriodicRepresentation.h"

namespace RationalConstants
{

	//returns a periodic representation of the number a/b
	PeriodicRepresentation & build(int a, int b);
	//compute the mult
	float computeMult(int w0, int wh, PeriodicRepresentation & ratConst, float x ); //x must be specified better.. evaluate a generic	
	//needed?
	//N = precision of x
	//Q = precision of the result
	int correctRounding(int N, int Q);	
}

PeriodicRepr & PeriodicReprFactory::build(int a, int b)
{
		//reduce a/b into c/d
		int c,d;
		simplify(a, b, c, d);
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
			t = 2;
			while ( t % d != 1 )
			{
				s = s + 1;
				t = 2 * t;
			}
			p = c * t / d ;
		}
		return PeriodicRepr(e, h, p, s);
}



float computeMult(int w0, int wh, PeriodicRepr & ratConst, float x )
{
	int s = PeriodicRepr.getS();
	int pi = new int[log(2,w0-wh)];

	int pi[0]=( 2^(-s) ) * p * x;	

	int i=0;

	while ( (2^i)*s < w0 )
	{
		pi[i+1] = pi[i] + ( ( 2^ ( -2 ^ i ) ) * s ) * pi[i] ;
		i++;
	}
	//trivial implementation to find j. evaluate a replacement
	int j=0;
	while ( ( 2^i + 2^j ) * s < ( w0 - wh ) ) j++; 

	int r;

	if (j <= i)
	{
		r= ( h*x + pi[j] ) + ( ( 2^ ( -2 ^ i ) ) * s ) * pi[i];
	} 
	else
	{
		r= h*x + ( pi[i]  + ( ( 2^ ( -2 ^ i ) ) * s ) * pi[i] );
	}
	delete [] pi;
	return r;
}
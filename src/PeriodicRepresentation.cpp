#include "PeriodicRepresentation.h"

PeriodicRepresentation::PeriodicRepresentation(int pE, int pH, int pP, int pS):
	s{ pS },
	p{ pP },
	h{ pH },
	e{ pE }
	 {/*nothing to do*/}


//getters
int PeriodicRepresentation::getS() const {return s;}
int PeriodicRepresentation::getP() const {return p;}
int PeriodicRepresentation::getH() const {return h;}
int PeriodicRepresentation::getE() const {return e;}
int * PeriodicRepresentation::getTuple() const
{
	int * retTuple=new int[4];
	retTuple[0]=e;
	retTuple[1]=h;
	retTuple[2]=p;
	retTuple[3]=s;
	return retTuple;
}
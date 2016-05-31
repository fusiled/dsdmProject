#include "PeriodicRepresentation.h"

PeriodicRepr::PeriodicRepr(int pS, int pP, int pH=0, int pE=0):
	s{ pS },
	p{ pP },
	h{ pH },
	e{ pE }
	 {/*nothing to do*/}


//getters
int PeriodicRepr::getS() const {return s;}
int PeriodicRepr::getP() const {return p}
int PeriodicRepr::getH() const {return h;}
int PeriodicRepr::getE() const {return e;}
#include "PeriodicRepresentation.h"

PeriodicRepresentation::PeriodicRepresentation(int pS, int pP, int pH, int pE):
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
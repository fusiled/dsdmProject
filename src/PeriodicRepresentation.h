#ifndef PERIODICREPRESENTATION_H
#define PERIODICREPRESENTATION_H 
/**
Periodic representation of a ftractiona number. Probably a struct would have done
the same job without additional payload
Default copy constructor should be ok (all attributes are int)
**/


class PeriodicRepresentation{
	
	public:
		PeriodicRepresentation(int pS, int pP, int pH, int pE);
		//avoid destructor inheritance
		virtual ~PeriodicRepresentation() {}
		//getters
		int getS() const;
		int getP() const;
		int getH() const;
		int getE() const;
		int * getTuple() const;



	private:
		//size of the period
		const int s;
		//the period
		const int p;
		//the header = the natural part of the fraction
		const int h;
		//scaling factor
		const int e;


};


#endif
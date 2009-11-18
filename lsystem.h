#ifndef LSYSTEM_H
#define LSYSTEM_H

#include "calc.h"
#include "iteratator3.h"
#include "alphabet.h"
#include "colormap.h"

struct LSystem{
	LSystem();
	virtual ~LSystem();

	Alphabet* ab;
	Calc* c;
	SIterator* it;
	ColorMap* cm;
	double angle;
	double startlength;
	double startthick;
};

#endif // LSYSTEM_H

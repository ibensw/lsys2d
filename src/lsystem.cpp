#include "lsystem.h"
#include <math.h>

LSystem::LSystem(){
	ab=new Alphabet();
	c=new Calc(ab);
	it=new SIterator(ab);
	cm=new ColorMap();
	angle=M_PI/2.0;
	startlength=1.0;
	startthick=0.1;
}

LSystem::~LSystem(){
	delete cm;
	delete it;
	delete c;
	delete ab;
}

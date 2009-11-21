#include "alphabet.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

Alphabet::Alphabet():
	alphatable(new action[256])
{
	memset(alphatable, IDLE, 256*sizeof(action));
	alphatable['+']=TURNL;
	alphatable['-']=TURNR;
	alphatable['&']=PITCHD;
	alphatable['^']=PITCHU;
	alphatable['/']=ROLLR;
	alphatable['\\']=ROLLL;
	alphatable['|']=FULLTURN;
	alphatable['[']=PUSH;
	alphatable[']']=POP;
	alphatable['{']=POLYSTART;
	alphatable['}']=POLYEND;
	alphatable['(']=PARASTART;
	alphatable[')']=PARAEND;
	alphatable['!']=THICKLESS;
	alphatable['?']=THICKMORE;
	alphatable['\'']=LENGTHLESS;
	alphatable['"']=LENGTHMORE;
	alphatable['c']=COLOR;
	alphatable['F']=DRAW;
	alphatable['f']=MOVE;
	alphatable['Z']=DRAWHALF;
	alphatable['z']=MOVEHALF;
}

Alphabet::~Alphabet(){
	delete alphatable;
}

void Alphabet::setAlphabet(const action a, const string s){
	unsigned int len=s.length();
	for (unsigned int i=0; i<len; ++i){
		alphatable[(unsigned int)s[i]]=a;
	}
}

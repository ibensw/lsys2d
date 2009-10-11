#include "iterator.h"

Iterator::Iterator()
{
}

void Iterator::CountChars(){
	for (int i=0; i<256; ++i){

	}
}

void Iterator::addRule(char f, string r){
	 rules.insert(pair<char,StringStat>(f,StringStat(r)));
}

Iteration::Iteration(Iterator *it, char x, unsigned long depthleft):
		location(0), depth(depthleft), main(it), sub(0), str(it->getRule(x))
{}

Iteration::~Iteration(){
	delete sub;
}

char Iteration::next(){
	char x;
	if (depth==0)
		return str[location++];

	if (sub)
		x=sub->next();

	if (sub && x)
		return x;

	if (sub){ // && !x
		delete sub;
		++location;
	}

	//!sub
	if (main->NoRule(str[location])){
		return str[location++];
	}

	//!sub && rule exists
	sub=new Iteration(main, str[location], depth-1);
	return sub->next();
}

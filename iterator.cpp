#include "iterator.h"

using namespace std;

Iterator::Iterator():
		init(0)
{
}

void Iterator::Initiate(string istr, unsigned long idepth){
	if (init)
		delete init;

	init=new Iteration(this, StringStat(istr), idepth);
}

void Iterator::CountChars(){
	for (int i=0; i<256; ++i){

	}
}

void Iterator::addRule(char f, string r){
	 rules.insert(pair<char,StringStat>(f,StringStat(r)));
}

char Iterator::next(){
	return init->next();
}

/////////////////////////////////////////////////////////////////////////////////

Iteration::Iteration(Iterator *it, StringStat x, unsigned long depthleft):
		location(0), depth(depthleft), main(it), sub(0), str(x)
{}

Iteration::~Iteration(){
	if (sub)
		delete sub;
}

unsigned long Iteration::CountChar(char x){
	if (depth==0){
		return str.chcount(x);
	}

	unsigned long c=0;
	if (main->NoRule(x)){
		c+=str.chcount(x);
	}

	Iteration* tcount;

	for (int i=0; i<256; ++i){
		tcount=new Iteration(main, main->getRule(i), depth-1);
		c+=str.chcount(i)*tcount->CountChar(i);
		delete tcount;
	}

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
		//printf("[delete sub]\n");
		delete sub;
		sub=0;
		++location;
	}

	//!sub
	if (main->NoRule(str[location])){
		return str[location++];
	}

	//!sub && rule exists
	sub=new Iteration(main, main->getRule(str[location]), depth-1);
	return sub->next();
}

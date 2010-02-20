#include "iteratator3.h"
#include <string.h>
#include <iostream>

#include <stdio.h>

using namespace std;

SIterator::SIterator(Alphabet *a){
	init=0;
	ab=a;
	direct=0;
	front();
}

SIterator::~SIterator(){
	std::map< std::pair<char, unsigned int>, SIteration*>::iterator it;
	for (it = itCache.begin(); it != itCache.end(); it++){
		delete it->second;
	}

	std::list< SIteration* >::iterator it2;
	for (it2 = itStochs.begin(); it2 != itStochs.end(); it2++){
		delete *it2;
	}
	itStochs.clear();

	if (init)
		delete init;
}

SIteration* SIterator::getIteration(char c, unsigned int d){
	std::map< std::pair<char, unsigned int>, SIteration*>::const_iterator it =
			itCache.find(std::make_pair<char, unsigned int>(c, d));

	if (it == itCache.end()){
		//cout << "cache fail, or stochastic" << endl;
		SIteration* siter = new SIteration(this, rules[c], d);
		itCache[std::make_pair<char, unsigned int>(c, d)] = siter;
		//printf("CACHEADD: %c, %u\n", c, d);
		return siter;
	}else if(it->second->isStochastic()){
		SIteration* siter = new SIteration(this, rules[c], d);
		//printf("ADDING: %X\n", (unsigned int)(siter));
		itStochs.push_back(siter);
		return siter;
	}else{
		//cout << "cache hit" << endl;
		return it->second;
	}
}

void SIterator::setIteration(StringStat x, unsigned int d){
	std::list< SIteration* >::iterator it2;
	for (it2 = itStochs.begin(); it2 != itStochs.end(); it2++){
		delete *it2;
	}
	itStochs.clear();

	if (init)
		delete init;
	initstr = x;
	CRule rule;
	rule.addRule(x, 1.0);
	init = new SIteration(this,rule,d);
}

void SIterator::setIteration(unsigned int d){
	std::list< SIteration* >::iterator it2;
	for (it2 = itStochs.begin(); it2 != itStochs.end(); it2++){
		//printf("DELETING: %X\n", (unsigned int)(*it2));
		delete *it2;
	}
	itStochs.clear();

	if (init)
		delete init;
	CRule rule;
	rule.addRule(initstr, 1.0);
	init = new SIteration(this, rule, d);
}

char SIterator::next(){
	++current;
	if (current > this->length())
		return 0;

	if (charsleft){
		--charsleft;

		return direct->operator [](current-directoffset);
	}else{
		return operator [](current-1);
	}
}

double SIterator::nextParam(){
	SIteration* backup_direct=direct;
	unsigned long backup_directoffset=directoffset;
	unsigned long backup_charsleft=charsleft;
	unsigned long backup_current=current;

	double ret=0.0;
	double emin=0.1;
	bool afterdot=false;
	char x=next();

	while ((x >= '.' && x <= '9' && x != '/') || x == '('){ //slash falls between . and 0
		if (x == '.'){
			afterdot=true;
		}else if (x == '('){
			//nothing
		}else if (afterdot){
			ret+=(x-'0')*emin;
			emin/=10.0;
		}else{
			ret*=10.0;
			ret+=(x-'0');
		}

		backup_direct=direct;
		backup_directoffset=directoffset;
		backup_charsleft=charsleft;
		backup_current=current;

		x=next();
	}

	direct=backup_direct;
	directoffset=backup_directoffset;
	charsleft=backup_charsleft;
	current=backup_current;

	return ret;
}

void SIterator::setDirect(SIteration* sit, unsigned long bufflen){
	direct=sit;
	directoffset=current;
	charsleft=bufflen-1;
}

void SIterator::addRule(char f, std::string r){
	std::map<char, CRule >::const_iterator it = rules.find(f);

	if (it == rules.end()){
		rules[f] = CRule();
	}
	rules[f].addRule(StringStat(r), 1.0);
}

//////////////////////////////////////////////////

SIteration::SIteration(SIterator* p, CRule c, unsigned long d){
	parent=p;
	StringStat s=c.getRule();
	stochastic=c.isStochastic();
	strlen=s.length();
	maskArr = new char[strlen];
	lens = new unsigned long[strlen];
	childArr = new SIteration*[strlen];

	lens[strlen-1]=strlen;
	memcpy(maskArr, s.string().c_str(), strlen);
	leaf = (d==0);

	if (!leaf){
		for (unsigned int i=0; i<strlen; ++i){
			if (i==0){
				lens[i]=0;
			}else{
				lens[i]=lens[i-1];
			}

			if (!p->NoRule(maskArr[i])){
				childArr[i] = p->getIteration(maskArr[i], d-1);
				maskArr[i] = 0;
				lens[i]+=childArr[i]->len();
				stochastic |= childArr[i]->isStochastic();
			}else{
				++(lens[i]);
			}
		}
	}

	buff=0;
	if (lens[strlen-1] <= BUFFSIZE){
		getBuff();
	}

	//enum action {IDLE, DRAW, MOVE, TURNL, TURNR, PITCHU, PITCHD, ROLLL, ROLLR, FULLTURN, PUSH, POP, POLYSTART, POLYEND};

	cpoints = 0;
	clines = 0;
	ctriangles = 0;
	int triangstack = 0;
	for (unsigned int i=0; i<strlen; ++i){
		if (maskArr[i]){
			switch(parent->alphalookup(maskArr[i])){
				case DRAW:
					++cpoints;
					++clines;
					if (triangstack) ++ctriangles;
					break;
				case MOVE:
					++cpoints;
					if (triangstack) ++ctriangles;
					break;
				case POP:
					++cpoints;
					if (triangstack) ++ctriangles;
					break;
				case POLYSTART:
					++triangstack;
					break;
				case POLYEND:
					--triangstack;
					break;
				default:
					break;
			}
		}else{
			cpoints += childArr[i]->countPoints();
			clines += childArr[i]->countLines();
			ctriangles += childArr[i]->countTriangles();
			if (triangstack) ctriangles += childArr[i]->countPoints();
		}
	}
}

char* SIteration::getBuff(){
	if (leaf)
		return maskArr;

	if (buff)
		return buff;
	buff = new char[lens[strlen-1]];

	long buffi=0;

	for (unsigned int i=0; i<strlen; ++i){
		if (maskArr[i]){
			buff[buffi]=maskArr[i];
			++buffi;
		}else{
			memcpy(&(buff[buffi]), childArr[i]->getBuff(), childArr[i]->len());
			buffi+=childArr[i]->len();
		}
	}

	return buff;
}

char SIteration::operator [](unsigned long p){
	if ((p==0) && (leaf || buff)){
		if (leaf){
			parent->setDirect(this, strlen);
		}else{
			parent->setDirect(this, lens[strlen-1]);
		}
	}

	if (leaf)
		return maskArr[p];
	if (buff)
		return buff[p];

	unsigned int imin=0;
	unsigned int imax=strlen;
	unsigned int i;
	unsigned int f=0;
	bool found=false;

	//custom search algo: O(log(n))
	while (!found){
		i=(imin+imax)/2;
		if (p == lens[i]){
			f=i+1;
			found=true;
		}else if (p > lens[i]){
			imin=i+1;
		}else if(p<lens[i]){
			imax=i;
		}
		if (imin == imax){
			f=imin;
			found=true;
		}
	}

	if (maskArr[f]==0){
		if (f==0){
			return childArr[f]->operator [](p);
		}else{
			return childArr[f]->operator [](p-lens[f-1]);
		}
	}else{
		return maskArr[f];
	}
}

void SIteration::cleanup(){
	if (buff)
		delete []buff;
}

unsigned long SIteration::len(){
	return lens[strlen-1];
}

SIteration::~SIteration(){
	cleanup();
	delete []childArr;
	delete []lens;
	delete []maskArr;
}

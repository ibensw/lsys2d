#include "iteratator3.h"
#include <string.h>

#include <stdio.h>

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

	if (init)
		delete init;
}

SIteration* SIterator::getIteration(char c, unsigned int d){
	std::map< std::pair<char, unsigned int>, SIteration*>::const_iterator it =
			itCache.find(std::make_pair<char, unsigned int>(c, d));

	if (it == itCache.end()){
		SIteration* siter = new SIteration(this, rules[c], d);
		itCache[std::make_pair<char, unsigned int>(c, d)] = siter;
		printf("CACHEADD: %c, %u\n", c, d);
		return siter;
	}else{
		return it->second;
	}
}

void SIterator::setIteration(StringStat x, unsigned int d){
	initstr = x;
	init = new SIteration(this,x,d);
}

void SIterator::setIteration(unsigned int d){
	delete init;
	init = new SIteration(this, initstr, d);
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
	double ret=0.0;
	double emin=0.1;
	bool afterdot=false;
	char x=next();
	while ((x >= '.' && x <= '9' && x != '/')){ //slash falls between . and 0
		if (x == '.'){
			afterdot=true;
		}else if (afterdot){
			ret+=(x-'0')*emin;
			emin/=10.0;
		}else{
			ret*=10.0;
			ret+=(x-'0');
		}
		x=next();
	}
	prev();
	return ret;
}

void SIterator::prev(){
	--current;
	if (charsleft){
		if (direct->len() > (charsleft+1)) //needs a check whether +1 is nessesary
			++charsleft;
		else
			charsleft=0; //no more direct buffer
	}
}

void SIterator::setDirect(SIteration* sit, unsigned long bufflen){
	direct=sit;
	directoffset=current;
	charsleft=bufflen-1;
}

//////////////////////////////////////////////////

SIteration::SIteration(SIterator* p, StringStat s, unsigned long d){
	parent=p;
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

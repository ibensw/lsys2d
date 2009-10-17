#include "iterator2.h"
#include <stdio.h>
#include <string.h>


using namespace std;

Iterator::Iterator(Alphabet* a):
		ab(a), init(0)
{
}

Iterator::~Iterator(){
	if (init)
		delete init;
}

void Iterator::setInit(string i){
	if (init)
		delete init;

	init=new Iteration(StringStat(i), this);
}

char Iterator::operator [](unsigned long i){
	return init->operator [](i);
}

unsigned long Iterator::countLines() const{
	unsigned long ret=0;
	for (unsigned char i=0; i<128; ++i){
		if (ab->lookup(i)==DRAW){
			if (this->NoRule(i)){
				ret+=init->countDumbChar(i);
			}else{
				ret+=init->countSubstChar(i);
			}
		}
	}
	return ret;
}

unsigned long Iterator::countPoints() const{
	unsigned long ret=1;
	for (unsigned char i=0; i<128; ++i){
		if (ab->lookup(i)==DRAW || ab->lookup(i)==MOVE || ab->lookup(i)==POP || ab->lookup(i)==POLYEND){
			if (this->NoRule(i)){
				ret+=init->countDumbChar(i);
			}else{
				ret+=init->countSubstChar(i);
			}
		}
	}
	return ret;
}

unsigned long Iterator::countTriangles() const{
	return countPoints()/3;
}

///////////////////////////////////

Iteration::Iteration(StringStat s, const Iterator* m):
		i(0), j(0), seek(0), main(m), str(s), depth(0), len(s.length())
{
	subs=new Iteration*[128];
	memset(subs, 0, 128*sizeof(Iteration**));
}

Iteration::~Iteration(){
	for (unsigned int i=0; i<128; ++i){
		if (subs[i]){
			delete subs[i];
		}
	}
}

void Iteration::Iterate(){
	i=0;
	seek=0;
	j=0;

	if (depth==0){
		for (unsigned int i=0; i<str.length(); ++i){
			if (!subs[(unsigned int)str[i]] && !main->NoRule((unsigned int)str[i])){
				subs[(unsigned int)str[i]]=new Iteration(main->getRule(str[i]), main);
			}
		}
	}else{
		for (unsigned int i=0; i<128; ++i){
			if (subs[i]){
				subs[i]->Iterate();
			}
		}
	}

	len=0;
	for (unsigned int i=0; i<str.length(); ++i){
		if (subs[(unsigned int)str[i]]){
			len+=subs[(unsigned int)str[i]]->length();
		}else{
			++len;
		}
	}

	++depth;
}

char Iteration::operator [](unsigned long index){
	i=index;
	//printf("I %u %u %u\n", depth, i, seek);
	if (depth==0){
		//printf("* %u %u ** %s\n", this, &i, this->str.string().c_str());
		return str[i++];
	}else{
		seek=0;

		for (j=0; j<str.length(); ++j){
			if (subs[(unsigned int)str[j]]){
				//printf("> %u %u %u (%u)\n", depth, i, seek, seek+subs[(unsigned int)str[j]]->length());
				if (i >= seek && i<seek+subs[(unsigned int)str[j]]->length())
					return subs[(unsigned int)str[j]]->operator []((i++)-seek);
				seek+=subs[(unsigned int)str[j]]->length();
			}else{
				//printf("< %u %u %u %c\n", depth, i, seek, str[j]);
				if (i==seek){
					++i;
					return str[j];
				}
				seek++;
			}
		}
		return 0;
	}
}

char Iteration::next(){
	//printf("\nC %u %u %u\n", depth, i, seek);
	if (depth==0){
		//printf("* %u %u ** %s\n", this, &i, this->str.string().c_str());
		return str[i++];
	}else{
		/*if (subs[(unsigned int)str[j]] && i >= seek){
			if (i<seek+subs[(unsigned int)str[j]]->length()){
				++i;
				return subs[(unsigned int)str[j]]->next();
			}
		}

		for (unsigned int i=0; i<128; ++i){
			if (subs[i]){
				subs[i]->front();;
			}
		}

		return operator[](i++);*/

		bool reset=false;
		for (; j<str.length(); ++j){
			if (subs[(unsigned int)str[j]]){
				//printf("> %u %u %u (%u)\n", depth, i, seek, seek+subs[(unsigned int)str[j]]->length());
				if (i >= seek && i<seek+subs[(unsigned int)str[j]]->length()){
					if (reset)
						return subs[(unsigned int)str[j]]->operator []((i++)-seek);
					++i;
					return subs[(unsigned int)str[j]]->next();
				}
				seek+=subs[(unsigned int)str[j]]->length();
			}else{
				//printf("< %u %u %u %c\n", depth, i, seek, str[j]);
				if (i==seek){
					++i;
					return str[j];
				}
				seek++;
			}
			reset=true;
		}
		return 0;
	}
}

void Iteration::front(){
	//printf("FRONT: %u\n", this);
	i=0;
	j=0;
	seek=0;

	for (unsigned int i=0; i<128; ++i){
		if (subs[i]){
			subs[i]->front();;
		}
	}
}

unsigned long Iteration::countSubstChar(char a){
	if (depth==0){
		return str.chcount(a);
	}

	unsigned long ret=0;
	for (unsigned int i=0; i<128; ++i){
		if (subs[i]){
			ret+=str.chcount(i)*subs[i]->countSubstChar(a);
		}
	}

	return ret;
}

unsigned long Iteration::countDumbChar(char a){
	unsigned long ret=str.chcount(a);

	if (depth==0){
		return ret;
	}

	for (unsigned int i=0; i<128; ++i){
		if (subs[i]){
			ret+=str.chcount(i)*subs[i]->countDumbChar(a);
		}
	}

	return ret;
}


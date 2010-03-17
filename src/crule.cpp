#include "crule.h"
#include <stdlib.h>
#include <time.h>
#include <utility>
#include "stringopt.h"

#include "alphabet.h"
#include "iteratator3.h"

using namespace std;

bool noRandInit=true;

CRule::CRule():
	total(0.0)
{
	if (noRandInit){
		noRandInit=false;
		srand(time(NULL));
	}
}

void CRule::addRule(string str, double chance){
	total+=chance;
	rules.push_back(make_pair(str, chance));
}

string CRule::getRule(){
	if (isStochastic()){
		double x=total*(double(rand())/(RAND_MAX+1.0)); //x<1
		std::list< std::pair<string, double> >::iterator it;
		double curr=0.0;
		for (it=rules.begin(); it!=rules.end(); it++){
			curr+=(*it).second;
			if (x<curr){
				return (*it).first;
			}
		}
	}else{
		return rules.front().first;
	}

	throw("Stochastic rule did not produce");
}

void CRule::optimize(Alphabet* ab, SIterator* const ite, std::vector<double>* params){
	std::list< std::pair<string, double> >::iterator it;
	for (it=rules.begin(); it!=rules.end(); it++){
		printf("From %s\n", (*it).first.c_str());
		(*it).first=cacheoptimize((*it).first, ab, ite, params);
		printf("To   %s\n", (*it).first.c_str());
	}
}

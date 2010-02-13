#include "crule.h"
#include <stdlib.h>
#include <time.h>
#include <utility>

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

void CRule::addRule(StringStat str, double chance){
	total+=chance;
	rules.push_back(make_pair(str, chance));
}

StringStat CRule::getRule(){
	if (isStochastic()){
		double x=total*(double(rand())/(RAND_MAX+1.0)); //x<1
		std::list< std::pair<StringStat, double> >::iterator it;
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
}

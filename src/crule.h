#ifndef CRULE_H
#define CRULE_H
#include "stringstat.h"
#include <list>

class CRule{ //Character rules
	public:
		CRule();
		void addRule(StringStat str, double chance=1.0);
		inline bool isStochastic(){ return rules.size()>1; }
		StringStat getRule();

	private:
		std::list< std::pair<StringStat, double> > rules;
		double total;
};

#endif // CRULE_H

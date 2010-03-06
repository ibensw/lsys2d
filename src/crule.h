#ifndef CRULE_H
#define CRULE_H
#include <string>
#include <list>

class CRule{ //Character rules
	public:
		CRule();
		void addRule(std::string str, double chance=1.0);
		inline bool isStochastic(){ return rules.size()>1; }
		std::string getRule();

	private:
		std::list< std::pair<std::string, double> > rules;
		double total;
};

#endif // CRULE_H

#ifndef ITERATOR_H
#define ITERATOR_H

#include <map>
#include "stringstat.h"

class Iteration;

class Iterator{
	public:
		Iterator();
		void SetDepth(unsigned long newdepth);
		char next();
		inline StringStat getRule(char c){return rules[c];}
		inline bool NoRule(char c) const {return rules.end()==rules.find(c);}
		void CountChars();
		void addRule(char f, string r);

	private:
		Iteration* init;
		unsigned long depth;
		unsigned long iterations;
		unsigned long counts[256];
		std::map<char, StringStat> rules;

};

class Iteration{
	public:
		Iteration(Iterator* it, char x, unsigned long depthleft);
		~Iteration();
		char next();

	private:
		unsigned long location;
		unsigned long depth;
		Iterator* main;
		Iteration* sub;
		StringStat str;
};

#endif // ITERATOR_H

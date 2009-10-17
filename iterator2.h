#ifndef ITERATOR2_H
#define ITERATOR2_H

#include "stringstat.h"
#include <string>
#include <map>
#include "alphabet.h"

class Iterator;

class Iteration{
	public:
		Iteration(StringStat stri, const Iterator* m);
		~Iteration();
		void Iterate();
		inline unsigned long length(){return len;}
		char operator[](unsigned long i);
		char next();
		void front();
		unsigned long countSubstChar(char a);
		unsigned long countDumbChar(char a);


	private:
		unsigned long i;
		unsigned long j;
		unsigned long seek;

		const Iterator* main;
		StringStat str;
		Iteration** subs;
		unsigned long depth;
		unsigned long len;
};

class Iterator{
	public:
		Iterator(Alphabet* a);
		~Iterator();
		void setInit(std::string i);
		char operator[](unsigned long i);
		inline unsigned long length(){return init?init->length():0;}
		inline StringStat getRule(char c) const {return rules[c];}
		inline bool NoRule(char c) const {return rules.end()==rules.find(c);}
		inline void addRule(char f, std::string r){rules.insert(std::pair<char,StringStat>(f,StringStat(r)));}
		inline void Iterate() {init->Iterate();}
		inline char next() {return init->next(); }
		inline void front() { init->front(); }
		unsigned long countLines() const;
		unsigned long countTriangles() const;
		unsigned long countPoints() const;


	private:
		Alphabet* ab;
		StringStat initstring;
		Iteration* init;
		mutable std::map<char, StringStat> rules;
};

#endif // ITERATOR2_H

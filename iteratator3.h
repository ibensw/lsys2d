#ifndef ITERATATOR3_H
#define ITERATATOR3_H

#include "stringstat.h"
#include <string>
#include <map>
#include "alphabet.h"

#define BUFFSIZE 1024

class SIterator;

class SIteration{
	public:
		SIteration(SIterator*, StringStat, unsigned long);
		virtual ~SIteration();
		unsigned long len();
		char operator[](unsigned long);
		void cleanup();
		char* getBuff();
		inline StringStat getString() const { return str; }
		unsigned long countLines() const { return clines; }
		unsigned long countPoints() const { return cpoints; }
		unsigned long countTriangles() const { return ctriangles; }

	private:
		unsigned long clines;
		unsigned long cpoints;
		unsigned long ctriangles;
		SIterator* parent;
		bool leaf;
		StringStat str;
		unsigned long strlen;
		char* maskArr;
		unsigned long* lens;
		SIteration** childArr;
		char* buff;
};

class SIterator{
	public:
		SIterator(Alphabet* a);
		virtual ~SIterator();
		void setIteration(StringStat, unsigned int d=1);
		void setIteration(unsigned int);
		SIteration* getIteration(char, unsigned int);
		inline bool NoRule(char c) const {return rules.end()==rules.find(c);}
		inline void addRule(char f, std::string r){rules.insert(std::pair<char,StringStat>(f,StringStat(r)));}
		inline unsigned long length() const {return init->len();}
		inline char operator[](unsigned long i) const {return init->operator [](i);}
		inline void front(){ charsleft=0; current=0; }
		char next();
		double nextParam();
		void prev();
		void setDirect(SIteration*, unsigned long);
		inline action alphalookup(char c){ return ab->lookup(c); }
		inline unsigned long countLines() const {return init->countLines();}
		inline unsigned long countPoints() const {return init->countPoints()+1;}
		inline unsigned long countTriangles() const {return init->countTriangles();}

	private:
		SIteration* direct;
		unsigned long directoffset;
		unsigned long charsleft;
		unsigned long current;

		Alphabet* ab;
		SIteration* init;
		StringStat initstr;
		mutable std::map<char, StringStat> rules;
		mutable std::map< std::pair<char, unsigned int>, SIteration*> itCache;
};

#endif // ITERATATOR3_H
#ifndef ITERATATOR3_H
#define ITERATATOR3_H

#include <string>
#include <map>
#include <list>
#include "alphabet.h"
#include "crule.h"

using std::string;

#define BUFFSIZE 1024

class SIterator;

class SIteration{
	public:
		SIteration(SIterator*, CRule, unsigned long);
		virtual ~SIteration();
		unsigned long len();
		char operator[](unsigned long);
		void cleanup();
		char* getBuff();
		inline string getString() const { return str; }
		unsigned long countLines() const { return clines; }
		unsigned long countPoints() const { return cpoints; }
		unsigned long countTriangles() const { return ctriangles; }
		inline bool isStochastic() const { return stochastic; }

	private:
		unsigned long clines;
		unsigned long cpoints;
		unsigned long ctriangles;
		SIterator* parent;
		bool leaf;
		string str;
		unsigned long strlen;
		char* maskArr;
		unsigned long* lens;
		SIteration** childArr;
		char* buff;
		bool stochastic;
};

class SIterator{
	public:
		SIterator(Alphabet* a);
		virtual ~SIterator();
		void setIteration(string, unsigned int d=1);
		void setIteration(unsigned int);
		SIteration* getIteration(char, unsigned int);
		inline bool NoRule(char c) const {return rules.end()==rules.find(c);}
		void addRule(char f, std::string r);
		inline unsigned long length() const {return init->len();}
		inline char operator[](unsigned long i) const {return init->operator [](i);}
		inline void front(){ charsleft=0; current=0; }
		char next();
		double nextParam();
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
		string initstr;
		mutable std::map<char, CRule > rules;
		mutable std::map< std::pair<char, unsigned int>, SIteration*> itCache;
		mutable std::list< SIteration* > itStochs;
};

#endif // ITERATATOR3_H

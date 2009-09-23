#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <map>
#include "alphabet.h"

using std::string;
using std::map;

class Replacer{
public:
	string r;
	Replacer(string rr, Alphabet* ab);
	long addLines;
	long addTriangles;
	long addPoints;
};

class Parser
{
	string current;
	string initiator;
	map<char, Replacer> rules;
	map<char, int> varCount;
	long lines;
	long triangles;
	long points;
	string drawchars;
	Alphabet* ab;

public:
	Parser(Alphabet*);
	void addRule(char, string);
	void iterate(int times=1);
	void init(string initData);
	string getData() const;
	inline long countLines() const{return lines;}
	inline long countTriangles() const{return triangles;}
	inline long countPoints() const {return points;}
};

#endif // PARSER_H

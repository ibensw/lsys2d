#include "parser.h"
//#include <iostream>

using namespace std;

inline unsigned int countLinesIntern(string s, Alphabet* ab){
	int ret=0;
	for (unsigned int i=0; i<s.length(); ++i){
		if (ab->lookup(s[i])==DRAW)
			++ret;
	}
	return ret;
}

inline unsigned int countPointsIntern(string s, Alphabet* ab){
	int ret=1;
	for (unsigned int i=0; i<s.length(); ++i){
		if (ab->lookup(s[i])==DRAW || ab->lookup(s[i])==MOVE || ab->lookup(s[i])==POP || ab->lookup(s[i])==POLYEND)
			++ret;
	}
	return ret;
}

inline unsigned int countTrianglesIntern(string s, Alphabet* ab){
	unsigned int ret=0;
	unsigned int polystack=0;
	for (unsigned int i=0; i<s.length(); ++i){
		switch (ab->lookup(s[i])){
			case POLYSTART:
				++polystack;
				break;
			case POLYEND:
				--polystack;
				break;
			case DRAW:
			case MOVE:
				++ret;
				break;
			default:
				break;
		}

	}
	return ret;
}

Replacer::Replacer(string rr, Alphabet* ab):
		r(rr), addLines(countLinesIntern(rr, ab)), addTriangles(countTrianglesIntern(rr, ab)), addPoints(countPointsIntern(rr, ab))
{}

Parser::Parser(Alphabet* a):
		current(""), initiator(""), lines(0), triangles(0), points(0), ab(a)
{}

void Parser::init(string initData){
	initiator=current=initData;
	lines=countLinesIntern(initData, ab);
	triangles=countTrianglesIntern(initData, ab);
	points=countPointsIntern(initData, ab);
}

void Parser::addRule(char f, string r){
	 rules.insert(pair<char,Replacer>(f,Replacer(r, ab)));
}

void Parser::iterate(int times){
	string newcurrent;
	for (; times>0; --times){
		for (unsigned int i=0; i<current.length(); ++i){
			if (rules.find(current[i]) != rules.end()){
				newcurrent.append(rules.find(current[i])->second.r);
				lines+=rules.find(current[i])->second.addLines;
				triangles+=rules.find(current[i])->second.addTriangles;
				points+=rules.find(current[i])->second.addPoints;
				if (ab->lookup(current[i])==DRAW){
					--lines;
				}
			}else{
				newcurrent+=current[i];
			}
		}
		current=newcurrent;
	}
}

string Parser::getData() const{
	return current;
}

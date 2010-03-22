#include "stringopt.h"
#include <list>
#include <stdlib.h>
#include <string.h>


using namespace std;

enum state {NOP=0, TURNS, PITCHS, ROLLS, MOVES, MOVEHALFS, DRAWS, DRAWHALFS, COLORS, LENGTHS, THICKS};

inline state type(action a){
	switch(a){
		case DRAW:
			return DRAWS;
			break;
		case DRAWHALF:
			return DRAWHALFS;
			break;
		case MOVE:
			return MOVES;
			break;
		case MOVEHALF:
			return MOVEHALFS;
			break;
		case TURNL:
		case TURNR:
		//case FULLTURN:
			return TURNS;
			break;
		case PITCHU:
		case PITCHD:
			return PITCHS;
			break;
		case ROLLL:
		case ROLLR:
			return ROLLS;
			break;
		case THICKLESS:
		case THICKMORE:
			return THICKS;
			break;
		case LENGTHLESS:
		case LENGTHMORE:
			return LENGTHS;
			break;
		case COLOR:
			return COLORS;
			break;
		default:
			return NOP;
	}
}

struct part{
	state type;
	string partial;
};

double param(string s, unsigned int &pos){
	double ret=0.0;
	double emin=0.1;
	bool afterdot=false;
	char x=s[pos];

	while ((x >= '.' && x <= '9' && x != '/') || x == '('){ //slash falls between . and 0
		if (x == '.'){
			afterdot=true;
		}else if (x == '('){
			//nothing
		}else if (afterdot){
			ret+=(x-'0')*emin;
			emin/=10.0;
		}else{
			ret*=10.0;
			ret+=(x-'0');
		}

		++pos;
		x=s[pos];
	}

	return ret;
}


string contract(string s, Alphabet* ab, action plus, action minus, char plussign, char minsign){
	int x=0;

	for (unsigned int i = 0; i < s.length(); ++i){
		if (ab->lookup(s[i]) == plus){
			++x;
		}else if (ab->lookup(s[i]) == minus){
			--x;
		}
	}

	if (x == 0){
		return "";
	}else{
		string ret;
		ret.push_back(plussign);
		ret.push_back('`');
		ret.push_back((char)x);

		if (x < 0){
			ret[0]=minsign;
			ret[2]=(unsigned char)-x;
		}

		return ret;
	}
}

string contract2(string s, Alphabet* ab, action plus, action minus, char sign, double mplus, double mminus, vector<double>* params){
	double total=1.0;

	for (unsigned int i = 0; i < s.length(); ++i){
		if (ab->lookup(s[i]) == plus){
			total*=mplus;
		}else if (ab->lookup(s[i]) == minus){
			total*=mminus;
		}
	}

	if (total == 0.0){ //Would be rarely the case
		return "";
	}else{
		string ret;
		ret.push_back(sign);
		ret.push_back('~');
		params->push_back(total);
		ret.push_back((char)(params->size()-1));
		return ret;
	}
}

string partopt(part p, Alphabet* ab, vector<double>* params){
	if (p.partial.length() < 2){ //Doing something twice is bether than reading a parameter
		return p.partial;
	}
	switch(p.type){
		case ROLLS:
			return contract(p.partial, ab, ROLLR, ROLLL, '/', '\\');
		case TURNS:
			return contract(p.partial, ab, TURNR, TURNL, '-', '+');
		case PITCHS:
			return contract(p.partial, ab, PITCHU, PITCHD, '^', '&');
		case DRAWS:
			return contract(p.partial, ab, DRAW, IDLE, 'F', '$');
		case DRAWHALFS:
			return contract(p.partial, ab, DRAWHALF, IDLE, 'Z', '$');
		case MOVES:
			return contract(p.partial, ab, MOVE, IDLE, 'f', '$');
		case MOVEHALFS:
			return contract(p.partial, ab, MOVEHALF, IDLE, 'z', '$');
		case THICKS:
			return contract2(p.partial, ab, THICKMORE, THICKLESS, '?', 1.4, 0.7, params);
		case LENGTHS:
			return contract2(p.partial, ab, LENGTHMORE, LENGTHLESS, '"', 1.1, 0.9, params);
		default:
			return p.partial;
			break;
	}
}

string cacheoptimize(string cache, Alphabet* ab, SIterator* const it, vector<double>* params){
	unsigned int i=0;
	state lasttype=NOP;
	unsigned int laststart=0;
	list<part> stringparts;
	part substr;
	cache=inlineparams(cache, params);
	while (i<cache.length()){
		if (lasttype!=type(ab->lookup(cache[i])) || (!it->NoRule(cache[i]))){
			if (i!=laststart || cache[i+1]=='~'){
				substr.type=lasttype;
				substr.partial=cache.substr(laststart, i-laststart);
				stringparts.push_back(substr);
			}
			laststart=i;
			lasttype=type(ab->lookup(cache[i]));
		}
		++i;
		if (cache[i]=='~'){
			i+=2;
			lasttype=NOP;
		}
	}
	substr.type=lasttype;
	substr.partial=cache.substr(laststart, i-laststart);
	stringparts.push_back(substr);


	string ret;
	for (list<part>::iterator it2=stringparts.begin(); it2!=stringparts.end(); it2++){
		//printf("%s\n", (*it2).partial.c_str());
		ret+=partopt(*it2, ab, params);
	}

	//return cache;
	return inlineparams(ret, params);
}

string inlineparams(string s, vector<double> *params){
	double par;
	unsigned int j;
	unsigned int inl;
	string rep;
	for (unsigned int i=0; i < s.length(); ++i){
		if (s[i] == '(' && (i>0 && s[i-1] != '`' && s[i-1] != '~')){
			j=i;
			par=param(s, i);
			params->push_back(par);
			rep="~";
			inl=params->size()-1;
			rep.push_back(inl);
			s.replace(j, i-j+1, rep);
		}
	}
	return s;
}

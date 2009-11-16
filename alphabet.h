#ifndef ALPHABET_H
#define ALPHABET_H

#include <string>

enum action {IDLE=0, DRAW, MOVE, TURNL, TURNR, PITCHU, PITCHD, ROLLL, ROLLR, FULLTURN, PUSH, POP, POLYSTART, POLYEND, PARASTART, PARAEND, THICKLESS, THICKMORE, LENGTHLESS, LENGTHMORE};

class Alphabet{
private:
	action* alphatable;

public:
	Alphabet();
	~Alphabet();
	void setAlphabet(const action a, const std::string s);
	inline action& lookup(char c){return alphatable[(unsigned int)c]; }
};

#endif // ALPHABET_H

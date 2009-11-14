#include "fileinput.h"
#define TIXML_USE_STL
#include "tinyxml/tinyxml.h"
#include "tinyxml/tinystr.h"
#include "iteratator3.h"

#include <math.h>

using namespace std;

int read_file(string filename, SIterator &p, Alphabet &a, double &angle){
	TiXmlDocument doc(filename);
	if (!doc.LoadFile()){
		return 1;
	}

	TiXmlElement* root=doc.RootElement();
	if (root->QueryDoubleAttribute("sigma", &angle) != TIXML_SUCCESS){
		angle*=M_PI/180;
		return 1;
	}

	TiXmlElement* child=root->FirstChildElement("alphabet");
	string type;
	string r;
	while (child){
		type=child->Attribute("action");
		r=child->GetText();
		if (type == "draw")
			a.setAlphabet(DRAW, r);
		else if (type == "move")
			a.setAlphabet(MOVE, r);
		else if (type == "idle")
			a.setAlphabet(IDLE, r);
		else if (type == "push")
			a.setAlphabet(PUSH, r);
		else if (type == "pop")
			a.setAlphabet(POP, r);
		else if (type == "turn left")
			a.setAlphabet(TURNL, r);
		else if (type == "pitch up")
			a.setAlphabet(PITCHU, r);
		else if (type == "pitch down")
			a.setAlphabet(PITCHD, r);
		else if (type == "roll left")
			a.setAlphabet(ROLLL, r);
		else if (type == "roll right")
			a.setAlphabet(ROLLR, r);
		else if (type == "full turn")
			a.setAlphabet(FULLTURN, r);
		child=child->NextSiblingElement("alphabet");
	}

	child=root->FirstChildElement("initiator");
	if (!child){
		return 1;
	}
	p.setIteration(StringStat(child->GetText()));


	child=root->FirstChildElement("rule");
	char s;
	while (child){
		s=child->Attribute("find")[0];
		r=child->GetText();
		p.addRule(s, r);
		child=child->NextSiblingElement("rule");
	}

	return 0;
}


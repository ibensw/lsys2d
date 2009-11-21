#include "fileinput.h"
#define TIXML_USE_STL
#include "tinyxml/tinyxml.h"
#include "tinyxml/tinystr.h"
#include "iteratator3.h"

#include <math.h>

using namespace std;

int read_file(string filename, LSystem &system){
	TiXmlDocument doc(filename);
	if (!doc.LoadFile()){
		printf("Unable to load file.\n");
		return 1;
	}

	TiXmlElement* root=doc.RootElement();
	if (root->QueryDoubleAttribute("sigma", &(system.angle)) == TIXML_SUCCESS){
		system.angle*=M_PI/180;
	}

	root->QueryDoubleAttribute("length", &(system.startlength));
	root->QueryDoubleAttribute("radius", &(system.startthick));

	TiXmlElement* child=root->FirstChildElement("alphabet");
	string type;
	string r;
	while (child){
		type=child->Attribute("action");
		r=child->GetText();
		if (type == "draw")
			system.ab->setAlphabet(DRAW, r);
		else if (type == "move")
			system.ab->setAlphabet(MOVE, r);
		else if (type == "idle")
			system.ab->setAlphabet(IDLE, r);
		else if (type == "push")
			system.ab->setAlphabet(PUSH, r);
		else if (type == "pop")
			system.ab->setAlphabet(POP, r);
		else if (type == "turn left")
			system.ab->setAlphabet(TURNL, r);
		else if (type == "pitch up")
			system.ab->setAlphabet(PITCHU, r);
		else if (type == "pitch down")
			system.ab->setAlphabet(PITCHD, r);
		else if (type == "roll left")
			system.ab->setAlphabet(ROLLL, r);
		else if (type == "roll right")
			system.ab->setAlphabet(ROLLR, r);
		else if (type == "full turn")
			system.ab->setAlphabet(FULLTURN, r);
		child=child->NextSiblingElement("alphabet");
	}

	child=root->FirstChildElement("initiator");
	if (!child){
		printf("No initiator found.\n");
		return 1;
	}
	system.it->setIteration(StringStat(child->GetText()), 0);

	child=root->FirstChildElement("rule");
	char s;
	while (child){
		s=child->Attribute("find")[0];
		r=child->GetText();
		system.it->addRule(s, r);
		child=child->NextSiblingElement("rule");
	}

	child=root->FirstChildElement("color");
	int id;
	float red;
	float green;
	float blue;
	while (child){
		red=green=blue=0.0;
		child->QueryFloatAttribute("r", &red);
		child->QueryFloatAttribute("g", &green);
		child->QueryFloatAttribute("b", &blue);
		child->QueryIntAttribute("id", &id);
		system.cm->add((unsigned int)id, Color(red, green, blue));
		child=child->NextSiblingElement("color");
	}

	system.c->init(system.it, system.angle);

	return 0;
}


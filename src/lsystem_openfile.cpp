#include "lsystem.h"

#define TIXML_USE_STL
#include "tinyxml/tinyxml.h"
#include "tinyxml/tinystr.h"

#include "stringopt.h"

#include <math.h>


void LSystem::openfile(char* filename){
	TiXmlDocument doc(filename);
	if (!doc.LoadFile()){
		throw("Unable to load file");
	}

	TiXmlElement* root=doc.RootElement();
	root->QueryDoubleAttribute("sigma", &sigma);
	params.push_back(sigma);

	root->QueryDoubleAttribute("length", &startlength);
	root->QueryDoubleAttribute("radius", &startthick);

	TiXmlElement* child=root->FirstChildElement("alphabet");
	string type;
	string r;
	while (child){
		type=child->Attribute("action");
		r=child->GetText();
		if (type == "draw")
			alphabet.setAlphabet(DRAW, r);
		else if (type == "move")
			alphabet.setAlphabet(MOVE, r);
		else if (type == "idle")
			alphabet.setAlphabet(IDLE, r);
		else if (type == "push")
			alphabet.setAlphabet(PUSH, r);
		else if (type == "pop")
			alphabet.setAlphabet(POP, r);
		else if (type == "turn left")
			alphabet.setAlphabet(TURNL, r);
		else if (type == "pitch up")
			alphabet.setAlphabet(PITCHU, r);
		else if (type == "pitch down")
			alphabet.setAlphabet(PITCHD, r);
		else if (type == "roll left")
			alphabet.setAlphabet(ROLLL, r);
		else if (type == "roll right")
			alphabet.setAlphabet(ROLLR, r);
		else if (type == "full turn")
			alphabet.setAlphabet(FULLTURN, r);
		child=child->NextSiblingElement("alphabet");
	}

	child=root->FirstChildElement("axiom");
	if (!child){
		throw("No axiom found");
	}
	iterator.setIteration(child->GetText(), 0);

	child=root->FirstChildElement("rule");
	char s;
	double c;
	while (child){
		s=child->Attribute("find")[0];
		c=1.0;
		child->Attribute("prob", &c);
		r=child->GetText();
		r=inlineparams(r, params);
		//r=cacheoptimize(string, &alphabet, &iterator, sigma);
		iterator.addRule(s, r);
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
		colors.add((unsigned int)id, Color(red, green, blue));
		child=child->NextSiblingElement("color");
	}

	iterator.optimize();
	//system.angle*=M_PI/180;
	//calculator.init(&iterator, sigma);
}


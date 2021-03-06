#include "lsystem.h"
#include "stringopt.h"

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <libxml++/libxml++.h>
#include <stdlib.h>
#include <list>
#include <vector>

using namespace xmlpp;
using Glib::ustring;
using std::list;
using std::string;

inline string Attrib(const Node* n, const char* e, string def=""){
	if (dynamic_cast<const Element*>(n)){
		return dynamic_cast<const Element*>(n)->get_attribute_value(e);
	}
	return def;
}

inline double AttribD(const Node* n, const char* e, double def=0.0){
	string ret=Attrib(n, e);
	if (ret!=""){
		return strtod(ret.c_str(), 0);
	}else{
		return def;
	}
}

inline string getText(const Node* n){
	list<Node*> ns = n->get_children("text");
	if (ns.size()){
		if (dynamic_cast<ContentNode*>(ns.front())){
			return dynamic_cast<ContentNode*>(ns.front())->get_content().raw();
		}
	}
	return "";
}

void LSystem::openfile(const char* filename){
	validgeo=false;

	if (geo)
		delete geo;

	//TiXmlDocument doc(filename);
	DomParser doc;
	//doc.set_validate();
	doc.set_substitute_entities(); //We just want the text to be resolved/unescaped automatically.
	doc.parse_file(filename);
	if (!doc){
		throw("Unable to load file");
	}

	//TiXmlElement* root=doc.RootElement();
	const Node* root = doc.get_document()->get_root_node();
	sigma = AttribD(root, "sigma", 45.0);
	params.push_back(sigma);
	startlength = AttribD(root, "length", 1.0);
	startthick = AttribD(root, "radius", 0.1);

	list<Node*> children = root->get_children("alphabet");
	list<Node*>::iterator childiter;
	string type;
	string r;
	for (childiter = children.begin(); childiter != children.end(); childiter++){
		type = Attrib(*childiter, "action");
		r = getText(*childiter);
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
		else
			printf("Invalid alphabet type: %s\n", type.c_str());
	}

	children = root->get_children("rule");

	char s;
	double c;
	for (childiter = children.begin(); childiter != children.end(); childiter++){
		s=Attrib(*childiter, "find")[0];
		c=AttribD(*childiter, "prob", 1.0);
		r=getText(*childiter);
		printf("%c (%f) -> %s\n", s, c, r.c_str());
		r=inlineparams(r, &params);
		iterator.addRule(s, r);
	}


	r=getText(root->get_children("axiom").front());
	printf("Axiom: %s\n", r.c_str());
	r=cacheoptimize(r, &alphabet, &iterator, &params);
	iterator.setIteration(r, 0);
	printf("Axiom: %s\n", r.c_str());

	children = root->get_children("color");

	int id;
	float red;
	float green;
	float blue;
	for (childiter = children.begin(); childiter != children.end(); childiter++){
		red=green=blue=0.0;
		red  =AttribD(*childiter, "r", 1.0);
		green=AttribD(*childiter, "g", 1.0);
		blue =AttribD(*childiter, "b", 1.0);
		id=int(AttribD(*childiter, "id"));
		colors.add((unsigned int)id, Color(red, green, blue));
	}

	//iterator.optimize();
        printf("Parameters inlined: %i\n", (int)params.size());
	geo=new Geometry();
}


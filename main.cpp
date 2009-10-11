#include <string>
#include <iostream>

#include "parser.h"
#include "calc.h"
//#include "mysdl.h"
#include "engine/engine.h"
#include <string>
#include <math.h>
#include <stdio.h>
#include "SDL/SDL.h"

#define TIXML_USE_STL
#include "tinyxml/tinyxml.h"
#include "tinyxml/tinystr.h"
//#include "tablegeo.h"
#include "point3d.h"
#include "alphabet.h"

#include <time.h>

#define WIDTH 1400
#define HEIGHT 800

using namespace std;

int read_file(string filename, Parser &p, Alphabet &a, double &angle){
	// cout << filename << "..." << endl;
	TiXmlDocument doc(filename);
	if (!doc.LoadFile()){
		// cout << "Error loading file: " << doc.ErrorDesc() << endl;
		return 1;
	}

	TiXmlElement* root=doc.RootElement();
	if (root->QueryDoubleAttribute("sigma", &angle) != TIXML_SUCCESS){
		angle*=M_PI/180;
		// cout << "Could not parse angle" << endl;
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
		// cout << "Could not find initiator" << endl;
		return 1;
	}
	p.init(child->GetText());


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

int main(int argc, char *argv[]){
/*	Point3D forward(0.0, 0.0, 1.0);
	Point3D right(1.0, 0.0, 0.0);
	cout << forward*left << endl;*/

	Alphabet ab;
	Parser p(&ab);
	Calc c(&ab);
	Engine gfx;
	gfx.init(WIDTH, HEIGHT);
	gfx.setViewport(0, 0, WIDTH, HEIGHT);
	double angle;
	double rotate=0.0;
	double rotatespeed=0.1;
	double pitch=0.0;
	bool drawing=true;
	unsigned int iterations=0;

	void (Engine::* lineFunc)(const Point3D&, const Point3D&)=&Engine::drawLine;

	if (argc < 2){
		cout << "No filename specified" << endl;
		return 1;
	}

	// cout << "Loading " << argv[1] << endl;
	if (read_file(argv[1], p, ab, angle)!=0){
		//cout << "Error parsing XML file" << endl;
		return 1;
	}

	SDL_Event event;
	bool running=true;
	unsigned long frame=0;
	clock_t Tstart=clock();
	clock_t Tend;

	c.init(p, angle*M_PI/180);
	c.calculate();

	while (running){
		if (drawing){
			if (frame==100){
				Tend=clock();
				printf("FPS: %f\n", 100.0*((double)CLOCKS_PER_SEC)/(Tend-Tstart));
				Tstart=Tend;
				frame=0;
			}
			++frame;


			gfx.clear();

			double factor=c.maxX-c.minX;
			double factorY=c.maxY-c.minY;

			if (factor<factorY)
				factor=factorY;
			gfx.setWindow(c.minX-1, c.minX+factor+1, c.minY-1, c.minY+factor+1, c.maxZ, c.minZ);

			gfx.rotateY(rotate);
			gfx.rotateX(pitch);
			c.draw(&gfx, lineFunc);
			gfx.draw();

			rotate=fmod(rotate+rotatespeed, 360.0);
		}

		//cout << "frame" << endl;

		Uint8 *keystate = SDL_GetKeyState(NULL);
		if (keystate[SDLK_UP])
			pitch+=0.1;
		if (keystate[SDLK_DOWN])
			pitch-=0.1;

		while (gfx.PollEvent(event)){
			if (event.type == SDL_QUIT){
				running=false;
			}else if(event.type == SDL_KEYDOWN){
				switch(event.key.keysym.sym){
					case SDLK_i:
						p.iterate(1);
						++iterations;
						//c.init(p, angle*M_PI/180);
						//c.calculate();
						break;
					case SDLK_ESCAPE:
					case SDLK_q:
						running=false;
						break;
					case SDLK_c:
						c.init(p, angle*M_PI/180);
						c.calculate();
						break;
					case SDLK_LEFT:
						rotatespeed-=0.05;
						break;
					case SDLK_RIGHT:
						rotatespeed+=0.05;
						break;
					case SDLK_UP:
						pitch+=0.5;
						break;
					case SDLK_DOWN:
						pitch-=0.5;
						break;
					case SDLK_p:
						printf("\nIterations: %i\nRotation: %f deg\n", iterations, rotate);
						break;
					case SDLK_s:
						printf("Size: %u\n", p.getData().length());
						break;
					case SDLK_d:
						drawing=!drawing;
						break;
					case SDLK_r:
						pitch=0.0;
						rotatespeed=0.0;
						rotate=0.0;
						break;
					case SDLK_l:
						if (lineFunc == &Engine::drawLine){
							lineFunc=&Engine::drawLinePlain;
						}else{
							lineFunc=&Engine::drawLine;
						}
						break;
					default:
						break;
				}
			}
		}
	}

	return 0;
}

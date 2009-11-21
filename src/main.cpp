#include "calc.h"
#include "engine/engine.h"
#include <stdio.h>
#include "SDL/SDL.h"

#include "point3d.h"
#include "alphabet.h"
#include "iteratator3.h"
#include "stringstat.h"
#include "openglshot.h"
#include "fileinput.h"
#include "lsystem.h"
#include <vector>
#include <string>
#include <map>

#include <time.h>
#include <fstream>

using namespace std;

enum COMMAND {NODEF=0, QUIT, ITERATE, CALC, POV, RENDER, ROTATE, STRING};

inline vector<string> splitstring(string line){
	size_t found = 0;
	size_t last = 0;
	vector<string> ret;
	if (!line.size()){
		return ret;
	}

	while ((found = line.find(' ', last)) != string::npos){
		ret.push_back(line.substr(last, found-last));
		last=found+1;
	}
	ret.push_back(line.substr(last, line.length()-last));

	return ret;
}

int main(int argc, char *argv[]){
	LSystem mainsystem;

	if (argc < 2){
		printf("No filename specified\n");
		return 1;
	}

	if (read_file(argv[1], mainsystem)!=0){
		printf("Error parsing XML file, exiting...\n");
		return 1;
	}

	clock_t Tstart;
	clock_t Tend;

	bool running=true;
	char input[256];

	map<string, COMMAND> cmdmap;
	cmdmap["quit"]=		cmdmap["q"]=	QUIT;
	cmdmap["iterate"]=	cmdmap["i"]=	ITERATE;
	cmdmap["calc"]=		cmdmap["c"]=	CALC;
	cmdmap["pov"]=		cmdmap["p"]=	POV;
	cmdmap["render"]=		cmdmap["r"]=	RENDER;
	cmdmap["rotate"]=		cmdmap["rt"]=	ROTATE;
	cmdmap["string"]=		cmdmap["s"]=	STRING;

	string lastinput;
	vector<string> cmd;

	int iterations=0;

	Engine* opengl=0;

	while (running){
		if (opengl){
			opengl->clear();
			mainsystem.c->draw(opengl, 0.0, mainsystem.cm);
		}

		printf("> ");
		if (scanf("%[^;\n]", input)==0) input[0]=0;
		getchar();
		if (input[0] != 0){
			lastinput=input;
			cmd=splitstring(lastinput);
		}else{
			printf("> %s\n", lastinput.c_str());
		}

		Tstart=clock();
		switch(cmdmap[cmd[0]]){
			case QUIT:
				running=false;
				break;

			case ITERATE:
				{
					int relative=1;
					if (cmd.size()>1){
						relative=atoi(cmd[1].c_str());
					}
					iterations+=relative;
					mainsystem.it->setIteration(iterations);
				}
				break;

			case CALC:
				mainsystem.c->calculate(&mainsystem);
				break;

			case POV:
				if (cmd.size()>1){
					printf("Writing to %s...\n", cmd[1].c_str());
					mainsystem.c->draw2(cmd[1].c_str(), mainsystem.cm);
				}else{
					printf("Writing to out.pov...\n");
					mainsystem.c->draw2("out.pov", mainsystem.cm);
				}

				break;

			case RENDER:
				if (!opengl){
					opengl = new Engine();
					opengl->init(800, 600);
				}

				if (cmd.size()>1){
					cmd.push_back("zbuff");
				}

				if (cmd[1]=="zbuff"){
					opengl->setLinePlain(false);
				}else if (cmd[1]=="line"){
					opengl->setLinePlain(true);
				}else if (cmd[1]=="off"){
					delete opengl;
					opengl=0;
				}

				break;

			case ROTATE:
				if (opengl){
					for (unsigned int i=0; i<360; ++i){
						opengl->clear();
						//opengl->rotateY(i);
						mainsystem.c->draw(opengl, i, mainsystem.cm);
					}
				}else{
					printf("No render active.\n");
				}
				break;

			case STRING:
				mainsystem.it->front();
				{
					for (unsigned int i=0; i<mainsystem.it->length() && i < 1024; ++i){
						printf("%c", mainsystem.it->next());
					}
				}

				break;
			default:
				printf("Command not recognized.\n");
				break;
		}
		Tend=clock();
		printf("(%f ms)\n", (1000.0*(Tend-Tstart))/(double)CLOCKS_PER_SEC);

		/*if (drawing){
			if (frame==1500){
				Tend=clock();
				printf("FPS: %f\n", 150.0*((double)CLOCKS_PER_SEC)/(Tend-Tstart));
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
						p.setIteration(++iterations);
						break;
					case SDLK_j:
						p.setIteration(--iterations);
						break;
					case SDLK_ESCAPE:
					case SDLK_q:
						running=false;
						break;
					case SDLK_c:
						c.init(&p, defaultangle*M_PI/180);
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
						printf("\nIterations: \t%i\nRotation: \t%f deg\nStringLength: \t%lu\n",
							 iterations, rotate, p.length());
						break;
					case SDLK_d:
						drawing=!drawing;
						break;
					case SDLK_s:
						{
							p.front();
							ofstream outfile("out");
							printf("size: %lu, printing to: \n", p.length());
							for (unsigned long x=0; x<p.length(); ++x){
								outfile.put(p.next());
							}
							outfile.close();
							printf("\n");
						}
						break;
					case SDLK_r:
						pitch=0.0;
						rotatespeed=0.0;
						rotate=0.0;
						break;
					case SDLK_m:
						Screenshot("out.png", 0, 0, WIDTH, HEIGHT);
						break;
					case SDLK_t:
						c.draw2();
						printf("Draw2 called and returned.\n");
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
		}*/
	}

	printf("Cleaning up...\n");

	if (opengl)
		delete opengl;
	return 0;
}

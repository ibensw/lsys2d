#include "calc.h"
#include "engine/oglengine.h"
#include "engine/povengine.h"
#include <stdio.h>

#include "point3d.h"
#include "alphabet.h"
#include "iteratator3.h"
#include "openglshot.h"
#include "fileinput.h"
#include "lsystem.h"
#include <vector>
#include <string>
#include <map>

#include <time.h>
#include <fstream>

using namespace std;

enum COMMAND {NODEF=0, QUIT, ITERATE, CALC, POV, RENDER, ROTATE, STRING, ROUNDON, ROUNDOFF};

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
	OGLEngine* opengl=0;

	if (argc < 2){
		printf("No filename specified\n");
		return 1;
	}

	mainsystem.openfile(argv[1]);

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
	cmdmap["roundon"]=	cmdmap["ron"]=	ROUNDON;
	cmdmap["roundoff"]=	cmdmap["roff"]=	ROUNDOFF;

	string lastinput;
	vector<string> cmd;

	while (running){
		if (opengl){
			opengl->clear();
			//mainsystem.c->draw(opengl, 0.0, mainsystem.cm);
			mainsystem.render(opengl);
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
					//iterations+=relative;
					//mainsystem.it->setIteration(iterations);
					mainsystem.iterate(relative);
				}
				break;

			case CALC:
				//mainsystem.c->calculate(&mainsystem);
				mainsystem.calculate();
				break;

			case POV:
				POVEngine* pov;;
				if (cmd.size()>1){
					printf("Writing to %s...\n", cmd[1].c_str());
					pov=new POVEngine(cmd[1].c_str(), mainsystem.getColors());
				}else{
					printf("Writing to out.pov...\n");
					pov=new POVEngine("out.pov", mainsystem.getColors());
				}
				mainsystem.render(pov);
				delete pov;

				break;

			case RENDER:
				if (!opengl){
					printf("Initializing OpenGL...\n");
					opengl = new OGLEngine(800, 600, "LSystem");
				}

				if (cmd.size()<2){
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
						opengl->rotateY(i);
						mainsystem.render(opengl);
					}
				}else{
					printf("No render active.\n");
				}
				break;

			/*case STRING:
				mainsystem.it->front();
				{
					for (unsigned int i=0; i<mainsystem.it->length() && i < 1024; ++i){
						printf("%c", mainsystem.it->next());
					}
				}

				break;*/

			case ROUNDON:
				opengl->setRoundCylinder(true);
				break;

			case ROUNDOFF:
				opengl->setRoundCylinder(false);
				break;

			default:
				printf("Command not recognized.\n");
				break;
		}
		Tend=clock();
		printf("(%f ms)\n", (1000.0*(Tend-Tstart))/(double)CLOCKS_PER_SEC);
	}

	printf("Cleaning up...\n");

	if (opengl)
		delete opengl;
	return 0;
}

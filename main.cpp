#include "calc.h"
#include "engine/engine.h"
#include <stdio.h>
#include "SDL/SDL.h"

#include "point3d.h"
#include "alphabet.h"
#include "iterator2.h"
#include "stringstat.h"
#include "openglshot.h"
#include "fileinput.h"

#include <time.h>

#define WIDTH 1000
#define HEIGHT 800

using namespace std;

int main(int argc, char *argv[]){
	Alphabet ab;
	Iterator p(&ab);
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
		printf("No filename specified\n");
		return 1;
	}

	if (read_file(argv[1], p, ab, angle)!=0){
		printf("Error parsing XML file\n");
		return 1;
	}

	SDL_Event event;
	bool running=true;
	unsigned long frame=0;
	clock_t Tstart=clock();
	clock_t Tend;

	c.init(&p, angle*M_PI/180);
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
						p.Iterate();
						++iterations;
						break;
					case SDLK_ESCAPE:
					case SDLK_q:
						running=false;
						break;
					case SDLK_c:
						c.init(&p, angle*M_PI/180);
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
						printf("Size: %u\n", (unsigned int)p.length());
						break;
					case SDLK_d:
						drawing=!drawing;
						break;
					case SDLK_r:
						pitch=0.0;
						rotatespeed=0.0;
						rotate=0.0;
						break;
					case SDLK_m:
						Screenshot("out.png", 0, 0, WIDTH, HEIGHT);
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

	printf("Cleaning up...\n");
	return 0;
}

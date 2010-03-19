#include "engine.h"
using namespace std;

#define ZTRANS -100.0f

Engine::Engine()
{
	plain=false;
	roundcyls=false;
}

Engine::~Engine(){}

void Engine::setPoints(Point3D* s){
	points=s;
}

void Engine::setColor(float r __attribute__ ((unused)), float g __attribute__ ((unused)), float b __attribute__ ((unused))){}

void Engine::draw(){}

void Engine::setWindow(double l __attribute__ ((unused)), double r __attribute__ ((unused)), double b __attribute__ ((unused)), double t __attribute__ ((unused)), double n __attribute__ ((unused)), double f __attribute__ ((unused))){}

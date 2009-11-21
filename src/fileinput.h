#ifndef FILEINPUT_H
#define FILEINPUT_H

#include "iteratator3.h"
#include "alphabet.h"
#include "lsystem.h"
#include <string>

int read_file(std::string filename, LSystem &system);

#endif // FILEINPUT_H

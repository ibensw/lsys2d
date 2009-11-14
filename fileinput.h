#ifndef FILEINPUT_H
#define FILEINPUT_H

#include "iteratator3.h"
#include "alphabet.h"
#include <string>

int read_file(std::string filename, SIterator &p, Alphabet &a, double &angle);

#endif // FILEINPUT_H

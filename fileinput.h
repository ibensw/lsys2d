#ifndef FILEINPUT_H
#define FILEINPUT_H

#include "iterator2.h"
#include "alphabet.h"
#include <string>

int read_file(std::string filename, Iterator &p, Alphabet &a, double &angle);

#endif // FILEINPUT_H

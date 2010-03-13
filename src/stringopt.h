//A String Optimizer
#ifndef STRINGOPT_H
#define STRINGOPT_H

#include <string>
#include "alphabet.h"
#include "iteratator3.h"
using std::string;

string cacheoptimize(string, Alphabet*, SIterator* const);
string inlineparams(string s, std::vector<double> &params);

#endif // STRINGOPT_H

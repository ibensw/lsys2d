#include "stringstat.h"
#include <stdio.h>
#include <string.h>

using namespace std;

StringStat::StringStat():
		str("")
{
	memset(charcount, 0, 128*sizeof(unsigned long));
}

StringStat::StringStat(std::string init):
		str(init)
{
	memset(charcount, 0, 128*sizeof(unsigned long));
	for (unsigned int i=0; i<str.length(); ++i){
		++charcount[(unsigned char)str[i]];
	}
}

void StringStat::Set(std::string init){
	str=init;

	memset(charcount, 0, 128*sizeof(unsigned long));
	for (unsigned int i=0; i<str.length(); ++i){
		++charcount[(unsigned char)str[i]];
	}
}


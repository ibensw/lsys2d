#ifndef STRINGSTAT_H
#define STRINGSTAT_H

#include <string>

class StringStat
{
	public:
		StringStat();
		StringStat(std::string init);
		void Set(std::string init);
		inline std::string string() const {return str;}
		inline std::string::size_type length() const {return str.length();}
		inline char operator[](unsigned long i) const {return str[i];}
		inline unsigned long chcount(unsigned char i){return charcount[i];}


	private:
		std::string str;
		unsigned long charcount[256];
};

#endif // STRINGSTAT_H

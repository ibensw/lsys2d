#ifndef COLORMAP_H
#define COLORMAP_H

#include <map>

struct Color{
	inline Color(){}
	inline Color(float rr, float gg, float bb):r(rr), g(gg), b(bb){}
	float r;
	float g;
	float b;
};

class ColorMap{
	public:
		inline ColorMap(){}
		inline void add(unsigned int i, Color c){ colors[i]=c;}
		inline Color operator[](unsigned int i) { return colors[i]; }

		std::map<unsigned int, Color> colors;
};

#endif // COLORMAP_H

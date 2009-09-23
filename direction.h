#ifndef DIRECTION_H
#define DIRECTION_H

#include <math.h>
#include "point3d.h"

#define AXIS_FORWARD axes[0]
#define AXIS_UP axes[1]
#define AXIS_LEFT axes[2]

class Direction
{
public:
	Point3D axes[3];

	inline Direction(){}
	inline Direction(Point3D& forward, Point3D& up){
		AXIS_FORWARD=forward;
		AXIS_UP=up;
		AXIS_LEFT=up*forward;
	}
	inline void TurnLeft(double a){
		AXIS_FORWARD=AXIS_LEFT*sin(a)+AXIS_FORWARD*cos(a);
		AXIS_LEFT=AXIS_UP*AXIS_FORWARD;
	}
	inline void PitchUp(double a){
		AXIS_FORWARD=AXIS_UP*sin(a)+AXIS_FORWARD*cos(a);
		AXIS_UP=AXIS_FORWARD*AXIS_LEFT;
	}
	inline void RollLeft(double a){
		AXIS_UP=AXIS_LEFT*sin(a)+AXIS_UP*cos(a);
		AXIS_LEFT=AXIS_UP*AXIS_FORWARD;
	}
	inline Point3D GetForward() const{
		return AXIS_FORWARD;
	}
	inline void Fix(){
		AXIS_FORWARD.Normalise();
		AXIS_LEFT.Normalise();
		AXIS_UP.Normalise();
	}
};

#undef AXIS_FORWARD
#undef AXIS_UP
#undef AXIS_LEFT

#endif // DIRECTION_H

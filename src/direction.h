#ifndef DIRECTION_H
#define DIRECTION_H

#include <math.h>
#include "point3d.h"
#include <stdio.h>

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
		a*=M_PI/180.0;
		AXIS_FORWARD=AXIS_LEFT*sin(a)+AXIS_FORWARD*cos(a);
		AXIS_LEFT=AXIS_UP*AXIS_FORWARD;
	}
	inline void PitchUp(double a){
		a*=M_PI/180.0;
		AXIS_FORWARD=AXIS_UP*sin(a)+AXIS_FORWARD*cos(a);
		AXIS_UP=AXIS_FORWARD*AXIS_LEFT;
	}
	inline void RollLeft(double a){
		a*=M_PI/180.0;
		AXIS_UP=AXIS_LEFT*sin(a)+AXIS_UP*cos(a);
		AXIS_LEFT=AXIS_UP*AXIS_FORWARD;
	}
	inline void RollHorizontal(){
		// Very dangerous if forward is near to up!
		AXIS_UP.c[0]=0.0;
		AXIS_UP.c[1]=0.0;
		AXIS_UP.c[2]=1.0;

		Point3D tmpLeft = AXIS_UP*AXIS_FORWARD;
		if (tmpLeft.LengthSquared() > 0.8){
			AXIS_LEFT=tmpLeft;
			AXIS_UP=AXIS_FORWARD*AXIS_LEFT;
		}else{
			AXIS_UP=AXIS_FORWARD*AXIS_LEFT;
			printf("RollHorizontall() on top facing vector, action restored.\n");
		}
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

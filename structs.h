#include <stdio.h>


struct bounds
{
	float xpos1;
	float xpos2;
	float ypos1;
	float ypos2;
};

struct object
{
	float xcoord;
	float ycoord;
	float xvec;
	float yvec;
	struct bounds out;
};

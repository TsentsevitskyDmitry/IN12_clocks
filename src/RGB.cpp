#include "RGB.h"

void RGB::setColor(int r, int g, int b)
{
	setR(r);
	setG(g);
	setB(b);
}

void RGB::setR(int r)
{
	current_red = r;
	analogWrite(RED_PIN, r);
}

void RGB::setG(int g)
{
	current_green = g;
	analogWrite(GREEN_PIN, g);
}

void RGB::setB(int b)
{
	current_blue = b;
	analogWrite(BLUE_PIN, b);
}

void RGB::trigColors(){
	// Need more time!
	// ++current_red;
	// ++current_green;
	// ++current_blue;

	// analogWrite(RED_PIN, current_red);
	// analogWrite(GREEN_PIN, current_green);
	// analogWrite(BLUE_PIN, current_blue);
}

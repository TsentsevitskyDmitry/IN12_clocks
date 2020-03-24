#include <Arduino.h>

#define RED_PIN 	8
#define GREEN_PIN 	9
#define BLUE_PIN 	10

class RGB{
private:
	int current_red;
	int current_green;
	int current_blue;

public:
	RGB() : current_red(0), current_green(0), current_blue(0){
		pinMode(RED_PIN, OUTPUT);
		pinMode(GREEN_PIN, OUTPUT);
		pinMode(BLUE_PIN, OUTPUT);
		digitalWrite(RED_PIN, LOW);   // turn the LED on (HIGH is the voltage level)
		digitalWrite(GREEN_PIN, LOW);   // turn the LED on (HIGH is the voltage level)
		digitalWrite(BLUE_PIN, LOW); 
	}

	void setColor(int r, int g, int b);
	void setR(int r);
	void setG(int g);
	void setB(int b);
	void trigColors();
};

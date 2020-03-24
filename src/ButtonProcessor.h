#include <Arduino.h>

#define BUTTON1 14
#define BUTTON2 15

class ButtonProcessor
{
private:
  int button1_pressed;
  int button2_pressed;
  
public:
  ButtonProcessor() : button1_pressed(0), button2_pressed(0)
  {
    pinMode(BUTTON1, INPUT);
      pinMode(BUTTON2, INPUT);
  }
  
  bool anyPressed();
  bool keyPressed(int& key_pressed, int key_number);
  bool key1Pressed();
  bool key2Pressed();
};

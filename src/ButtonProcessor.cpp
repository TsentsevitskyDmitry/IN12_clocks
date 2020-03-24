#include "ButtonProcessor.h"

bool ButtonProcessor::anyPressed()
{
  return key1Pressed() || key2Pressed();
}

bool ButtonProcessor::key1Pressed()
{
  return keyPressed(button1_pressed, BUTTON1);
}

bool ButtonProcessor::key2Pressed()
{
  return keyPressed(button2_pressed, BUTTON2);
}

bool ButtonProcessor::keyPressed(int& button_pressed, int button_number)
{
  if (digitalRead(button_number) == HIGH)
  {
    if(!button_pressed){
      button_pressed = true;
      return true;
    }
  }
  else 
    button_pressed = false;  
  
  return false;
}

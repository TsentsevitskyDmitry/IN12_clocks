#include <Arduino.h>

#define K155A0 0
#define K155A1 2
#define K155A2 3
#define K155A3 1

#define TLP721_HL 6
#define TLP721_HR 5
#define TLP721_ML 21
#define TLP721_MR 20
#define TLP721_BL 7 

#define BLINK_DUTY 300

const byte digits[][4] = {{0, 1, 1, 1}, {0, 0, 1, 0}, 
                          {0, 0, 1, 1}, {0, 1, 1, 0}, 
                          {0, 1, 0, 1}, {0, 0, 0, 0}, 
                          {1, 0, 0, 0}, {1, 0, 0, 1}, 
                          {0, 0, 0, 1}, {0, 1, 0, 0}};
                          
const byte positions[] = {TLP721_HL, TLP721_HR, TLP721_ML, TLP721_MR, TLP721_BL};
const byte adresses[] = {K155A3, K155A2, K155A1, K155A0};

class GRI
{
private:
  int display_hours_hi;
  int display_hours_lo;
  int display_minutes_hi;
  int display_minutes_lo;
  byte display_mask;
  
  void setK155(const byte digit[4]);
  void prepareTime(byte time[4]);
  void tick(byte time[4]);
  
public:
  GRI() : display_hours_hi(0), display_hours_lo(0), display_minutes_hi(0), display_minutes_lo(0), display_mask(0xFF)
  {
    // K155
    for(int i = 0; i < 4; ++i){
      pinMode(adresses[i], OUTPUT);
      digitalWrite(adresses[i], LOW);
    }
    // TLP721
    for(int i = 0; i < 5; ++i){
      pinMode(positions[i], OUTPUT);
      digitalWrite(positions[i], LOW);
    }
  }
  
  void setTime(int hours, int mins);
  void setDisplayMask(byte mask);
  void setDot(int state);
  void tick();
  void animate_waterfall();
};

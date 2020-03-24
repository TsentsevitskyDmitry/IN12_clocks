#include "RGB.h"
#include "GRI.h"
#include "ButtonProcessor.h"
#include "RTC.h"

#define BLINK_DUTY 300    // ms of neon blink
#define TEMP_PERIOD 20    // secs period of temp show
#define TEMP_DUTY 5       // secs show temp
#define ANIMATE_PERIOD 20  // secs

RGB rgb;
GRI gri;
RTC rtc;
ButtonProcessor buttons;

bool is_temp = 0;
int hours, minutes;
int tempHI, tempLO;
unsigned long last_update = 0, last_blink = 0, last_temp = 0, animate_timeout = 0, buttons_timeout = -3000;

void setup() {
  rgb.setColor(0, 0, 255);
  rtc.getTime(hours, minutes);
  gri.setTime(hours, minutes);
  pinMode(LED_BUILTIN, OUTPUT);
}

void timeBlink()
{
  if (last_blink + 1000 < millis())
  {
    last_blink = millis();
    gri.setDot(HIGH);
  }
  else if (last_blink + BLINK_DUTY < millis())
  {
    gri.setDot(LOW);
  }
}

void tempUpdate()
{
  if (last_temp + TEMP_PERIOD * 1000 < millis())
  {
    is_temp = 1;
    rtc.getTemp(tempHI, tempLO);
    gri.setTime(tempHI, tempLO);
  }
  if (last_temp + (TEMP_PERIOD + TEMP_DUTY) * 1000 < millis())
  {
    last_temp = millis();
    gri.setTime(hours, minutes);
    is_temp = 0;
  }
}

void timeUpdate()
{
  if (last_update + 30 * 1000 < millis()) // if half minute passed
  {    
    gri.animate_waterfall();
    last_update = millis();
    rtc.getTime(hours, minutes);
    gri.setTime(hours, minutes);
  }
}

void processButtons()
{
  if (buttons_timeout + 3000 > millis())
  {
    delay(100);
    if (buttons.key1Pressed()) {
      buttons_timeout = millis();
      minutes = rtc.incrementMinutes();
      gri.setTime(hours, minutes);
    }
    if (buttons.key2Pressed()) {
      buttons_timeout = millis();
      hours = rtc.incrementHours();
      gri.setTime(hours, minutes);
    }
  }
  else
  {
    if (buttons.key1Pressed())
      buttons_timeout = millis();
    if (buttons.key2Pressed())
      gri.animate_waterfall();
  }
}

void processAnimation()
{
  if (animate_timeout + ANIMATE_PERIOD * 1000 < millis()) 
  {
    animate_timeout = millis();
    gri.animate_waterfall();
  }
}

void loop()
{
  if (!is_temp)
    timeBlink();
  else
    gri.setDot(HIGH);

  processButtons();
  //processAnimation();
  //tempUpdate();
  timeUpdate();
  gri.tick();

  enablePower(POWER_ADC);
  int color =  analogRead(3) / 4;
  rgb.setColor(0, 0, color);
}

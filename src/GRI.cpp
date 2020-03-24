#include "GRI.h"

void GRI::setTime(int hours, int mins)
{
  display_hours_hi = hours / 10;
  display_hours_lo = hours % 10;
  display_minutes_hi = mins / 10;
  display_minutes_lo = mins % 10;
}

void GRI::setDisplayMask(byte mask)
{
	display_mask = mask;
}

void GRI::animate_waterfall()
{
  byte time[4] = {1, 1, 1, 1};
  int seq[10] = {3, 8, 9, 4, 0, 5 ,7, 2, 6, 1};
  for(int i = 0; i < 10; ++i)
  {
    for(int j = 0; j < 4; ++j)
      time[j] = seq[i];

    unsigned long start = millis();
    while(start + 70 > millis())
      tick(time);
  }
}

void GRI::setDot(int state)
{
	digitalWrite(positions[4], state);
}

void GRI::setK155(const byte digit[4])
{
	for(int i = 0; i < 4; ++i)
	{
		digitalWrite(adresses[i], digit[i]);
	}
}

void GRI::prepareTime(byte time[4])
{
	time[3] = display_hours_hi;
	time[2] = display_hours_lo;
	time[1] = display_minutes_hi;
	time[0] = display_minutes_lo;
}

void GRI::tick(byte time[4])
{
	for(int i = 0; i < 4; ++i)
	{
		digitalWrite(positions[i], HIGH * (display_mask >> i & 0x01));
		setK155(digits[time[i]]);
		delay(2);
		digitalWrite(positions[i], LOW);
		delay(1);
	}
}

void GRI::tick()
{
  byte time[4] = {};
  prepareTime(time);
  tick(time);
}

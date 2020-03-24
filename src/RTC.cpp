#include <Wire.h>
#include "RTC.h"

void RTC::syncData()
{
	Wire.beginTransmission(DS3231); // начинаем обмен с DS3231
	Wire.write(byte(0x00)); // записываем адрес регистра, с которого начинаются данные даты и времени
	Wire.endTransmission(); // завершаем передачу

	int i = 0; // индекс текущего элемента массива
	Wire.beginTransmission(DS3231); // начинаем обмен с DS3231
	Wire.requestFrom(DS3231, 7); // запрашиваем 7 байтов у DS3231
	while(Wire.available()) // пока есть данные от DS3231
	  raw_datetime[i++] = Wire.read(); // читаем 1 байт и сохраняем в массив dateTime
	
	Wire.endTransmission(); // завершаем передачу
	fillTime(); // выводим дату и время
 
	Wire.beginTransmission(DS3231); // начинаем новый обмен с DS3231
	Wire.write(byte(0x11)); // записываем адрес регистра, с которого начинается температура
	Wire.endTransmission(); // завершаем передачу

	i = 0; // обнуляем счётчик элементов массива
	Wire.beginTransmission(DS3231); // начинаем обмен с DS3231
	Wire.requestFrom(DS3231, 2); // запрашиваем 2 байта у DS3231
	while(Wire.available()) 
	  raw_temp[i++] = Wire.read();

	Wire.endTransmission();
	fillTemp(); // выводим температуру
}

void RTC::fillTime()
{
	current_mins = raw_datetime[1] / 16 * 10 + raw_datetime[1] % 16;
	current_hours = raw_datetime[2] / 16 * 10 + raw_datetime[2] % 16;
}

void RTC::fillTemp()
{
	//   float rtcTempC = ((((short)temp[0] << 8) | (short)temp[1]) >> 6) / 4.0;
	tempHI = raw_temp[0]; // целая часть
	tempLO = raw_temp[1]*0.25; // дробная часть
}

void RTC::getTime(int& hours, int& mins)
{
	syncData();
	hours = current_hours;
	mins = current_mins;
}

void RTC::getTemp(int& tempHi, int& tempLo)
{
	tempHi = tempHI;
	tempLo = tempLO;
}


int RTC::incrementMinutes()
{
	++current_mins;
	if(current_mins > 59)
		current_mins = 0;
	setTime(current_hours, current_mins);
	return current_mins;
}

int RTC::incrementHours()
{
	++current_hours;
	if(current_hours > 23)
		current_hours = 0;
	setTime(current_hours, current_mins);
	return current_hours;
}


void RTC::setTime(int hours, int mins)
{
	Wire.beginTransmission(0x68); // начинаем обмен с DS3231 с i2c адресом 0x68

	raw_datetime[1] = (mins / 10) * 16 + mins % 10;
	raw_datetime[2] = (hours / 10) * 16 + hours % 10;

	Wire.write(byte(0x00)); // записываем адрес регистра, с которого начинаются данные даты и времени
	Wire.write(raw_datetime, 7); // записываем 8 байтов массива arr
	Wire.endTransmission(); // завершение передачи
}
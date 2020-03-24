
const byte DS3231 = 0x68; // I2C адрес таймера DS3231

class RTC
{
private:
 	byte raw_datetime[7]; // 7 байтов для хранения даты и времени
 	byte raw_temp[2]; // 7 байтов для хранения даты и времени

	int current_hours;
	int current_mins;
	int tempHI;
	int tempLO;

	void syncData();
	void fillTime();
	void fillTemp();
	void setTime(int hours, int mins);

public:
	RTC() : current_hours(0), current_mins(0), tempHI(0), tempLO(0) {}

	int incrementMinutes();
	int incrementHours();

	void getTime(int& hours, int& mins);
	void getTemp(int& tempHi, int& tempLo);
};

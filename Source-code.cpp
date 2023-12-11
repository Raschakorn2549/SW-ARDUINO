#include <DS1302.h>

#include<stdio.h>

namespace
 {
const int kCePin   = 5; // Chip Enable
const int kIoPin   = 6; // Input/Output
const int kSclkPin = 7; // Serial Clock
 // Create a DS1302 object.
 DS1302 rtc(kCePin, kIoPin, kSclkPin);

String dayAsString(const Time::Day day ) {
  switch (day){
    case Time::kSunday: return"Sunday";
    case Time::kMonday: return"Monday";
    case Time::kTuesday: return"Tuesday";
    case Time::kWednesday: return"Wednesday";
    case Time::kThursday: return"Thursday";
    case Time::kFriday: return"Friday";
    case Time::kSaturday: return"Saturday";
  }
  return "(unknown day)";
}
void printTime() {
  Time t = rtc.time();

  const String day = dayAsString(t.day);

  char buf[50];
  snprintf(buf, sizeof(buf), "%s %o4d-%02d-%02d %o4d:%02d:%02d",
           day.c_str(),
           t.yr, t.mon, t.date,
           t.hr, t.min, t.sec);

  Serial.println(buf);
}

} // namespace
void setup() {
  Serial.begin(9600);
  rtc.halt(false);
  rtc.writeProtect(false);

  Time t(2023, 01, 02, 10, 03, 15, Time::kWednesday);

  rtc.time(t);
}


void use_speaker(int pin, int Hz, int hour, int minute, int play_time_m) {
  
 Time t = rtc.time();
  if ((t.hr == hour) && (t.min == minute)) {
    tone(pin, Hz);
    delay(play_time_m * 60000);
    noTone(3);
  }
}
void loop() {
  printTime();
  delay(1000);
  
  use_speaker(3, 1000, 10, 07, 30); 
  return;
}

#ifndef Eliot_wireless_h
#define Eliot_wireless_h

#include "Arduino.h"
#include <TheAirBoard.h>

class Eliot_wireless
{
public:
  Eliot_wireless(void){};
  virtual short init(void);
  virtual short send(int experimentation, int device_code, int batt, int sensor_code, short lenght, int payload[10]);
  virtual void set_interval(unsigned long period);
  virtual unsigned long get_interval(void);
protected:
  unsigned long interval;

};

#endif

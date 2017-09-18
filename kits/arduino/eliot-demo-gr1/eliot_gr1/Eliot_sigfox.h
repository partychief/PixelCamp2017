#ifndef Eliot_sigfox_h
#define Eliot_sigfox_h

#include "Arduino.h"
#include "Eliot_wireless.h"

#define MIN_PERIOD 600000

class Eliot_sigfox : public Eliot_wireless
{
public:
  Eliot_sigfox(void);
  short init(void);
  short send(int experimentation, int device_code, int batt, int sensor_code, short lenght, int payload[10]);
  void set_interval(unsigned long period);
  unsigned long get_interval(void);
};

#endif

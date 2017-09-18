#ifndef Eliot_lora_h
#define Eliot_lora_h

#include "Arduino.h"
#include "Eliot_wireless.h"

// DOES NOT ALWAYS RESPECT DUTY CYCLE, USE ONLY FOR SHORT TIME EXPERIMENTATION!
#define MIN_PERIOD 0

class Eliot_lora : public Eliot_wireless
{
public:
  Eliot_lora(void);
  short init(void);
  short send(int experimentation, int device_code, int batt, int sensor_code, short lenght, int payload[10]);
  void set_interval(unsigned long period);
  unsigned long get_interval(void);

};

#endif

#ifndef Eliot_sensor_h
#define Eliot_sensor_h

#include "Arduino.h"
#include <TheAirBoard.h>



class Eliot_sensor
{
public:
  Eliot_sensor(void){};
  virtual void init(void);
  virtual short get_data(int data[10]);
  virtual short read(void);
  virtual void set_frequency(unsigned long freq);
  virtual unsigned long get_frequency(void);
protected:
  unsigned long frequency;
  int cpt;
};

#endif

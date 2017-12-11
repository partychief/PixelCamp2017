#ifndef Eliot_light_h
#define Eliot_light_h

#include <Eliot_sensor.h>

#define MIN_FREQUENCY 100

class Eliot_light: public Eliot_sensor
{
public:
  Eliot_light(void);
  void init(void);
  short get_data(int data[10]);
  short read(void);
  void set_frequency(unsigned long freq);
  unsigned long get_frequency(void);
};

#endif

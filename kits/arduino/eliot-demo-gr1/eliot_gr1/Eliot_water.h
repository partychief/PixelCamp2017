#ifndef Eliot_water_h
#define Eliot_water_h

#include <Eliot_sensor.h>

#define MIN_FREQUENCY 1000

class Eliot_water: public Eliot_sensor
{
public:
  Eliot_water(void);
  void init(void);
  short get_data(int data[10]);
  short read(void);
  void set_frequency(unsigned long freq);
  unsigned long get_frequency(void);
};

#endif

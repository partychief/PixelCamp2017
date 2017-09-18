#ifndef Eliot_loudness_h
#define Eliot_loudness_h

#include <Eliot_sensor.h>

#define MIN_FREQUENCY 100

class Eliot_loudness: public Eliot_sensor
{
public:
  Eliot_loudness(void);
  void init(void);
  short get_data(int data[10]);
  short read(void);
  void set_frequency(unsigned long freq);
  unsigned long get_frequency(void);
};

#endif

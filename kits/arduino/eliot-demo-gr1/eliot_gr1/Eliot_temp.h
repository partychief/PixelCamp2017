#ifndef Eliot_temp_h
#define Eliot_temp_h

#include <Eliot_sensor.h>
#include <DHT.h>

#define MIN_FREQUENCY 10000

class Eliot_temp: public Eliot_sensor
{
public:
  Eliot_temp(void);
  void init(void);
  short get_data(int data[10]);
  short read(void);
  void set_frequency(unsigned long freq);
  unsigned long get_frequency(void);
};

#endif

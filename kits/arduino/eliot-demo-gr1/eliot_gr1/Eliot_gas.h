#ifndef Eliot_gas_h
#define Eliot_gas_h

#include <Eliot_sensor.h>

#define MIN_FREQUENCY 100

class Eliot_gas: public Eliot_sensor
{
public:
  Eliot_gas(void);
  void init(void);
  short get_data(int data[10]);
  short read(void);
  void set_frequency(unsigned long freq);
  unsigned long get_frequency(void);
};

#endif

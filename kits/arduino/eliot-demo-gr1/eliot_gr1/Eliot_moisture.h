#ifndef Eliot_moisture_h
#define Eliot_moisture_h

#include <Eliot_sensor.h>

#define MIN_FREQUENCY 1000

class Eliot_moisture: public Eliot_sensor
{
public:
  Eliot_moisture(void);
  void init(void);
  short get_data(int data[10]);
  short read(void);
  void set_frequency(unsigned long freq);
  unsigned long get_frequency(void);
};

#endif

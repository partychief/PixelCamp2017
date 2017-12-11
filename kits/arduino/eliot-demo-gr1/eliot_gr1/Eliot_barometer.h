#ifndef Eliot_barometer_h
#define Eliot_barometer_h

#include <Eliot_sensor.h>
#include <Barometer.h>
#include <Wire.h>

#define MIN_FREQUENCY 30000

class Eliot_barometer: public Eliot_sensor
{
public:
  Eliot_barometer(void);
  void init(void);
  short get_data(int data[10]);
  short read(void);
  void set_frequency(unsigned long freq);
  unsigned long get_frequency(void);
};

#endif

#ifndef Eliot_ultrasonic_h
#define Eliot_ultrasonic_h

#include <Eliot_sensor.h>
#include <Ultrasonic.h>

#define MIN_FREQUENCY 2000

class Eliot_ultrasonic: public Eliot_sensor
{
public:
  Eliot_ultrasonic(void);
  void init(void);
  short get_data(int data[10]);
  short read(void);
  void set_frequency(unsigned long freq);
  unsigned long get_frequency(void);
};

#endif

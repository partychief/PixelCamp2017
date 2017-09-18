#ifndef Eliot_button_h
#define Eliot_button_h

#include <Eliot_sensor.h>

#define MIN_FREQUENCY 0

class Eliot_button: public Eliot_sensor
{
public:
  Eliot_button(void);
  void init(void);
  short get_data(int data[10]);
  short read(void);
  void set_frequency(unsigned long freq);
  unsigned long get_frequency(void);
};

#endif

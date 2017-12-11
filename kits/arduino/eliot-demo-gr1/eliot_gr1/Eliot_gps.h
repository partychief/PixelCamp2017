#ifndef Eliot_gps_h
#define Eliot_gps_h

#include <Eliot_sensor.h>

#define MIN_FREQUENCY 5000

class Eliot_gps: public Eliot_sensor
{
public:
  Eliot_gps(void);
  void init(void);
  short get_data(int data[10]);
  short read(void);
  void set_frequency(unsigned long freq);
  unsigned long get_frequency(void);
private:
  void clearBufferArray(void);
};

#endif

#include "Eliot_temp.h"

DHT dht(A5, DHT22);
int _current_temp = 0;
int _min_temp = 0;
int _max_temp = 0;
unsigned long _sum_temp;
int _average_temp = 0;
int _current_hum = 0;
int _min_hum = 0;
int _max_hum = 0;
unsigned long _sum_hum;
int _average_hum = 0;

Eliot_temp::Eliot_temp() {

}

void Eliot_temp::init(void){
    frequency = MIN_FREQUENCY;
    cpt = 0;
    dht.begin();
}

short Eliot_temp::get_data(int data[10]) {
  data[0] = _current_temp;
  data[1] = _current_hum;
  data[2] = _min_temp;
  data[3] = _max_temp;
  data[4] = _average_temp;
  data[5] = _min_hum;
  data[6] = _max_hum;
  data[7] = _average_hum;
  cpt = 0;
  _sum_temp = 0;
  _sum_hum = 0;
  return 8;
}

short Eliot_temp::read(void) {
  short result = 0;
  int ct = dht.readTemperature() * 100;
  int ch = dht.readHumidity() * 100;
  // TODO: improve test to detect error in reading values
  result = ct > 0 && ch > 0 && ch < 10000;
  if (result == 1) {
    _current_temp = ct;
    _current_hum = ch;
    if (cpt == 0) {
      _min_temp = ct;
      _max_temp = ct;
      _average_temp = ct;
      _min_hum = ch;
      _max_hum = ch;
      _average_hum = ch;
    } else {
      if (ct < _min_temp)
        _min_temp = ct;
      else if (ct > _max_temp)
        _max_temp = ct;
      _sum_temp += ct;
      _average_temp = _sum_temp / cpt;
      if (ch < _min_hum)
        _min_hum = ch;
      else if (ch > _max_hum)
        _max_hum = ch;
      _sum_hum += ch;
      _average_hum = _sum_hum / cpt;
    }
    cpt++;
  }
  return result;
}

void Eliot_temp::set_frequency(unsigned long freq) {
  if (freq >= MIN_FREQUENCY) {
    frequency = freq;
  }
}

unsigned long Eliot_temp::get_frequency(void) {
  return frequency;
}

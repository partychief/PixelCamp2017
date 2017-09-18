#include <Eliot_barometer.h>

Barometer myBarometer;
int current_temp = 0;
int min_temp = 0;
int max_temp = 0;
unsigned long sum_temp;
int average_temp = 0;
int current_pressure = 0;
int min_pressure = 0;
int max_pressure = 0;
unsigned long sum_pressure;
int average_pressure = 0;

Eliot_barometer::Eliot_barometer(){

}

void Eliot_barometer::init(void){
    frequency = MIN_FREQUENCY;
    cpt = 0;
    digitalWrite(6, HIGH);
  myBarometer.init();
  digitalWrite(6, LOW);
}

short Eliot_barometer::get_data(int data[20]) {
  data[0] = current_pressure;
  data[1] = current_temp;
  data[2] = min_pressure;
  data[3] = max_pressure;
  data[4] = average_pressure;
  data[5] = min_temp;
  data[6] = max_temp;
  data[7] = average_temp;
  cpt = 0;
  sum_temp = 0;
  sum_pressure = 0;

  return 8;
}

short Eliot_barometer::read(void) {
  short result = 0;
  int ct = int(myBarometer.bmp085GetTemperature(myBarometer.bmp085ReadUT())*100.0);
  int cp = myBarometer.bmp085GetPressure(myBarometer.bmp085ReadUP())/100;
  result = cp > 0;
  if (result == 1) {
    current_temp = ct;
    current_pressure = cp;
    if (cpt == 0) {
      min_temp = ct;
      max_temp = ct;
      average_temp = ct;
      min_pressure = cp;
      max_pressure = cp;
      average_pressure = cp;
    } else {
      if (ct < min_temp)
        min_temp = ct;
      else if (ct > max_temp)
        max_temp = ct;
      sum_temp += ct;
      average_temp = sum_temp / cpt;
      if (cp < min_pressure)
        min_pressure = cp;
      else if (cp > max_pressure)
        max_pressure = cp;
      sum_pressure += cp;
      average_pressure = sum_pressure / cpt;
    }
    cpt++;
  }
  return result;
}

void Eliot_barometer::set_frequency(unsigned long freq) {
  if (freq >= MIN_FREQUENCY) {
    frequency = freq;
  }
}

unsigned long Eliot_barometer::get_frequency(void) {
  return frequency;
}

#include "Eliot_moisture.h"

int current_moist = 0;
int min_moist = 0;
int max_moist = 0;
unsigned long sum_moist = 0;
int average_moist = 0;

Eliot_moisture::Eliot_moisture() {

}

void Eliot_moisture::init(void){
    frequency = MIN_FREQUENCY;
    cpt = 0;
}

short Eliot_moisture::get_data(int data[10]) {
  data[0] = current_moist;
  data[1] = min_moist;
  data[2] = max_moist;
  data[3] = average_moist;
  cpt = 0;
  sum_moist = 0;
  return 4;
}

short Eliot_moisture::read(void) {
  short result = 1;
  int cm = analogRead(A5);
  if (result == 1) {
    current_moist = cm;
    if (cpt == 0) {
      min_moist = cm;
      max_moist = cm;
      average_moist = cm;
	  sum_moist = cm;
    } else {
      if (cm < min_moist)
        min_moist = cm;
      else if (cm > max_moist)
        max_moist = cm;
      sum_moist += cm;
      average_moist = sum_moist / (cpt+1);
    }
    cpt++;
  }
  return result;
}

void Eliot_moisture::set_frequency(unsigned long freq) {
  if (freq >= MIN_FREQUENCY) {
    frequency = freq;
  }
}

unsigned long Eliot_moisture::get_frequency(void) {
  return frequency;
}

#include "Eliot_gas.h"

int current_gas = 0;
int min_gas = 0;
int max_gas = 0;
unsigned long sum_gas = 0;
int average_gas = 0;

Eliot_gas::Eliot_gas() {
}

void Eliot_gas::init(void){
    frequency = MIN_FREQUENCY;
    cpt = 0;
}

short Eliot_gas::get_data(int data[10]) {
  data[0] = current_gas;
  data[1] = min_gas;
  data[2] = max_gas;
  data[3] = average_gas;
  cpt = 0;
  sum_gas = 0;
  return 4;
}

short Eliot_gas::read(void) {
  short result = 1;
  int cg = analogRead(A5);
  if (result == 1) {
    current_gas = cg;
    if (cpt == 0) {
      min_gas = cg;
      max_gas = cg;
      average_gas = cg;
	  sum_gas = cg;
    } else {
      if (cg < min_gas)
        min_gas = cg;
      else if (cg > max_gas)
        max_gas = cg;
      sum_gas += cg;
      average_gas = sum_gas / (cpt+1);
    }
    cpt++;
  }
  return result;
}

void Eliot_gas::set_frequency(unsigned long freq) {
  if (freq >= MIN_FREQUENCY) {
    frequency = freq;
  }
}

unsigned long Eliot_gas::get_frequency(void) {
  return frequency;
}

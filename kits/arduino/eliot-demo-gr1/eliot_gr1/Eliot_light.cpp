#include "Eliot_light.h"

int current_light = 0;
int min_light = 0;
int max_light = 0;
unsigned long sum_light = 0;
int average_light = 0;

Eliot_light::Eliot_light() {

}

void Eliot_light::init(void){
    frequency = MIN_FREQUENCY;
    cpt = 0;
}

short Eliot_light::get_data(int data[10]) {
  data[0] = current_light;
  data[1] = min_light;
  data[2] = max_light;
  data[3] = average_light;
  cpt = 0;
  sum_light = 0;
  return 4;
}

short Eliot_light::read(void) {
  short result = 1;
  int cg = analogRead(A5);
  if (result == 1) {
    current_light = cg;
    if (cpt == 0) {
      min_light = cg;
      max_light = cg;
      average_light = cg;
	  sum_light = cg;
    } else {
      if (cg < min_light)
        min_light = cg;
      else if (cg > max_light)
        max_light = cg;
      sum_light += cg;
      average_light = sum_light / (cpt+1);
    }
    cpt++;
  }
  return result;
}

void Eliot_light::set_frequency(unsigned long freq) {
  if (freq >= MIN_FREQUENCY) {
    frequency = freq;
  }
}

unsigned long Eliot_light::get_frequency(void) {
  return frequency;
}

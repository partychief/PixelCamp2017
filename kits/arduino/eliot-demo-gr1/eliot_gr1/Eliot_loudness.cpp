#include "Eliot_loudness.h"

int current_loudness = 0;
int min_loudness = 0;
int max_loudness = 0;
unsigned long sum_loudness = 0;
int average_loudness = 0;

Eliot_loudness::Eliot_loudness() {

}

void Eliot_loudness::init(void){
    frequency = MIN_FREQUENCY;
    cpt = 0;
}

short Eliot_loudness::get_data(int data[10]) {
  data[0] = current_loudness;
  data[1] = min_loudness;
  data[2] = max_loudness;
  data[3] = average_loudness;
  cpt = 0;
  sum_loudness = 0;
  return 4;
}

short Eliot_loudness::read(void) {
  short result = 1;
  analogRead(A5),
  delay(10);
  int cg = analogRead(A5);
  if (result == 1) {
    current_loudness = cg;
    if (cpt == 0) {
      min_loudness = cg;
      max_loudness = cg;
      average_loudness = cg;
	  sum_loudness = cg;
    } else {
      if (cg < min_loudness)
        min_loudness = cg;
      else if (cg > max_loudness)
        max_loudness = cg;
      sum_loudness += cg;
      average_loudness = sum_loudness / (cpt+1);
    }
    cpt++;
  }
  return result;
}

void Eliot_loudness::set_frequency(unsigned long freq) {
  if (freq >= MIN_FREQUENCY) {
    frequency = freq;
  }
}

unsigned long Eliot_loudness::get_frequency(void) {
  return frequency;
}

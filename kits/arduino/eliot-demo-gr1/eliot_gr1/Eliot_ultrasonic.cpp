#include "Eliot_ultrasonic.h"

Ultrasonic ultrasonic(A5);
int current_dist = 0;
int min_dist = 0;
int max_dist = 0;
unsigned long sum_dist = 0;
int average_dist = 0;
int cpt_move = 0;
bool presence = false;

Eliot_ultrasonic::Eliot_ultrasonic() {

}

void Eliot_ultrasonic::init(void){
    frequency = MIN_FREQUENCY;
    cpt = 0;
}

short Eliot_ultrasonic::get_data(int data[10]) {
  data[0] = current_dist;
  data[1] = cpt_move;
  data[2] = min_dist;
  data[3] = max_dist;
  data[4] = average_dist;
  cpt = 0;
  sum_dist = 0;
  cpt_move = 0;
  return 5;
}

short Eliot_ultrasonic::read(void) {
  short result = 0;
  long cd = ultrasonic.MeasureInCentimeters();
  // TODO: improve test to detect error in reading values
  result = cd > 0;
  if (result == 1) {
	bool previous = presence;
    current_dist = cd;
	presence = cd < 80;
	if (presence == true && previous == false) {
		cpt_move++;
	}
    if (cpt == 0) {
      min_dist = cd;
      max_dist = cd;
      average_dist = cd;
	  sum_dist = cd;
    } else {
      if (cd < min_dist)
        min_dist = cd;
      else if (cd > max_dist)
        max_dist = cd;
      sum_dist += cd;
      average_dist = sum_dist / (cpt+1);
    }
    cpt++;
  }
  return result;
}

void Eliot_ultrasonic::set_frequency(unsigned long freq) {
  if (freq >= MIN_FREQUENCY) {
    frequency = freq;
  }
}

unsigned long Eliot_ultrasonic::get_frequency(void) {
  return frequency;
}

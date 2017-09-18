#include <Eliot_water.h>

int state = LOW;

Eliot_water::Eliot_water(){
}

void Eliot_water::init(void){
    frequency = MIN_FREQUENCY;
    cpt = 0;
}

short Eliot_water::get_data(int data[20]) {
  data[0] = state;
  data[1] = cpt;
  cpt = 0;
  return 2;
}

short Eliot_water::read(void) {
  short result = 1;
  int previous = state;
  state = digitalRead(A5);
  if(state != previous){
	  if(state == HIGH){
		  cpt++;
	  }
  }
  return result;
}

void Eliot_water::set_frequency(unsigned long freq) {
  if (freq >= MIN_FREQUENCY) {
    frequency = freq;
  }
}

unsigned long Eliot_water::get_frequency(void) {
  return frequency;
}

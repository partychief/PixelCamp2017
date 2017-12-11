#include <Eliot_button.h>

int button_state = LOW;

Eliot_button::Eliot_button(){
}

void Eliot_button::init(void){
    frequency = MIN_FREQUENCY;
    cpt = 0;
}

short Eliot_button::get_data(int data[20]) {
  data[0] = button_state;
  data[1] = cpt;
  cpt = 0;
  return 2;
}

short Eliot_button::read(void) {
  short result = 1;
  int previous = button_state;
  button_state = digitalRead(A5);
  if(button_state != previous){
	  if(button_state == HIGH){
		  cpt++;
	  }
  }
  digitalWrite(GREEN, button_state);
  digitalWrite(RED, button_state);
  return result;
}

void Eliot_button::set_frequency(unsigned long freq) {
  if (freq >= MIN_FREQUENCY) {
    frequency = freq;
  }
}

unsigned long Eliot_button::get_frequency(void) {
  return frequency;
}

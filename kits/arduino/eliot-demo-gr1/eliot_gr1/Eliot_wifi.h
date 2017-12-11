#ifndef Eliot_wifi_h
#define Eliot_wifi_h

#include "Arduino.h"
#include "Eliot_wireless.h"

#define MIN_PERIOD 1000

class Eliot_wifi : public Eliot_wireless
{
public:
  Eliot_wifi(void);
  short init(void);
  short init(char *ssid, char *pwd);
  short init(char *ssid, char *pwd, char *ip, int port, char *method, char *route, char *payload_id);
  short send(int experimentation, int device_code, int batt, int sensor_code, short lenght, int payload[10]);
  void set_interval(unsigned long period);
  unsigned long get_interval(void);
  uint8_t connect(void);
  uint8_t disconnect(void);
  void set_params(char *ssid, char *pwd);
private:
  int8_t send_cmd(char *ATcommand, char *expected_answer1, char *expected_answer2, unsigned int timeout);
  void set_server(char *ip, int port, char *method, char *route, char *payload_id);
  uint8_t init_id();
};

#endif

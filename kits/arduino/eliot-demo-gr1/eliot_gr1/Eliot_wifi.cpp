#include <Eliot_wifi.h>

char *_ssid = "ssid";
char *_pwd = "password";
char *_ip = "192.168.130.1";
int _port = 5001;
char *_method = "GET";
char *_route = "/experimentation/devices/data/input";
char *_payload_id = "payload";

char id[18];

Eliot_wifi::Eliot_wifi() {
}

short Eliot_wifi::init(void){
    interval = MIN_PERIOD;
    digitalWrite(RF, HIGH);
    Serial.begin(9600);
    delay(1000);
    while(Serial.available()>0){
        Serial.read();
    }
    send_cmd("AT+CWMODE_CUR=1", "OK", "ERROR", 10000);
    init_id();
    short r = 0;
    while (r == 0){
        digitalWrite(BLUE, HIGH);
        r = connect();
        digitalWrite(BLUE, LOW);
        if (r==0){
            delay(1000);
        }
    }
    r = send_cmd("AT", "OK", "ERROR", 5000);
    return r;
}

short Eliot_wifi::init(char *ssid, char *pwd){
    set_params(ssid, pwd);
    init();
}

short Eliot_wifi::init(char *ssid, char *pwd, char *ip, int port, char *method, char *route, char *payload_id){
  set_params(ssid, pwd);
  set_server(ip,port,method,route,payload_id);
  init();
}

short Eliot_wifi::send(int experimentation, int device_code, int batt, int sensor_code, short length, int payload[10]) {
  if (length > 10) {
    return 0;
  } else {
      short r = 0;
      char cmd[128];
      memset(cmd, '\0', 128);
      sprintf(cmd, "AT+CIPSTART=\"TCP\",\"%s\",%i",_ip,_port);
      r = send_cmd(cmd, "OK", "ERROR", 10000);
      if (r==1){
          r = send_cmd("AT+CIPMODE=1", "OK", "ERROR", 10000);
          if (r==1){
              sprintf(cmd, "%s %s?id=%s&%s=%.4X%.4X%.4X%.4X", _method, _route, id, _payload_id, experimentation, device_code, batt, sensor_code);
              for (int i = 0; i < length; i++) {
                sprintf(cmd, "%s%.4X", cmd, payload[i]);
              }
              sprintf(cmd, "%s\r\n", cmd);
              r = send_cmd("AT+CIPSEND", ">", "ERROR", 5000);
              if (r == 1){
                  r = send_cmd(cmd, "code", ">", 10000);
                  delay(1000);
                  Serial.print("+++");
                  delay(100);
                  r = send_cmd("AT+CIPCLOSE", "OK", "ERROR", 10000);
              }
      }
    }
//    disconnect();
  return r;
 }
}

void Eliot_wifi::set_interval(unsigned long period) {
  if (period >= MIN_PERIOD) {
    interval = period;
  }
}

unsigned long Eliot_wifi::get_interval(void) {
  return interval;
}

int8_t Eliot_wifi::send_cmd(char *ATcommand, char *expected_answer1, char *expected_answer2, unsigned int timeout){

      uint8_t x = 0,  answer = 0;
      char response[512];

      memset(response, '\0', 100);    // Initialize the string

      delay(100);

      while ( Serial.available() > 0) Serial.read();// debug.print(Serial.read());   // Clean the input buffer

      unsigned long previous = millis();
      digitalWrite(GREEN, 1);
      Serial.println(ATcommand);    // Send the AT command

      x = 0;

//      delay(100);
      do {
        // if there are data in the UART input buffer, reads it and checks for the asnwer
        if (Serial.available() != 0) {
          response[x] = Serial.read();
          x++;
          // check if the desired answer 1  is in the response of the module
          if (strstr(response, expected_answer1) != NULL){
            answer = 1;
          }
          // check if the desired answer 2 is in the response of the module
          else if (strstr(response, expected_answer2) != NULL){
            answer = 2;
          }
        }
      }
      // Waits for the asnwer with time out
      while ((answer == 0) && ((millis() - previous) < timeout));
      digitalWrite(GREEN, 0);
      return answer;
}

uint8_t Eliot_wifi::init_id(){
    uint8_t x = 0,  answer = 0, id_pos = 0;
    char response[256];
    char *expected_answer1 = "OK";
    char *expected_answer2 = "ERROR";
    char *mac = "CIPAPMAC_CUR:\"";
    unsigned int timeout = 10000;
    bool reading = false;
    bool first = true;

      memset(response, '\0', 100);    // Initialize the string

    delay(100);

    while ( Serial.available() > 0) Serial.read(); // Clean the input buffer

    unsigned long previous = millis();
    digitalWrite(GREEN, 1);
    Serial.println("AT+CIPAPMAC_CUR?");    // Send the AT command

    x = 0;

    delay(100);
    // this loop waits for the answer
    do {
      // if there are data in the UART input buffer, reads it and checks for the asnwer
      if (Serial.available() != 0) {
        response[x] = Serial.read();
        if(reading == true){
            id[id_pos] = response[x];
            id_pos++;
            if(id_pos == 17){
                id[id_pos] = '\0';
                reading = false;
                first = false;
            }
        }
        x++;
        // check if the desired answer 1  is in the response of the module
        if (strstr(response, expected_answer1) != NULL){
          answer = 1;
        }
        // check if the desired answer 2 is in the response of the module
        else if (strstr(response, expected_answer2) != NULL){
          answer = 2;
        }
        else if (strstr(response, mac) != NULL && first == true){
            reading = true;
        }
      }
    }
    // Waits for the asnwer with time out
    while ((answer == 0) && ((millis() - previous) < timeout));
    digitalWrite(GREEN, 0);
    return answer;
}

void Eliot_wifi::set_params(char *ssid, char *pwd){
  _ssid = ssid;
  _pwd = pwd;
}

void Eliot_wifi::set_server(char *ip, int port, char *method, char *route, char *payload_id){
  _ip = ip;
  _method = method;
  _route = route;
  _payload_id = payload_id;
}

uint8_t Eliot_wifi::connect(void){
    uint8_t answer = 0;
    char cmd[128] = "";
    sprintf(cmd, "AT+CWJAP_CUR=\"%s\",\"%s\"",_ssid,_pwd);
    answer = send_cmd(cmd, "OK", "ERROR", 15000);
    delay(2000);
    return answer;
}

uint8_t Eliot_wifi::disconnect(void){
  return send_cmd("AT+CWQAP", "OK", "FAIL", 5000);
}

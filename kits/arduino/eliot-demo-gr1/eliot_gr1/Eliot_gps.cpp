#include <Eliot_gps.h>
#include <SoftwareSerial.h>

SoftwareSerial SoftSerial(A5, A4);
char buffer[65];                   // buffer array for data receive over serial port
int count = 0;                              // counter for buffer array
char SEP = ',';
int lat_1 =0;
int lat_2 =0;
int lng_1 =0;
int lng_2 =0;

Eliot_gps::Eliot_gps(){
}

void Eliot_gps::init(void){
    frequency = MIN_FREQUENCY;
    SoftSerial.begin(9600);
    digitalWrite(BLUE, HIGH);
    while(read()==0){
        delay(5000);
    }
    digitalWrite(BLUE, LOW);
}

short Eliot_gps::get_data(int data[20]) {
  data[0] = lat_1;
  data[1] = lat_2;
  data[2] = lng_1;
  data[3] = lng_2;
  return 4;
}

short Eliot_gps::read(void) {
  short result = 0;
  if (SoftSerial.available())                     // if date is coming from software serial port ==> data is coming from SoftSerial shield
  {
    while (SoftSerial.available())              // reading data into char array
    {
      buffer[count++] = SoftSerial.read();    // writing data into array
      if (count == 64) {
        buffer[count] = '\0';
        break;
      }
    }

    int ilt = 0;
    int ilg = 0;
    if (strstr(buffer, "$GPGGA") != NULL) {
      char lat[10] = "";
      char lng[11] = "";
      int plat = 2;
      int plng = 4;
      int pl = 0;
      int plns = 3;
      int pleo = 5;
      bool west = false;
      bool south = false;
      for (int i = 0; i < count && pl <= 5; i++) {
        char cur = buffer[i];
        if (cur == '\r' || cur == '\n' || cur == '\0') {
          break;
        } else if (cur == ',') {
          pl++;
        } else if (pl == plat) {
          if (ilt < 9) {
            lat[ilt] = cur;
            ilt++;
          } else if (ilt == 9) {
            lat[ilt] = '\0';
          }
        } else if (pl == plng) {
          if (ilg < 10) {
            lng[ilg] = cur;
            ilg++;
          } else if (ilg == 10) {
            lng[ilg] == '\0';
          }
      } else if (pl == plns) {
          if(cur!='N'){
              south = true;
          }
      } else if (pl == pleo){
          if(cur!='E'){
              west = true;
          }
      }
      }
      if (ilt == 9 && ilg == 10) {
          result = 2;
        char v1[5];
        char v2[5];
        char v3[6];
        char v4[5];
        for (int i = 0; i < 4; i++) {
          v1[i] = lat[i];
        }
        v1[4] = '\0';
        lat_1 = atoi(v1);
        if(south == true){
            lat_1 = 0 - lat_1;
        }
        for (int i = 5; i < 10; i++) {
          v2[i-5] = lat[i];
        }
        v2[4] = '\0';
        lat_2 = atoi(v2);
        for (int i = 0; i < 5; i++) {
          v3[i] = lng[i];
        }
        v3[5] = '\0';
        lng_1 = atoi(v3);
        if(west == true){
            lng_1 = 0 - lng_1;
        }
        for (int i = 6; i < 11; i++) {
          v4[i-6] = lng[i];
        }
        v4[4] = '\0';
        lng_2 = atoi(v4);
      }
    }

    clearBufferArray();                         // call clearBufferArray function to clear the stored data from the array
    count = 0;                                  // set counter of while loop to zero
  }


  return result;
}

void Eliot_gps::set_frequency(unsigned long freq) {
  if (freq >= MIN_FREQUENCY) {
    frequency = freq;
  }
}

unsigned long Eliot_gps::get_frequency(void) {
  return frequency;
}

void Eliot_gps::clearBufferArray(void) {
  memset(buffer, '\0', 65);
}

/*
  Main program used to connect a sensor to eliot using GR-1 extension
*/
#include <TheAirBoard.h>

// Supported sensors: uncomment the one you want to use
//#define TEMP 0x01         // Temperature & humidity grove sensor
#define BAROMETER 0x02    // Barometer grove sensor
//#define WATER 0x03        // Water level grove sensor
//#define GPS 0x04          // Gps grove sensor
//#define ULTRASONIC 0x05   // Ultrasonic ranger grove sensor
//#define MOISTURE 0x06     // Moisture grove sensor
//#define GAS 0x07          // Gas grove sensor
//#define MOTION 0x08
//#define GESTURE 0x09
//#define ACCELEROMETER 0x0A
//#define BUTTON 0x0B
//#define LIGHT 0x0C
//#define NUNCHUCK 0x0D
//#define POTENTIOMETER 0x0E
//#define LOUDNESS 0x0F

// Supported networks: uncomment the one you want to use
//#define LORA 0x01
// #define SIGFOX 0x02
#define WIFI 0x03

// Uncomment to activate deep sleep (NOT IMPLEMENTED YET!)
//#define DEEP_SLEEP

// Uncomment to activate debug mode
#define DEBUG

/*
 * Sensors configuration
 */
#ifdef TEMP
#include <Eliot_temp.h>
Eliot_temp sensor;
#define DATA_FREQ 10000
int sensor_code = TEMP;
#elif BAROMETER
#include <Eliot_barometer.h>
Eliot_barometer sensor;
#define DATA_FREQ 30000
int sensor_code = BAROMETER;
#elif WATER
#include <Eliot_water.h>
Eliot_water sensor;
#define DATA_FREQ 1000
int sensor_code = WATER;
#elif GPS
#include <Eliot_gps.h>
Eliot_gps sensor;
#define DATA_FREQ 10000
int sensor_code = GPS;
#elif ULTRASONIC
#include <Eliot_ultrasonic.h>
Eliot_ultrasonic sensor;
#define DATA_FREQ 2000
int sensor_code = ULTRASONIC;
#elif MOISTURE
#include <Eliot_moisture.h>
Eliot_moisture sensor;
#define DATA_FREQ 10000
int sensor_code = MOISTURE;
#elif GAS
#include <Eliot_gas.h>
Eliot_gas sensor;
#define DATA_FREQ 1000
int sensor_code = GAS;
#elif LIGHT
#include <Eliot_light.h>
Eliot_light sensor;
#define DATA_FREQ 1000
int sensor_code = LIGHT;
#elif LOUDNESS
#include <Eliot_loudness.h>
Eliot_loudness sensor;
#define DATA_FREQ 1000
int sensor_code = LOUDNESS;
#endif

/*
 * Wireless configuration
 */
#ifdef LORA
#include "Eliot_lora.h"
Eliot_lora wireless;
#define PERIOD 120000
#elif SIGFOX
#include "Eliot_sigfox.h"
Eliot_sigfox wireless;
#define PERIOD 600000
#elif WIFI
#include "Eliot_wifi.h"
Eliot_wifi wireless;
char ssid[32] = "your_ssid";
char pwd[32] = "your_password";
#define PERIOD 60000
#endif

/*
 * Uncomment to activate debug
 */
#ifdef DEBUG
#include <SoftwareSerial.h>
SoftwareSerial debug(7, 8);
#endif

// Experimentation values
#define EXPERIMENTATION 0x00
#define DEVICE_CODE 0X00

TheAirBoard board;

void setup() {
#ifdef DEBUG
  debug.begin(9600);
  debug.print(F("["));
  debug.print(millis());
  debug.println(F("] Start setup"));
#endif
  init_board();
  sensor.init();
  sensor.set_frequency(DATA_FREQ);
#ifdef WIFI
  wireless.set_params(ssid, pwd);
#endif
  wireless.init();
  wireless.set_interval(PERIOD);
  read_from_sensor();
  send_data();
#ifdef DEBUG
  debug.print(F("["));
  debug.print(millis());
  debug.println(F("] End setup"));
  debug.println();
#endif
}

void loop() {
  unsigned long start = millis();
#ifdef DEBUG
  debug.print(F("["));
  debug.print(start);
  debug.println(F("] Start loop"));
#endif

  // Reading loop
  while ((millis() - start) < wireless.get_interval()) {
    read_from_sensor();
    delay(sensor.get_frequency());
  }
  send_data();
#ifdef DEBUG
  unsigned long real = millis() - start;
  debug.print(F("["));
  debug.print(millis());
  debug.print(F("] End of loop with duration: "));
  debug.println(real);
  debug.println();
#endif
}

void read_from_sensor(){
#ifdef DEBUG
    debug.print(F("["));
    debug.print(millis());
    debug.print(F("] Reading data from sensor, result code: "));
#endif
    short result = sensor.read();
#ifdef DEBUG
    debug.println(result);
#endif
}

void send_data(){
  // Get data from sensor
#ifdef DEBUG
  debug.println();
  debug.print(F("["));
  debug.print(millis());
  debug.println(F("] Getting data from sensor..."));
#endif
  int data[10];
  short lenght = sensor.get_data(data);
  // Send data to wireless module
  float b = board.batteryChk();
  int batt = int(b * 100);
#ifdef DEBUG
  debug.print(F("["));
  debug.print(millis());
  debug.print("] Data count: ");
  debug.println(lenght);
  debug.print(F("["));
  debug.print(millis());
  debug.print("] Data: ");
  for(int i=0; i<lenght; i++){
    debug.print(data[i]);
    debug.print(" ");
  }
  debug.println();
  debug.print(F("["));
  debug.print(millis());
  debug.print("] Battery: ");
  debug.print(b);
  debug.println(F("V"));
  debug.print(F("["));
  debug.print(millis());
  debug.println("] Start sending data...");
#endif
  short result = wireless.send(EXPERIMENTATION, DEVICE_CODE, batt, sensor_code, lenght, data);
#ifdef DEBUG
  debug.print(F("["));
  debug.print(millis());
  debug.println(F("Results:"));
  debug.print(F("["));
  debug.print(millis());
  debug.print(F("] Data from sensor: "));
  for (int i = 0; i < lenght; i++) {
    debug.print(data[i]);
    debug.print(" ");
  }
  debug.println();
  debug.print(F("["));
  debug.print(millis());
  debug.print("] Result code: ");
  debug.println(result);
  debug.println();
#endif
  // Show data sending result
  if (result == 1) {
    show(GREEN, 3);
  } else if (result == 0) {
    show(RED, 3);
  } else {
    show(RED, 5);
  }
}

// Method to initialize The AirBoard
void init_board() {
  // Init The AirBoard pins
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(RF, OUTPUT);
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);

  // Blink LEDs
  digitalWrite(RED, HIGH);
  delay(500);
  digitalWrite(RED, LOW);
  delay(500);
  digitalWrite(GREEN, HIGH);
  delay(500);
  digitalWrite(GREEN, LOW);
  delay(500);
  digitalWrite(BLUE, HIGH);
  delay(500);
  digitalWrite(BLUE, LOW);
  delay(500);
}

// Method to use red, green or blue led to show an operation result
void show(short led, short time) {
  for (int i = 0; i < time; i++) {
    digitalWrite(led, HIGH);
    delay(500);
    digitalWrite(led, LOW);
    delay(500);
  }
}

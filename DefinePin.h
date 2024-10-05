// /* NEOPICEL RGB PIN 1 */

// #define RGB_PIN 2 /* PIN 2 IN RGB */
// #define NUMPIXELS 2
// #define DELAYVAL 20

// #define COLOR_TIME 1000 /* TIME FOR EACH COLOR 10 SECONDS */
// #define BREAK_TIME 1000
// #define OFF_TIME 1000

#define SERVOMIN 125
#define SERVOMAX 600
#define SERVOMID 360

int k = 0;
int i = 0;
int j = 0, vW2 = 0, vW1 = 0;
int state = 0;
long current = 0, last = 0;
long current1 = 0, last1 = 0;
unsigned long lastTimeColorChange = 0;
uint32_t last_time = 0;
float vxX, vyY, y_value, x_value;

/* I/O FOR MOTOR */

PCA9557 io1(0x18, &Wire);
PCA9557 io2(0x19, &Wire); 

/* nRF24L01 SETUP */

RF24 radio(7, 8);                /* CE PIN 7, CSN PIN 8 */
const byte address[6] = "000077"; /* ADDRESS OF THE TRANSMITTER */

/* STRUCTURE TO HOLD RECEIVER JOYSTICK DATA */

struct JoystickData {
  int vx;
  int vy;
  int VX;
  int VY;
  uint8_t counter;
} data;

unsigned long lastReceiveTime = 0;
unsigned long currentTime = 0;
const unsigned long timeout = 10; /* 1 SECOND TIMEOUT */

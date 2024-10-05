#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

/* PIN JOYSTICK */ 

  const int vxPin = A3;
  const int vyPin = A2;
  const int VXPin = A1;
  const int VYPin = A0;

/* JOYSTICK VALUES */ 

  int vx = 0;    
  int vy = 0; 
  int VX = 0; 
  int VY = 0;

  int Joystick_vx = 0; 
  int Joystick_vy = 0;
  int Joystick_VX = 0; 
  int Joystick_VY = 0;

/* nRF24L01 SETUP */ 

  RF24 radio(7, 8); /* CE PIN 7, CSN PIN 8 */ 
  const byte address[6] = "000077"; /* ADDRESS OF THE RECEIVER */ 

/* STRUCTURE TO HOLD JOYSTICK VALUES */ 

  struct JoystickData {
    int vx;
    int vy;
    int VX;
    int VY;
    uint8_t counter;
  } data;

  void setup() {
    Serial.begin(9600);
      radio.begin();
      radio.openWritingPipe(address);
      radio.setPALevel(RF24_PA_LOW);
      radio.stopListening();
  }

  void loop() {
    readJoystick();
      data.vx = Joystick_vx;
      data.vy = Joystick_vy;
      data.VX = Joystick_VX;
      data.VY = Joystick_VY;

  /* DATA TRASMITTER */
      data.counter = 128;
      if (radio.write(&data, sizeof(data))) {
        // Serial.println("DATA SEND");
      } else {
        // Serial.println("SENDING DATA FAILED"); 
      }
      Serial.print("Joystick vx: ");
      Serial.print(Joystick_vx);
      Serial.print(" | Joystick vy: ");
      Serial.print(Joystick_vy);
      Serial.print(" | Joystick VX: ");  
      Serial.print(Joystick_VX);
      Serial.print(" | Joystick VY: ");
      Serial.println(Joystick_VY);
  }

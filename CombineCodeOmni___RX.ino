#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <PCA9557.h>
// #include <Adafruit_NeoPixel.h>
#include "DefinePin.h"
#include <DriverMotor.h>
#include <Adafruit_PWMServoDriver.h>

motor myMotor;
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
/* RESET DATA WHEN DISCONNECT REMOTE CONTROL */

void resetData() {
  data.vx = 128;
  data.vy = 128;
  data.VX = 128;
  data.VY = 128;
}
void setup() {
  radio.begin();
  pwm.begin();
  pwm.setPWMFreq(60);
  myMotor.begin();
  Serial.begin(9600);
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();
  // strip.begin();
}

void loop() {

  /* DATA RECEIVER */

  if (radio.available()) {
    lastReceiveTime = millis();
    radio.read(&data, sizeof(data));

  } else {
    currentTime = millis();
    if (currentTime - lastReceiveTime > timeout) {
      resetData();
      Serial.println("DATA RESET DUE TO TIMEOUT");
    }
  }

  /* RESET DATA WHEN DISCONNECT REMOTE CONTROL */
  if (data.counter != 0) {
    if (data.vx > 138) {
      x_value = map(data.vx, 138, 255, 0, 255);
    } else if (data.vx < 118) {
      x_value = map(data.vx, 118, 0, 0, -255);
    } else if (data.vx >= 118 && data.vx < 138) x_value = 0;

    if (data.vy > 138) {
      y_value = map(data.vy, 138, 255, 0, 255);
    } else if (data.vy < 118) {
      y_value = map(data.vy, 118, 0, 0, -255);
    } else if (data.vy >= 118 && data.vy < 138) y_value = 0;

    if (data.VX > 138) {
      vxX = map(data.VX, 138, 255, 0, 255);
    } else if (data.VX < 118) {
      vxX = map(data.VX, 118, 0, 0, -255);
    } else if (data.VX >= 118 && data.VX < 138) vxX = 0;

    if (data.VY > 138) {
      vyY = map(data.VY, 138, 255, 0, 255);
    } else if (data.VY < 118) {
      vyY = map(data.VY, 118, 0, 0, -255);
    } else if (data.VY >= 118 && data.VY < 138) vyY = 0;
  }
  servo();
  setMotorSpeeds(x_value, y_value);
}
void setMotorSpeeds(float vx, float vy) {
  vW1 = vx - vy;
  vW2 = vx + vy;

  if (vW1 > 150) {
    vW1 = 150;
  }
  if (vW1 < -150) {
    vW1 = -150;
  }

  if (vW2 > 150) {
    vW2 = 150;
  }
  if (vW2 < -150) {
    vW2 = -150;
  }

  //Motor 3
  if (vW1 > 0) {
    myMotor.motor3(1, vW1);
  }
  if (vW1 < 0) {
    myMotor.motor3(0, -vW1);
  }
  if (vW1 == 0) {
    myMotor.motorStop(3);
  }

  //Motor 2
  if (vW2 > 0) {
    myMotor.motor2(1, vW2);
  }
  if (vW2 < 0) {
    myMotor.motor2(0, -vW2);
  }
  if (vW2 == 0) {
    myMotor.motorStop(2);
  }
}
void servo() {
  current = millis();
  current1 = millis();
  if (vxX > 0) {
    if (i >= 180) {
      i = 179;
    }
    if (current - last > 0) {
      i++;
      last = current;
    }
  }

   if (vyY > 0) {
    if (j >= 180) {
      j = 179;
    }
    if (current - last > 5) {
      j++;
      last = current;
    }
  }

  if (vxX < 0) {
    if (i <= 0) {
      i = 2;
    }
    if (current1 - last1 > 0) {
      i--;
      last1 = current1;
    }
  }

   if (vyY < 0) {
    if (j <= 0) {
      j = 2;
    }
    if (current1 - last1 > 5) {
      j--;
      last1 = current1;
    }
  }

  int servoPositionY2 = map(i, 0, 180, 125, 500);
  int servoPositionX2 = map(j, 0, 180, 225, 125);
  Serial.print(" | i: ");
  Serial.println(i);
  pwm.setPWM(1, 0, servoPositionY2);
  pwm.setPWM(0, 0, servoPositionX2);
  Serial.print(" | vW1: ");
  Serial.print(vW1);
  Serial.print(" | vW2: ");
  Serial.print(vW2);
}

/* READ JOYSTICK */
void readJoystick() {
  vx = analogRead(vxPin);
  vy = analogRead(vyPin);
  VX = analogRead(VXPin);
  VY = analogRead(VYPin);

  if (vx >= 0 && vx <= 462) {
    Joystick_vx = map(vx, 462, 0, 128, 0);
  } else if (vx > 562 && vx <= 1023) {
    Joystick_vx = map(vx, 562, 1023, 128, 255);
  } else {
    Joystick_vx = 128;
  }

  if (vy >= 0 && vy <= 462) {
    Joystick_vy = map(vy, 462, 0, 128, 0);
  } else if (vy > 562 && vy <= 1023) {
    Joystick_vy = map(vy, 562, 1023, 128, 255);
  } else {
    Joystick_vy = 128;
  }

  if (VX >= 0 && VX <= 462) {
    Joystick_VX = map(VX, 462, 0, 128, 0);
  } else if (VX > 562 && VX <= 1023) {  
    Joystick_VX = map(VX, 562, 1023, 128, 255);
  } else {
    Joystick_VX = 128;
  }

  if (VY >= 0 && VY <= 462) {
    Joystick_VY = map(VY, 462, 0, 128, 0);
  } else if (VY > 562 && VY <= 1023) {
    Joystick_VY = map(VY, 562, 1023, 128, 255);
  } else {
    Joystick_VY = 128;
  }
}
#include "Freenove_4WD_Car_For_Pico_W.h"
#include <IRremote.hpp>

#include "Car_Movement.h"

#define IR_Pin 3
#define ENABLE_LED_FEEDBACK true
#define DISABLE_LED_FEEDBACK false

#define BASE_DRIVE_LENGTH 1000.0


// CONFIG VARIABLES
float Motor_Power = 50; // Int between 0 & 100 to define the power of the motors
float Current_Drive_Length = BASE_DRIVE_LENGTH; // Runtime Variable to define the current length to wait on the current loop.
bool At_Home = true;


void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_Pin, DISABLE_LED_FEEDBACK);
  Servo_Setup();
  Motor_Setup();
  Buzzer_Setup();
  Current_Drive_Length = BASE_DRIVE_LENGTH;
  At_Home = true;
}

void loop() {
  if (IrReceiver.decode()) {
    if (At_Home == true) {
      Move_Car(Motor_Power * -1, Current_Drive_Length);
      At_Home = false;
    }
    else if (At_Home == false) {
      Move_Car(Motor_Power, Current_Drive_Length);
      At_Home = true;
      Current_Drive_Length += BASE_DRIVE_LENGTH;

    }
    delay(100);
    IrReceiver.resume();
  }
}





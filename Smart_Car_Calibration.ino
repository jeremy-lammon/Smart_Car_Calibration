#include "Freenove_4WD_Car_For_Pico_W.h"
#include <IRremote.hpp>

#include "Car_Movement.h"

#define IR_Pin 3
#define ENABLE_LED_FEEDBACK true
#define DISABLE_LED_FEEDBACK false



// CONFIG VARIABLES
#define BASE_DRIVE_LENGTH 500.0
#define INCREMENT_AMOUNT 250.0

int Mode = 1; // 0 = Traveling Forward/Backward; 1 = Turning Left & Right;
float Motor_Power = 50; // Int between 0 & 100 to define the power of the motors
float Current_Drive_Length; // Runtime Variable to define the current length to wait on the current loop.
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
    
    if (Mode == 0) {
      Move_Car(At_Home ? -Motor_Power : Motor_Power, Current_Drive_Length);
    }
    else {
      Turn_Car(At_Home ? -Motor_Power : Motor_Power, Current_Drive_Length);
    }

    At_Home = !At_Home;
    if (At_Home == true) {
      Current_Drive_Length += INCREMENT_AMOUNT;
    }
    
    IrReceiver.resume();
  }
}





#include "Freenove_4WD_Car_For_Pico_W.h"
#include <IRremote.hpp>

#define IR_Pin 3
#define ENABLE_LED_FEEDBACK true
#define DISABLE_LED_FEEDBACK false

#define BASE_DRIVE_LENGTH 1000.0

#define MOTOR_M1_RATIO 1.0
#define MOTOR_M2_RATIO 1.0
#define MOTOR_M3_RATIO 1.0
#define MOTOR_M4_RATIO 1.0


int Motor_Power = 50; // Int between 0 & 100 to define the power of the motors


double Current_Drive_Length = BASE_DRIVE_LENGTH; // Runtime Variable to define the current length to wait on the current loop.

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
      //Buzzer_Alert(1,2);
    }
    else if (At_Home == false) {
      Move_Car(Motor_Power, Current_Drive_Length);
      At_Home = true;
      Current_Drive_Length += BASE_DRIVE_LENGTH;
      //Buzzer_Alert(1,2);

    }
    delay(100);
    IrReceiver.resume();
  }
}

// Power is an integer between -100 and 100, with Drive_Length being in milliseconds. 
//Will move the car in that power amount, for that time, while also taking into account for motor steering correction ratios.
void Move_Car(int Power, int Drive_Length) {
  double Acceleration_Length = Drive_Length/ 2.0;
  double Cycle_Delay = Acceleration_Length / 10.0;
  for (int i = 0; i < 10; i++) {
    double Current_Power = ((Power / 20.0) * i) + (Power / 2.0);
    Serial.println(String(i * 10.0) + "% ACCELERATION. CURRENT POWER: " + String(Current_Power));
    Motor_M_Move(Current_Power * MOTOR_M1_RATIO, Current_Power * MOTOR_M2_RATIO, Current_Power * MOTOR_M3_RATIO, Current_Power * MOTOR_M4_RATIO);
    Serial.println("CYCLE DELAY: " + String(Cycle_Delay));
    delay(Cycle_Delay);
  }

  double Main_Move_Length = 1000.0;//Drive_Length - (Acceleration_Length * 2.0);
  Serial.println("ACCELERATION COMPLETED. MOVING AT " + String(Power) + " FOR " + String(Main_Move_Length) + " MILLISECONDS.");
  Motor_M_Move(Power * MOTOR_M1_RATIO, Power * MOTOR_M2_RATIO, Power * MOTOR_M3_RATIO, Power * MOTOR_M4_RATIO);
  delay(Main_Move_Length);

  for (int i = 0; i < 10; i++) {
    double Current_Power = Power - ((Power / 20.0) * i);
    Serial.println(String(i * 10.0) + "% ACCELERATION. CURRENT POWER: " + String(Current_Power));
    Motor_M_Move(Current_Power * MOTOR_M1_RATIO, Current_Power * MOTOR_M2_RATIO, Current_Power * MOTOR_M3_RATIO, Current_Power * MOTOR_M4_RATIO);
    Serial.println("CYCLE DELAY: " + String(Cycle_Delay));
    delay(Cycle_Delay);
  }
  Serial.println("DEACCELERATION COMPLETED. SETTING POWER TO 0 AND RETURNING.");
  Motor_M_Move(0,0,0,0);
  return;
}

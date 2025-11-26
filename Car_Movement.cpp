#include <Arduino.h>
#include "Freenove_4WD_Car_For_Pico_W.h"
#include "Car_Movement.h"



void Drive_Car(float M1_Power, float M2_Power, float M3_Power, float M4_Power) {
  Motor_M_Move(M1_Power * MOTOR_M1_RATIO, M2_Power * MOTOR_M2_RATIO, M3_Power * MOTOR_M3_RATIO, M4_Power * MOTOR_M4_RATIO);
  return;
}

void Drive_Car_Straight(float Power) {
  Drive_Car(Power, Power, Power, Power);
  return;
}

void Accelerate_Car(float Current_Power, float Desired_Power, float Duration) {
  
  const float Step_Delay = Duration / 10.0;
  const float Step_Power_Change = ((Desired_Power - Current_Power) / 10.0);
  float Step_Power = Current_Power;

  Serial.println("STARTING (DE)ACCELERATION FROM POWER " + String(Current_Power) + " TO POWER " + String(Desired_Power) + " OVER " + String(Duration) + " MILLISECONDS WITH " + String(Step_Power_Change) + " POWER INCREMENTS.");
  for (int i = 0; i < 10; i++) {
    Step_Power += Step_Power_Change;
    Drive_Car_Straight(Step_Power);
    delay(Step_Delay);
  }

  Serial.println("(DE)ACCELERATION COMPLETED.");
  return;
}





// Power is an integer between -100 and 100, with Drive_Length being in milliseconds. 
//Will move the car in that power amount, for that time, while also taking into account for motor steering correction ratios.
void Move_Car(float Power, float Drive_Length) {
  Serial.println("MOVING CAR AT POWER " + String(Power) + " FOR " + String(Drive_Length) + " MILLISECONDS.");
  //Accelerate_Car(Power / 2.0, Power, ACCELERATION_TIME);

  float Drive_Time = Drive_Length; //- (ACCELERATION_TIME * 2.0);
  Serial.println("MOVING AT " + String(Power) + " FOR " + String(Drive_Time) + " MILLISECONDS.");
  Drive_Car_Straight(Power);
  delay(Drive_Time);

  //Accelerate_Car(Power, 0, ACCELERATION_TIME);
  Drive_Car(0,0,0,0);
  return;
}

//Same as Move_Car_Straight, but solely for turning in the left direction at a certain power for certain length.
//Use Positive Powers for turning Left, and Negative Powers for Turning Right
void Turn_Car(float Power, float Duration) {
  Serial.println("TURNING CAR LEFT AT POWER " + String(Power) + " FOR " + String(Duration) + " MILLISECONDS.");
  Drive_Car(-Power, -Power, Power, Power);
  delay(Duration);
  Drive_Car(0,0,0,0);
  Serial.println("COMPLETED TURNING CAR. RETURNING.");
  return;
}
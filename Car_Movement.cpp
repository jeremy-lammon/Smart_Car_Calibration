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
  Serial.println("STARTING ACCELERATION FROM POWER " + String(Current_Power) + " TO POWER " + String(Desired_Power) + " OVER " + String(Duration) + " SECONDS.");
  const float Step_Delay = Duration / 10.0;
  const float Step_Power_Change = ((Desired_Power - Current_Power) / 10.0);
  float Step_Power = Current_Power;
  for (int i = 0; i < 10; i++) {
    Step_Power += Step_Power_Change;
    Serial.println(String(i * 10.0) + "% ACCELERATION PROGRESS. CURRENT POWER: " + String(Step_Power) + " STEP DELAY: " + String(Step_Delay));
    Drive_Car_Straight(Step_Power);
    delay(Step_Delay);
  }
  Serial.println("ACCELERATION COMPLETED.");
  return;
}
  /*for (int i = 0; i < 10; i++) {
    float Current_Power = ((Power / 20.0) * i) + (Power / 2.0);
    Serial.println(String(i * 10.0) + "% ACCELERATION. CURRENT POWER: " + String(Current_Power));
    Drive_Car(Current_Power, Current_Power, Current_Power, Current_Power);
    Serial.println("CYCLE DELAY: " + String(Cycle_Delay));
    delay(Cycle_Delay);
  }*/

// Power is an integer between -100 and 100, with Drive_Length being in milliseconds. 
//Will move the car in that power amount, for that time, while also taking into account for motor steering correction ratios.
void Move_Car(float Power, float Drive_Length) {
  Serial.println("MOVING CAR AT POWER " + String(Power) + " FOR " + String(Drive_Length) + " MILLISECONDS.");
  float Acceleration_Length = Drive_Length/ 2.0;
  float Cycle_Delay = Acceleration_Length / 10.0;

  Accelerate_Car(25, Power, Acceleration_Length);

  
  /*float Main_Move_Length = 1000.0;//Drive_Length - (Acceleration_Length * 2.0);
  Serial.println("ACCELERATION COMPLETED. MOVING AT " + String(Power) + " FOR " + String(Main_Move_Length) + " MILLISECONDS.");
  Drive_Car(Power, Power, Power, Power);
  delay(Main_Move_Length);*/

  Accelerate_Car(Power, 25, Acceleration_Length);
  Serial.println("DEACCELERATION COMPLETED. SETTING POWER TO 0 AND RETURNING.");
  Drive_Car(0,0,0,0);
  return;
}
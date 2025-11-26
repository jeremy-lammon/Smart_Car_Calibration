#ifndef _CAR_MOVEMENT_H
#define _CAR_MOVEMENT_H

#define MOTOR_M1_RATIO 1.0
#define MOTOR_M2_RATIO 1.0
#define MOTOR_M3_RATIO 1.0
#define MOTOR_M4_RATIO 1.0

#define ACCELERATION_TIME 250.0


void Drive_Car(float M1_Power, float M2_Power, float M3_Power, float M4_Power); // Equivelant to Motor_M_Move in original code, but takes into account motor power ratios.
void Accelerate_Car(float Current_Power, float Desired_Power, float Duration); // Tweens the car's power on all 4 motors from their current power provided to the desired power provided within the length in milliseconds.


void Move_Car(float Power, float Drive_Length); // Drives the car forward for the provided power and drive length in milliseconds.
void Turn_Car(float Power, float Duration);




#endif

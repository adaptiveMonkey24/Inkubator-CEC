#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

float Kp = 1.5;
float Ki = 0.05;
float Kd = 0.1;

float error;
float previousError;
float integral;
float derivative;

float calculatePID(float setpoint, float input)
{
    error = setpoint - input;

    integral += error;
    derivative = error - previousError;

    float output = (Kp * error) +
                   (Ki * integral) +
                   (Kd * derivative);

    previousError = error;

    return output;
}

void setPID(float kp, float ki, float kd)
{
    Kp = kp;
    Ki = ki;
    Kd = kd;
}

void resetPID()
{
    error = 0;
    previousError = 0;
    integral = 0;
    derivative = 0;
}

#endif

#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <string.h>

#define SWITCH_LIGHT_GPIO 28
#define IR_SENSOR_GPIO 7
#define DIST_SENSOR_TRIG 4
#define DIST_SNESOR_ECHO 5

int setupGpio()
{
    
    
    
}

int lightControl(int cmd)
{
    wiringPiSetupGpio();
    int lightStatus = digitalRead(SWITCH_LIGHT_GPIO);

    int cmdStatus = 99;
    int cmdStart = 1;
    int cmdStop = 0;

    if (cmd == cmdStatus)
    {
        return lightStatus;
    }
    else if (cmd == cmdStart || cmd == cmdStop)
    {
        if (lightStatus == 1)
        {
            digitalWrite(SWITCH_LIGHT_GPIO, 0);
            return 0;
        }
        else if (lightStatus == 0)
        {
            digitalWrite(SWITCH_LIGHT_GPIO, 1);
            return 1;
        }
        else
        {
            printf("Erreur Light Control");
            return -1;
        }
    }
    
}

int IRSensor()
{
    wiringPiSetupGpio();
    int IRStatus = digitalRead(IR_SENSOR_GPIO);
    return IRStatus;
}

int DISTSensor()
{
    wiringPiSetup();
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);

    //TRIG pin must start LOW
    digitalWrite(TRIG, LOW);
    delay(30);

    digitalWrite(TRIG, HIGH);
    delayMicroseconds(20);
    digitalWrite(TRIG, LOW);

    //Wait for echo start
    while(digitalRead(ECHO) == LOW);

    //Wait for echo end
    long startTime = micros();
    while(digitalRead(ECHO) == HIGH);
    long travelTime = micros() - startTime;

    //Get distance in cm
    int distance = travelTime / 58;

    return distance;   
}

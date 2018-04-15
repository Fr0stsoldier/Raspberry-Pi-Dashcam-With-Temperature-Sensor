#include <Servo.h>
Servo myservo;//initialize servo object
const int sensor = A0;//variable to record temperature
int x;//variable for breaking out of loop
int pos = 0;//variable for positioning servo
char command;//variable for servo direction
char variable = '0';//variable for switch statements
void setup()
{
  Serial.begin(9600);//initialize baud rate
  myservo.attach(9);//is pin servo is attached too
}

void loop()
{
  if (Serial.available() > 0)//if records input
    variable = Serial.read();
  int sensorVal = analogRead(sensor);//reads from analog sensor
  float voltageVal = (sensorVal / 1024.0) * 5.0;//next three commands converts from voltage to number
  float temp = (voltageVal - .5) * 100;
  float tempf = ((temp * (9 / 5)) + 32);
  switch (variable)//contains different scenarios
  {
    case '0': //This will start the sweep along while printing temperature
      for (pos = 0; pos <= 180; pos += 1)//standard sweep
      {
        myservo.write(pos);
        delay(15);
      }
      sensorVal = analogRead(sensor);
      voltageVal = (sensorVal / 1024.0) * 5.0;
      temp = (voltageVal - .5) * 100;
      tempf = ((temp * (9 / 5)) + 32);
      Serial.print(tempf);
      Serial.println("  ");
      for (pos = 180; pos >= 0; pos -= 1)
      {
        myservo.write(pos);
        delay(20);
      }
      sensorVal = analogRead(sensor);
      voltageVal = (sensorVal / 1024.0) * 5.0;
      temp = (voltageVal - .5) * 100;
      tempf = ((temp * (9 / 5)) + 32);
      Serial.print(tempf);
      Serial.println("  ");
      break;
    case '8'://send message to RPi to poweroff
      variable = '0';
      for (pos = 0; pos <= 180; pos += 1)
      {
        myservo.write(pos);
        delay(20);
      }
      Serial.print(tempf);
      Serial.println(" stop");
      for (pos = 180; pos >= 0; pos -= 1)
      {
        myservo.write(pos);
        delay(15);
      }
      Serial.print(tempf);
      Serial.println(" stop");
      delay(2000);
      break;
    case '9'://This will let you manually move the servo
      {
        int cool = 9;
        while (cool = 9)
        {
          if (Serial.available())
          {
            command = (Serial.read());
            {
              if (command == '1')//turn to 180
              {
                Serial.println("Servo motor to 180 degrees");
                myservo.write(180);
                sensorVal = analogRead(sensor);
                voltageVal = (sensorVal / 1024.0) * 5.0;
                temp = (voltageVal - .5) * 100;
                tempf = ((temp * (9 / 5)) + 32);
                Serial.print(tempf);
                Serial.println("  ");
                delay(500);

              }

              else if (command == '2')//turn to 90
              {
                Serial.println("Servo motor to 90 degrees");
                myservo.write(90);
                sensorVal = analogRead(sensor);
                voltageVal = (sensorVal / 1024.0) * 5.0;
                temp = (voltageVal - .5) * 100;
                tempf = ((temp * (9 / 5)) + 32);
                Serial.print(tempf);
                Serial.println("  ");
                delay(500);
              }
              else if (command == '3')//turn to 0
              {
                Serial.println("Servo motor to  degrees");
                myservo.write(20);
                sensorVal = analogRead(sensor);
                voltageVal = (sensorVal / 1024.0) * 5.0;
                temp = (voltageVal - .5) * 100;
                tempf = ((temp * (9 / 5)) + 32);
                Serial.print(tempf);
                Serial.println("  ");
                delay(500);
              }
              else if (command == '4')//break out of loop and start sweeping again
              {
                sensorVal = analogRead(sensor);
                voltageVal = (sensorVal / 1024.0) * 5.0;
                temp = (voltageVal - .5) * 100;
                tempf = ((temp * (9 / 5)) + 32);
                Serial.print(tempf);
                Serial.println("  ");
                cool = 0;
                variable = '0';
                break;
              }
            }
          }
        }
        break;
      }
  }
}




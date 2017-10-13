#include <Servo.h>

//Global Variables
float rpm = 0;
float counter = 0;
int timer = 0;
int pos = 0;
boolean stat = true;

//Servo variable
Servo myservo;

//DC Motor - Digital Pin 3
int motorPin = 3;

//LED - Digital Pin 8
int LEDPin = 8;

void setup()
{
  Serial.begin(9600);
  pinMode(LEDPin, OUTPUT);
  pinMode(motorPin, OUTPUT);
  analogWrite(motorPin, 60);
  myservo.attach(11);

  // Initially Turns Servo to 90 degrees
  myservo.write(0);
}

void loop()
{
  // Hall Effect Sensor Reading
  int value = analogRead(0);

  //Timer
  timer++;

  if (timer == 61)
  {
    rpm = (counter / 60);
    if (rpm > 0.08 && stat == true) //imitates 35km/hr
    {
      analogWrite(motorPin, 30);       //reduces speed in the motor
      Serial.println("ENGINE OFF");    //prints ENGINE OFF
      digitalWrite(LEDPin, HIGH);      //turn the LED ON
      delay(1000);                     //wait for a second
      myservo.write(55);               //turns servo to zero degrees
      stat = false;
    }
    else if (rpm <= 0.08 && stat == false)  //imitates 25km/hr
    {
      analogWrite(motorPin, 60);       //increases speed in the motor
      Serial.println("ENGINE ON");     //prints ENGINE ON
      digitalWrite(LEDPin, LOW);       //turn the LED OFF
      delay(1000);                     //wait for a second
      myservo.write(0);                //turns servo to 90 degrees
      stat = true;
    }
    else if (rpm < 0.08 && stat == true)  //imitates 35km/hr
    {
      analogWrite(motorPin, 30);
      Serial.println("ENGINE OFF");
      digitalWrite(LEDPin, HIGH);
      delay(1000);
      myservo.write(55);
      stat = false;
    }

    else if (rpm >= 0.08 && stat == false)  //imitates 25km/hr
    {
      analogWrite(motorPin, 60);
      Serial.println("ENGINE ON");
      digitalWrite(LEDPin, LOW);
      delay(1000);
      myservo.write(0);
      stat = true;
    }

    //Resets the timer and the Counts of revolutions
    timer = 0;
    counter = 0;
  }

  //Computes the number of revolutions
  if (value > 600)
  {
    counter++;
  }

  //Print Results
  Serial.print(timer); Serial.print(" seconds"); Serial.print("\t");
  Serial.print(counter); Serial.print(" revs"); Serial.print("\t");
  Serial.print(rpm); Serial.println(" rpm");
  delay(250);//displays results for 250ms, before next reading.

}

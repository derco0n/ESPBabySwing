/*
This will drive a servo motor to a 90° position and back in and endless loop.
The speed it does this is calculated by an analog-input of a potentiometer which is connected between 3.3V and GND

This can be used to move a babyswing back and forth and may help them sleep...

This comes without any warranty.
USE AT YOUR OWN RISK.
ALWAYS KEEP AN EYE ON YOUR BABY.

Take care.


Pins used:
==========
GPIO 25: Input Potentiometer
GPIO 26: Output PWM Servo-motor
3.3V: Vcc for the Potentiometer
GND: GND for the Potentiometer and Servo
5.V: Vcc for the Servo-Motor (Attention: depending on the motor's power you may need an extra power-supply instead of powering it via the Microcontroller-Board!)
*/

#include <Servo.h>

#define SERVO_PIN 26 // ESP32 pin GPIO26 connected to servo motor
#define POTI_PIN 25 // ESP32 pi GPIO25 connect to a potentiometer (connected to ground and 3.3V)

Servo servoMotor;
/* Define delay-limits
     Maximum 3 times per second (0-90) (3 full cycles)
     Minimum 0.25 times per second  (1 quarter cycle)

     1 second has 1000ms
     3 cycles have 6*90=540 steps at 90° max opening angle
     0.25 cycles (1 quarter cycle) has 45 steps...
     At minimum speed 45 steps should be done within 1000ms
     Maximumdelay (Min speed) is therefore: 1000/45=22.222 ~ 22ms
     
     At full speed 540 steps must be done within 1000ms
     Minimumdelay (Max speed) is therefore: 1000/540=1,8 ~ 2ms
     
*/
static int MAXANGLE=90; //Maximum angle to open....

static int MINDELAY=2; //see above for calculation
static int MAXDELAY=22; //see above for calculation


void setup() {
  
  servoMotor.attach(SERVO_PIN);  // attaches the servo on ESP32 pin
  Serial.begin(19200); // Open Serial Output
  analogReadResolution(9); //Resolution of 9 Bits (0-511) instead of the default 12
  Serial.println();
  Serial.println("Babyschaukel by Waschi. ;) - 01/2025");
  Serial.println();
  Herz();
}

int readpoti(){ //read from the Potetiometers analogpin an returns a delay value
  int potivalue=analogRead(POTI_PIN);  
  float percentage = 1.0 / 511 * potivalue; // calculate percentage  
  int range=MAXDELAY-MINDELAY;
  int calcdelay=(int)(MAXDELAY-(percentage*(float)range)); //calculate delay based on range and Poti-percentage. (Poti left => more delay)
  Serial.print("Current delay is: ");
  Serial.println(calcdelay);

  return calcdelay;
}

void Herz(){
  Serial.println("     ****     ****     ");
  Serial.println("   **    ** **    **   ");
  Serial.println("  **       *       **  ");
  Serial.println("  **               **  ");
  Serial.println("   **  Für        **   ");
  Serial.println("    **           **    ");
  Serial.println("     **    Lea  **     ");
  Serial.println("      **       **      ");
  Serial.println("       **     **       ");
  Serial.println("        **   **        ");
  Serial.println("         ** **         ");
  Serial.println("          ***          ");
  Serial.println("           *           ");
  Serial.println("           ;           ");
  Serial.println("          ;            ");
  Serial.println("          ;            ");
  Serial.println("          ',           ");
  Serial.println("           ;           ");
  Serial.println("          ,'           ");
  Serial.println("          ;            ");
  Serial.println("          ',           ");
  Serial.println("           ',          ");
  Serial.println("            ;          ");
  Serial.println("           '           ");  
  Serial.println();
  Serial.println();
}

void loop() {
  int delaycur=readpoti();
   
  // rotates from 0 degrees to MAXANGLE degrees
  for (int pos = 0; pos <= MAXANGLE; pos += 1) {
    // in steps of 1 degree
    /*
    Serial.print("Setting motor to angle: ");
    Serial.println(pos);
    */
    servoMotor.write(pos);    
    delay(delaycur); // waits 15ms to reach the position
  }

  // rotates from MAXANGLE degrees to 0 degrees
  for (int pos = MAXANGLE; pos >= 0; pos -= 1) {
    /*
     Serial.print("Setting motor to angle: ");
    Serial.println(pos);
    */
    servoMotor.write(pos);
    delay(delaycur); // waits a few ms to reach the position
  }
}

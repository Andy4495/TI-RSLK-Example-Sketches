/*
   01_Bump_Switch_with_OLED

   0.0.1  A.T.  10/28/2020  Initial Version

   Summary:
   This example has the TI Robotic System Learning Kit (TI RSLK) driving forward
   until it hits an object (ie a bump switch is triggered) then it stops.

   Displays status on NewHaven 2x16 OLED.

   How to run:
   1) Push left button on Launchpad to start the demo
   2) Robot will drive forward until the bump switches are triggered
   3) Once switches are triggered the robot will halt.
   4) Push left button again to start demo

   External Libraries:
   - https://github.com/fcooper/Energia-RSLK-Library
   - https://github.com/Andy4495/NewhavenOLED

   Based on example sketches included with the Energia-RSLK-Library by Franklin Cooper, Jr.

*/

#include "Romi_Motor_Power.h"
/* Defines pin configuration of robot */
#include "RSLK_Pins.h"
#include "SimpleRSLK.h"

// NewHaven OLED object definitions
#include <NewhavenOLED.h>
const byte ROW_N = 2;        // Number of display rows
const byte COLUMN_N = 16;    // Number of display columns
const byte CS = 49;          // LCDCS pin on AF938 Display connector
const byte RES = 62;         // LCDRST pin on AF938 Display connector (optional, can be always high)
const byte SCLK = 66;        // LCDSCLK pin on AF938 Display connector
const byte SDIN = 67;        // LCDMOSI pin on AF938 Display connector
byte new_line[4] = {0x80, 0xA0, 0xC0, 0xE0};               // DDRAM address for each line of the display
NewhavenOLED oled(ROW_N, COLUMN_N, SDIN, SCLK, CS, RES);
const char s1[] = "Push left button to start.      ";   // Padded to 32 characters.
const char s2[] = "Running.                        ";   // Padded to 32 characters.

// End NewHaven OLED object definitions

Romi_Motor_Power left_motor;
Romi_Motor_Power right_motor;
int motorSpeed = 10;

void setup() {
  Serial.begin(115200);

  oled.begin();

  left_motor.begin(MOTOR_L_SLP_PIN,
                   MOTOR_L_DIR_PIN,
                   MOTOR_L_PWM_PIN);

  right_motor.begin(MOTOR_R_SLP_PIN,
                    MOTOR_R_DIR_PIN,
                    MOTOR_R_PWM_PIN);

  pinMode(BP_SW_PIN_0, INPUT_PULLUP);
  pinMode(BP_SW_PIN_1, INPUT_PULLUP);
  pinMode(BP_SW_PIN_2, INPUT_PULLUP);
  pinMode(BP_SW_PIN_3, INPUT_PULLUP);
  pinMode(BP_SW_PIN_4, INPUT_PULLUP);
  pinMode(BP_SW_PIN_5, INPUT_PULLUP);

  /* Left button on Launchpad */
  pinMode(LP_LEFT_BTN, INPUT_PULLUP);
  /* Red led in rgb led */
  pinMode(RED_LED, OUTPUT);


}

void loop() {
  const char* btnMsg = "Push left button on Launchpad to start demo.\n";
  oled.clear();
  oled.write(s1);
  /* Wait until button is pressed to start robot */
  waitBtnPressed(LP_LEFT_BTN, btnMsg, RED_LED);
  oled.clear();
  oled.write(s2);

  /* Enable both motors */
  left_motor.enableMotor();
  right_motor.enableMotor();

  /* Set both motors direction to forward */
  left_motor.directionForward();
  right_motor.directionForward();

  delay(2000);

  /* Set motors speed to 10% of max value */
  left_motor.setSpeed(10);
  right_motor.setSpeed(10);

  // Drive the robot forward until it runs into something
  while (true) {
    if (digitalRead(BP_SW_PIN_0) == 0)
      break;

    if (digitalRead(BP_SW_PIN_1) == 0)
      break;

    if (digitalRead(BP_SW_PIN_2) == 0)
      break;

    if (digitalRead(BP_SW_PIN_3) == 0)
      break;

    if (digitalRead(BP_SW_PIN_4) == 0)
      break;

    if (digitalRead(BP_SW_PIN_5) == 0)
      break;
  }

  Serial.println("Collision detected");
  left_motor.disableMotor();
  right_motor.disableMotor();
}

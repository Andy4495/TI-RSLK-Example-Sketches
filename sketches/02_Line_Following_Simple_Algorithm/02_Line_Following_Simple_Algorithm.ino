/*
   02_Simple_Line_Follower

   0.0.1  A.T.  10/28/2020  Initial Version

   https://github.com/Andy4495/TI-RSLK-Example-Sketches

   Summary:
   This example has the TI Robotic System Learning Kit (TI RSLK) follow a line
   using a simple line following algorithm. This example works on a dark floor with
   a white line or a light floor with a dark line. The robot first needs to be calibrated
   Then place the robot on the hit the left button again to begin the line following.

   Displays status on NewHaven 2x16 OLED.

   How to run:
   1) Push left button on Launchpad to have the robot perform calibration.
   2) Robot will drive forwards by a predefined distance.
   3) Place the robot center on the line you want it to follow.
   4) Push left button again to have the robot follow the line.

   Parts Info:
   - Black eletrical tape or white electrical tape. Masking tape does not work well
     with IR sensors.

   Based on example sketches included with the Energia-RSLK-Library by Franklin Cooper, Jr.
     https://github.com/fcooper/Energia-RSLK-Library

*/

// MSP432 uses the RSLK library built into the platform core
// Tiva needs to have the RSLK library installed from https://github.com/fcooper/Energia-RSLK-Library
// The different libraries have slightly different parameter 
// lists for some functions
#include "SimpleRSLK.h"
// The following #ifndef is to allow compilation with tivac board package
#ifndef __TM4C123GH6PM__
#include <cstdio>
#endif

uint16_t sensorVal[LS_NUM_SENSORS];
uint16_t sensorCalVal[LS_NUM_SENSORS];
uint16_t sensorMaxVal[LS_NUM_SENSORS];
uint16_t sensorMinVal[LS_NUM_SENSORS];

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
//                "Line 1          Line 2          "    // Template with 2x16 spacing for total of 32 chars
const char s0[] = "02 Simple Line  Follower        ";   // Padded to 32 characters.
const char s1[] = "Push left buttonto calibrate.   ";   // Padded to 32 characters.
const char s2[] = "Running         calibration.    ";   // Padded to 32 characters.
const char s3[] = "Reading floor   values complete ";   // Padded to 32 characters.
const char s4[] = "Left button to  start robot.    ";   // Padded to 32 characters.

// End NewHaven OLED object definitions

enum Direction {LEFT, RIGHT};
Direction lastDirection = LEFT;

void setup()
{
  Serial.begin(115200);
  oled.begin();
  oled.clear();
  oled.write(s0);  // Display program info
  delay(1000);

  setupRSLK();
  /* Left button on Launchpad */
  setupWaitBtn(LP_LEFT_BTN);
  /* Red led in rgb led */
  setupLed(RED_LED);
  clearMinMax(sensorMinVal, sensorMaxVal);
}

void floorCalibration() {
  /* Place Robot On Floor (no line) */
  delay(2000);
  oled.clear();
  oled.write(s1);
  /* Wait until button is pressed to start robot */
#if defined(BOARD_MSP_EXP432P401R) || defined(BOARD_MSP_EXP432P4111)
  waitBtnPressed(LP_LEFT_BTN, RED_LED);
#else
  // MSP432 uses the RSLK library built into the platform core instead of 
  // pulling the library from the GitHub link above
  // The MSP432 version does not have the "msg" parameter
  const char* btnMsg = "Push left button on Launchpad to begin calibration.\n" "Make sure the robot is on the floor away from the line.\n";
  waitBtnPressed(LP_LEFT_BTN, btnMsg, RED_LED);
#endif
  delay(1000);

  oled.clear();
  oled.write(s2);
  Serial.println("Running calibration on floor");
  simpleCalibrate();
  oled.clear();
  oled.write(s3);
  Serial.println("Reading floor values complete");

  oled.clear();
  oled.write(s4); 
  /* Wait until button is pressed to start robot */
#if defined(BOARD_MSP_EXP432P401R) || defined(BOARD_MSP_EXP432P4111)
  // MSP432 uses the RSLK library built into the platform core instead of 
  // pulling the library from the GitHub link above
  // The MSP432 version does not have the "msg" parameter
  waitBtnPressed(LP_LEFT_BTN, RED_LED);
#else
  const char* btnMsg2 = "Push left button on Launchpad to begin line following.\n" "Make sure the robot is on the line.\n";
  waitBtnPressed(LP_LEFT_BTN, btnMsg2, RED_LED);
#endif
  delay(1000);

  enableMotor(BOTH_MOTORS);
}

void simpleCalibrate() {
  /* Set both motors direction forward */
  setMotorDirection(BOTH_MOTORS, MOTOR_DIR_FORWARD);
  /* Enable both motors */
  enableMotor(BOTH_MOTORS);
  /* Set both motors speed 20 */
  setMotorSpeed(BOTH_MOTORS, 20);

  for (int x = 0; x < 100; x++) {
    readLineSensor(sensorVal);
    setSensorMinMax(sensorVal, sensorMinVal, sensorMaxVal);
  }

  /* Disable both motors */
  disableMotor(BOTH_MOTORS);
}

bool isCalibrationComplete = false;
void loop()
{
  uint16_t normalSpeed = 7;    /// Originally 10
  uint16_t fastSpeed =  11;    /// Originally 20
  char oled_text[33];

  /* Valid values are either:
      DARK_LINE  if your floor is lighter than your line
      LIGHT_LINE if your floor is darker than your line
  */
  uint8_t lineColor = DARK_LINE;

  /* Run this setup only once */
  if (isCalibrationComplete == false) {
    floorCalibration();
    isCalibrationComplete = true;
    oled.clear();
  }

  readLineSensor(sensorVal);
  readCalLineSensor(sensorVal,
                    sensorCalVal,
                    sensorMinVal,
                    sensorMaxVal,
                    lineColor);

  uint32_t linePos = getLinePosition(sensorCalVal, 0); // 0 -> line is darker than floor
  // The following #ifndef is to allow compilation with tivac board package
  #ifndef __TM4C123GH6PM__
  std::snprintf(oled_text, 33, "Sensor: %8lu                ", linePos);
  #endif
  oled.write(oled_text);

  if (linePos < 100) {   // No line detected
    if (lastDirection == LEFT) {
      setMotorSpeed(LEFT_MOTOR, 0);
      setMotorSpeed(RIGHT_MOTOR, normalSpeed);
      oled.write("                Lost: spin LEFT ");
    }
    else {
      setMotorSpeed(LEFT_MOTOR, normalSpeed);
      setMotorSpeed(RIGHT_MOTOR, 0);
      oled.write("                Lost: spin RIGHT");
    }
  }
  if (linePos <= 1000) {
    setMotorSpeed(LEFT_MOTOR, 0); // If line has drifted far left, then spin right
    setMotorSpeed(RIGHT_MOTOR, fastSpeed);
    lastDirection = LEFT;
  }
  else if ( linePos <= 3000) {
    setMotorSpeed(LEFT_MOTOR, normalSpeed);
    setMotorSpeed(RIGHT_MOTOR, fastSpeed);
    lastDirection = LEFT;
  } else if (linePos < 4000) {
    setMotorSpeed(LEFT_MOTOR, normalSpeed);
    setMotorSpeed(RIGHT_MOTOR, normalSpeed);
    // Going straight, so don't adjust "lastDirection"
  } else if (linePos < 6000) {
    setMotorSpeed(LEFT_MOTOR, fastSpeed);
    setMotorSpeed(RIGHT_MOTOR, normalSpeed);
    lastDirection = RIGHT;
  } else {
    setMotorSpeed(LEFT_MOTOR, fastSpeed);
    setMotorSpeed(RIGHT_MOTOR, 0);
    lastDirection = RIGHT;
  }
}

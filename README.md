TI-RSLK Example Sketches
========================

The TI-RSLK robot kit has a complete online embedded programming course based on it. The course uses Code Composer Studio for the development environment.

A simpler development environment is available by using Energia and fcooper's "Energia-RSLK-Library" which provides easy to use functions to access the various peripherals that are part of the robot chassis. Combined with the multitasking capabilities built into Energia ("Energia-MT", based on Texas Instruments' RTOS) and available for the MSP432 processor, a sophisticated robot control sketch can be created.

This repo contains various example and testing programs that I have created while experimenting with the TI-RSLK.

Sketch Descriptions
-------------------


Display Connection
------------------

The RSLK main board has connections to attach an LCD or OLED display to the robot chassis. The pins directly support SparkFun 10168, Adafruit 338, or Adafruit 938 displays. I don't have any of those displays, so I connected a NewHave 2x16 OLED. Since the pin placement does not match, I created an adapter board that made use of the AF938 connector (which I use because it has a 5V supply pin). The pins are numbers 8 to 1 (left to right) when looking at the chassis from the top:
```
                   Display
SF 10168 LCD
AF 338   LCD
AF 938  OLED  8  7  6  5  4  3  2  1

            AF938  MSP432  J5   Energia
Signal       Pin    Pin    Pin    Pin    Comment
------      -----  ------  ---  -------  ---------------------------------
LCD-MOSI      8     P9.7    21     67    Called "SI" on NewHaven OLED
LCD-SCLK      7     P9.5    19     66    Called "CLK" on NewHaven OLED
LCD-DC        6     P9.6    20     NC    Not used with NewHaven OLED
LCD-RST       5     P9.3    11     62
LCD-CS        4     P9.4    18     49
NC            3      -       -      -    Pin is not connected
5V            2      -       -      -    Note that NewHaven OLED needs 5V, not 3.3V
GND           1      -       -      -   
```

References
----------

+ Texas Instruments TI-RSLK [main page][1].
+ TI-RSLK [curriculum][2].
+ TI-RSLK [schematic][3].
+ TI-RSLK [pin diagram][4].
+ Energia-TI-RSLK [library][5] and [documentation][6].
+ TI-RSLK and MSP432 [pin diagram][7] for Energia.
+ NewHaven OLED [library][8].

[1]:http://www.ti.com/rslk
[2]:https://university.ti.com/en/faculty/ti-robotics-system-learning-kit/ti-rslk-max-edition-curriculum
[3]:https://www.pololu.com/file/0J1670/ti-rslk-max-chassis-board-v1.0-schematic.pdf
[4]:https://www.pololu.com/file/0J1695/ti_rslk_max_chassis_board_pinout.pdf
[5]:https://github.com/fcooper/Energia-RSLK-Library
[6]:https://fcooper.github.io/Energia-RSLK-Library/
[7]:https://embeddedcomputing.weebly.com/ti-rslk-max-pins-maps.html
[8]:https://github.com/Andy4495/NewhavenOLED

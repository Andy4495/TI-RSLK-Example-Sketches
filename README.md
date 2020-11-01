TI-RSLK Example Sketches
========================

The Texas Instruments Robotics System Learning Kit (TI-RSLK) has a complete online embedded programming course based on it. The course uses Code Composer Studio for the development environment.

A simpler development environment is available by using [Energia][11] and Franklin Cooper's "[Energia-RSLK-Library][5]" which provides easy to use functions to access the various peripherals that are part of the robot chassis. Combined with the multitasking capabilities built into Energia ("Energia-MT", based on [TI-RTOS][12]) and available on the MSP432 processor, a sophisticated robot control sketch can be created.

This repo contains various example and testing programs that I have created while experimenting with the TI-RSLK.

Sketch Descriptions
-------------------
All sketches include code to display messages and status information to an external NewHaven 2x16 OLED. The MSP432 controller used by the robot has 256KB flash memory and 64KB RAM, which is more than adequate to support the OLED library and text string storage, whether or not an actual display is used.

### 01_Bump_Switch_with_OLED
This example has the TI RSLK driving forward until it hits an object (i.e. a bump switch is triggered), then it stops.


Display Connection
------------------

The RSLK main board has connections to attach an LCD or OLED display to the robot chassis. The pins directly support SparkFun 10168, Adafruit 338, or Adafruit 938 displays. I don't have any of those displays, so I connected a NewHaven 2x16 OLED. Since the pin placement does not match, I created an adapter board that made use of the AF938 connector (which I use because it has a 5V supply pin). The pins are numbers 8 to 1 (left to right) when looking at the chassis from the top:
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

+ Texas Instruments TI-RSLK [product page][1].
+ TI University [course page][10].
+ TI-RSLK [curriculum][2].
+ TI-RSLK [schematic][3].
+ TI-RSLK [pin diagram][4].
+ Energia-TI-RSLK [library][5] and [documentation][6].
+ TI-RSLK and MSP432 [pin diagram][7] for Energia.
+ NewHaven OLED [library][8].
+ Energia-MT RTOS [overview][14].
+ Energia-MT with Galaxia Library tutorials:
  + [Multitasking][13]
  + [Events][15]
  + [Passing data across tasks][16]
  + [Manage single resource across tasks][17]

[1]:https://www.ti.com/tool/TIRSLK-EVM
[2]:https://university.ti.com/en/faculty/ti-robotics-system-learning-kit/ti-rslk-max-edition-curriculum
[3]:https://www.pololu.com/file/0J1670/ti-rslk-max-chassis-board-v1.0-schematic.pdf
[4]:https://www.pololu.com/file/0J1695/ti_rslk_max_chassis_board_pinout.pdf
[5]:https://github.com/fcooper/Energia-RSLK-Library
[6]:https://fcooper.github.io/Energia-RSLK-Library/
[7]:https://embeddedcomputing.weebly.com/ti-rslk-max-pins-maps.html
[8]:https://github.com/Andy4495/NewhavenOLED
[10]:http://www.ti.com/rslk
[11]:https://energia.nu/
[12]:https://www.ti.com/tool/TI-RTOS-MCU
[13]:https://www.hackster.io/rei-vilo/multi-tasking-with-energia-mt-and-galaxia-library-20bd64
[14]:https://embeddedcomputing.weebly.com/launchpad-msp432-rtos-for-everyone.html
[15]:https://www.hackster.io/rei-vilo/events-with-energia-mt-and-galaxia-library-741d9b
[16]:https://www.hackster.io/rei-vilo/send-data-across-tasks-with-energia-and-galaxia-8be05c
[17]:https://www.hackster.io/rei-vilo/manage-single-resource-with-energia-mt-and-galaxia-cadb26

# GFS-RADAR
This project includes the use of two **RCWL-0516** microwave-Radar modules, a **BLE HC-10**, [lcd name] and a **STM32 Nucleo L152RE** Microcontroller [But many different Microcontroller can be used]. 

## RCWL-0516
<img src="https://github.com/Hannah-Ga/GFS-RADAR/blob/main/images/rcwl-0516.png" width="300" alt="rcwl-0516">

* 3V3: Data Sheets Mentioned it is used to supply power to other Boards, but i have found out, it is possible to run this device through this pin with the 3,3V connector.

* GND: Needs to be connected to a ground pin or negative (if connected to a battery).

* OUT: Delivers a digital signal whether it has detected movement or not.

* VIN: For Power Delivery, Data Sheets mentioned it has a Operating Voltage between 4-28V, connecting it to the 5V pin on a Microcontroller works fine.

* CDS: Is used for LDR, It was unused and unneccessary for myself, so no further Information here.

* R-GN: A Resistor or Potentiometer can be connected between those two contacts in order to reduce detection range. This was neccessary, especially if two or more of those modules are being used in closer Proximity.

  * For this Project in particular i have found out a 180k Ohm Resistor worked the best. while it Still may get the issues due to it being multiple Modules in close Proximity. it works the best for small Objects passing by very close. If used a smaller Resistor (Tested 140k Ohm) It might barely detect something. And if a larger Resistor was used (Tested 240k Ohm) The Rate of accidental triggers rised exponentially.

* C-TM: I haven't used this thus i can only provide the Information given by Datasheets. It appears that if a capacitor will be connected, the length of the HIGH signal can be changed. By default it sends a HIGH signal for ~2 seconds after movement stopped.

* R-CDS: I also haven't used this one, since it is for a LDR, which lets us to disable the Module during the Day.


## How does the RCWL-0516 Work?

From my own experience and from research i can tell, the RCWL-0516 works by using the Doppler effect, sending out a microwave radar signal and "listening" to it. Moving objects disturb the duration of the signal, creating a higher or lower "pitched" version, which the RCWL-0516 is able to detect.

* For a more precise explanation of this phenomenon this [Wikipedia](https://en.wikipedia.org/wiki/Doppler_effect#Radar) article about the Doppler effect provides a detailed explanation.

  * **!The RCWL-0516 is unable to measure the speed of objects, it only can detect IF there is movement**

With this knowledge, i was able to tackle down the issue of Both Modules triggering at the same time, thus the Solution with the Resistor. It is noteworthy that some shielding may help too, but the Materials i had didn't help with this issue and buying new Materials wasn't feasable for the type of project and the time i had. 

# The Project

Now, after i have given neccessary Information about the Module this project was about, its time to dive deeper into the project.

For anyone, who was interested in the solutions of those two modules interfering and/or general information about those and don't seem to care about the rest, then everything from here on may be not of interest for you.

#### Parts used

* [STM32 Nucleo L152RE](https://www.st.com/en/evaluation-tools/nucleo-l152re.html): Microcontroller

* 2x [RCWL-0516](https://lastminuteengineers.com/rcwl0516-microwave-radar-motion-sensor-arduino-tutorial/): Radar Module

* [HC-10 BLE](https://people.ece.cornell.edu/land/courses/ece4760/PIC32/uart/HM10/DSD%20TECH%20HM-10%20datasheet.pdf): Bluetooth Low Energy Module

* [PCF8574](https://www.instructables.com/Using-PCF8574-Backpacks-With-LCDs-and-Arduino/): LCD Display

#### The Idea

Two **RCWL-0516** Modules were placed on wodden Pillars aproximately 50cm away from Each other, facing upwards. If a Object, for example a Hand passes in close Proximity to those Sensors (around 5cm above them), movement will be detected and the Sensors sends a digital HIGH Signal from the OUT pin. This triggers a External Interrupt and Starts a Timer. When the second Sensor also detects movement in a timespan of 4 seconds after the first one, it triggers a Second Interrupt, stopping the Timer and Calculating the average speed of said Object. 

#### Implementation

```attachInterrupt();```

  


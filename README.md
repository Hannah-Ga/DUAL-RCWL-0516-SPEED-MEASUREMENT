# GFS-RADAR
This project includes the use of two **RCWL-0516** microwave-Radar modules, a **BLE HC-10**, [lcd name] and a **STM32 Nucleo L152RE** Microcontroller [But many different Microcontroller can be used]. 
### Project
Two **RCWL-0516** Modules were placed on wodden Pillars aproximately 50cm away from Each other, facing upwards. If a Object, for example a Hand passes in close Proximity to those Sensors (around 5cm above them), movement will be detected and the Sensors sends a HIGH Signal to the Board. This triggers a External Interrupt and Starts a Timer. When the second Sensor also detects movement in a timespan of 4 seconds after the first one, it triggers a Second Interrupt, stopping the Timer and Calculating the average speed of said Object. 

### RCWL-0516
<img src="https://github.com/Hannah-Ga/GFS-RADAR/blob/main/images/rcwl-0516.png" width="300" alt="rcwl-0516">
- 3V3: Data Sheets Mentioned it is used to supply power to other Boards, but i have found out, it is possible to run this device through this pin with the 3,3V connector
- GND: Needs to be connected to a ground pin or negative (if connected to a battery)
- OUT: Delivers a digital signal whether it has detected movement or not
- VIN: For Power Delivery, Data Sheets mentioned it has a Operating Voltage between 4-28V, connecting it to the 5V pin on a Microcontroller works fine
- CDS: Is used for LDR, It was unused and unneccessary for myself, so no further Information here

- R-GN: A Resistor or Potentiometer can be connected between those two contacts in order to reduce detection range. This was neccessary, especially if two or more of those modules are being used in closer Proximity. 
  


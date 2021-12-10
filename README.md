# TERCO-Temperature-Regulating-Clothing
### By Eugene Choe and Jihoon Han

Temperature regulating clothing, or TERCO, is an energy harvesting smart clothing aimed to help people experience temperature regulation while outside. We wanted to design an energy efficient wearable system that provides heating and cooling for outdoor activities, for a lot of people expereince temperature issues due to lack of heating and cooling system outside. Thus, we create a smart clothing, which a wearable that covers the largest surface area on human body, providing temperature control system for both heating and cooling.
<br /> <br />

## Background

### Energy Harvesting
Conventional indoor heating and cooling systems, ranging from electric heater to air conditioner, have one major issue from our perspective: it consumes way too much power. Even smaller portable sized air conditioner and heater takes significant amount of energy. With that, we did not want to contribute for more energy consumption through this and thought about whether making a self-sustainable cooling and heating system. 

Initially, we looked at generating power from body temperature, and there were some articles and reports showing that generating power from human body temperaure is possible. Nevertheless, the power generated from it was roughly around 20 to 25 milliwatt, which is nowhere close to what the system needed, so we had to quickly end this idea and seek for something else.

In the end, solar power turned out to be the most suitable option for the system, as it has a lot of ready-made circuitries for prototyping, and it also generated eonugh power for our system to operate on nearly self-sustainable base. Furthermore, it was the easiest work with as solar panels are widely used in industries and researches.

### Heating and Cooling
For cooling, the best option was using a small fan as it is the most basic, but it works almost the best. However, for heating, we had to think about a couple different options that we had. In the end, we decided to go with a peltier heater, which utilizes the Peltier effect to create heat, since it only required a simple DC voltage and current to generate the amount of heat that we wanted. You can get more information on peltiers from this [website](https://ii-vi.com/how_do_thermoelectric_coolers_tec_work/).

<br /> <br />
## System Overview

TERCO is mainly consist of three major functional blocks: power, control, and heater/cooler. The attached diagram is a block diagram for TERCO. 
<img src="https://github.com/jihoonyyy/TERCO-Temperature-Regulating-Clothing/blob/main/block_diagram.png">

### Power
The power part includes the solar panel, battery, and the power regulator/harvester. The system itself is very simple; the solar panel provides power to the regulator/harvester board up to 6 watt, and once the regulator/harvester receives enough power, it will start charging the li-po battery that is connected to the board. For this, Adafruit's BQ24074 was utilized to maximize the power regulating and harvesting. <br />
<img src="https://github.com/jihoonyyy/TERCO-Temperature-Regulating-Clothing/blob/main/power.png" width=45% height=50%> <img src="https://github.com/jihoonyyy/TERCO-Temperature-Regulating-Clothing/blob/main/harvester.png" width=45% height=50%>

### Control
The control part is responsible for overall system. We decided to use Adafruit Feather STM32F405 Express board, or feather board, from Adafruit, since it is low-power based system at which it still provides all the functionalities including I2C and SPI communcation protocol, 3.3 volt logic control, sufficient input/output pins, and etc. The control board receives data from the temperature sensor, makes decision to generate either heat ot cooling, and shows the information on an attached display. The decision is made based upon user's input; user can set a desired temperature, and once the difference between the measured temperature and the desired temperature is more than a designated offset, which is 3 degree celsius in our system, the peltier/fan starts operating. <br />
<img src="https://github.com/jihoonyyy/TERCO-Temperature-Regulating-Clothing/blob/main/feather.png" width=45% height=50%> <img src="https://github.com/jihoonyyy/TERCO-Temperature-Regulating-Clothing/blob/main/feather_size.png" width=45% height=50%>

### Heater/Cooler
As mentioned, we implemented a heating/cooling system using peltiers and mini fans. Implementation of them are very straight forward, as positive and negative ends are designated with colors, so it would just require right wire connection from the source. To control the amount of control fed into both devices to turn them on and off, we utilized an NMOS as a switch. Referring to the block diagram, the NMOS's drain is connected to the power system, as it provides more current and voltage than an internal regulator from the feather board, and the gate pin is connected to GPIO of the feather board. With an appropriate choice for the NMOS, meaning low drain current and low steady power consumption, we can create a power efficient switch system without using a physical switch. Pictures of the peltier and the fan is attached below. <br />
<img src="https://github.com/jihoonyyy/TERCO-Temperature-Regulating-Clothing/blob/main/peltier.png" width=35% height=30%><img src="https://github.com/jihoonyyy/TERCO-Temperature-Regulating-Clothing/blob/main/fan.png" width=35% height=30%>

<br /> <br />


## Implementation

### Hardware
The picture of overall hardware implementation is attached below <br />
<img src="https://github.com/jihoonyyy/TERCO-Temperature-Regulating-Clothing/blob/main/parts.png">
This hardware implementation is almost the exact realization of the block diagram that we provided. Due to the issue with chip/board supply shortages, we were not able to create a dedicated PCB for it, but for prototyping purposes, we used a breat board to implement the overall system. One difference from the block diagram is that there are two buttons used in this system, and this is for setting up a desired temperature for the user. Designated temperature gets displayed on the display alongside with the current temperature.

Display and the temperature sensor are connected to the feather board through I2C communication. Since they do not require high data bandwidth or fast data transfer, I2C was chosen to save space on the board. SPI could have worked better if we really wanted to save some more energy, but the express board only has a single channel for SPI, so the implementation becomes much simpler if we use I2C as the main communication protocol.

### Software
Although setting up Arduino IDE to work with the Feather Board was a bit tedious, writing and implementing the code in Arduino was fairly straight forward. Arduino IDE is nice in that it has many available libraries and example code that make deployment fairly easy and quick. Some of the libraries that I used in this project were the for the temperature sensor (Adafruit_AHTX0) and LCD display (Adafruit_SSD1306). I also used the Wire library to take care of the I2C communication between the board and both the temperature sensor and the lcd display. 

As seen below, I implemented a very simple feedback control loop system to keep the temperature read by the sensor close to the temperature set by the user. 
<img src="https://github.com/jihoonyyy/TERCO-Temperature-Regulating-Clothing/blob/main/arduino code.png">
This system has three stages, which are cooling (turn fans on, peltiers off), heating (turn peltiers on, fans off), and idle (both peltiers and fans are off). Once the user gets within 2 degrees of the set temperature, the peripherials will turn off to prevent the system from going over the set temperature limit. 

I have also my setting for programming the board below.
<img src="https://github.com/jihoonyyy/TERCO-Temperature-Regulating-Clothing/blob/main/ports.png">

<br /> <br />

## List of Items
1. [Adafruit Feather STM32F405 Express](https://www.adafruit.com/product/4382#description)
2. [Power regulator/harvester: Adafruit BQ24074](https://www.adafruit.com/product/4755#technical-details)
3. [Solar panel](https://www.adafruit.com/product/500)
4. [Li-po battery: 3.7V 4400mAh](https://www.adafruit.com/product/354)
5. [Mini fan](https://www.digikey.com/en/products/detail/sunon-fans/UF3H3-710/4916523)
6. [Peltier](https://www.digikey.com/en/products/detail/cui-devices/CP60133/1747364)
7. [Temperature sensor](https://www.adafruit.com/product/4566)

<br /> <br />

## Pictures and Videos

Please post the video and some pictures, and briefly explain the overall implementation.



<br /> <br />

## Lessons Learned
The implementation of the overall system was not so complicated, but coming up with an energy harvesting system was very difficult. Especially, we learned that power supplied from energy harvesters are often very fickle, leaving the system with an unrealiable power source. We have compensated the system with a decently sized li-po battery, but managing power with a such system is not an easy task. 

Generating appropriate heating was also very tricky; fans were straightforward to implement, but we had to figure out how to use peltiers effectively to tranfer heat to other people. We devised two ways: for a larger peltier, we can use heat sinks to radiate heat to human body, and for a smaller peltier, it can be placed right behind people's neck (not directly touching) to warm the body temperature up.

We also learned that setting up Arduino IDE with mac is tedious with ports nots showing up in Arduino and not being able to see serial communication. We ended up switching back to a Windows machine to DFU our code, which made things simpler. There were also issues starting up the code on the Feather Board, as there were a series of steps that needed to be taken that was not well documented by ADAFruit.. This included needing to pull pin BO high and pressing reset to enable the bootloader, DFU the code onto the board, and then putting pin B0 low and pressing reset again. Figuring this out took a long time and also slowed down our development of our project.

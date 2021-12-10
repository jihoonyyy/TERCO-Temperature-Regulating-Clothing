# TERCO-Temperature-Regulating-Clothing
### By Eugene Choe and Jihoon Han

Temperature regulating clothing, or TERCO, is an energy harvesting smart clothing aimed to help people experience temperature regulation while outside. We wanted to design an energy efficient wearable system that provides heating and cooling for outdoor activities, for a lot of people expereince temperature issues due to lack of heating and cooling system outside. Thus, we create a smart clothing, which a wearable that covers the largest surface area on human body, providing temperature control system for both heating and cooling.

## Background

### Power
Conventional indoor heating and cooling systems, ranging from electric heater to air conditioner, have one major issue from our perspective: it consumes way too much power. Even smaller portable sized air conditioner and heater takes significant amount of energy. With that, we did not want to contribute for more energy consumption through this and thought about whether making a self-sustainable cooling and heating system. 

Initially, we looked at generating power from body temperature, and there were some articles and reports showing that generating power from human body temperaure is possible. Nevertheless, the power generated from it was roughly around 20 to 25 milliwatt, which is nowhere close to what the system needed, so we had to quickly end this idea and seek for something else.

In the end, solar power turned out to be the most suitable option for the system, as it has a lot of ready-made circuitries for prototyping, and it also generated eonugh power for our system to operate on nearly self-sustainable base. Furthermore, it was the easiest work with as solar panels are widely used in industries and researches.

### Heating and Cooling
For cooling, the best option was using a small fan as it is the most basic, but it works almost the best. However, for heating, we had to think about a couple different options that we had. In the end, we decided to go with a peltier heater, which utilizes the Peltier effect to create heat, since it only required a simple DC voltage and current to generate the amount of heat that we wanted. You can get more information on peltiers from this [website](https://ii-vi.com/how_do_thermoelectric_coolers_tec_work/).


## System Overview

TERCO is mainly consist of three major functional blocks: power, control, and heater/cooler. The attached diagram is a block diagram for TERCO. 
<img src="https://github.com/jihoonyyy/TERCO-Temperature-Regulating-Clothing/blob/main/block_diagram.png">

The power part includes the solar panel, battery, and the power regulator/harvester. The system itself is very simple; the solar panel provides power to the regulator/harvester board up to 6 watt, and once the regulator/harvester receives enough power, it will start charging the li-po battery that is connected to the board. For this, Adafruit's BQ24074 was utilized to maximize the power regulating and harvesting capabilites ![integrated](https://github.com/jihoonyyy/TERCO-Temperature-Regulating-Clothing/blob/main/power.png) ![harvester](ttps://github.com/jihoonyyy/TERCO-Temperature-Regulating-Clothing/blob/main/harvester.png)




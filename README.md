
In this project we have build an fully automated Irrigation ststem
1. In order to maximize water potential for the plant, both lysimerer and time interval are controlled.
2. Irrigation can be controled by the soil moisure probe("PM-WCS-3"),When the soil moisture falls below a pre-determined level, irrigation is stopped until the soil moisture stabilizes.
3. Irrgation also controled by the "plant demand", during the day the the loss of weight measured can be translated to evapotranspiration (https://en.wikipedia.org/wiki/Evapotranspiration), and we can irrigate by the water loss.

this project involves 

involve: 
* building a digital scale based on a load cell.
* setting up an ESP32 microcontrollers to receive data from the sensors make the necessary real-time calculations, and control irrigation.\n",
* uploading real-time data to the cloud (e.g. ThingSpeak)

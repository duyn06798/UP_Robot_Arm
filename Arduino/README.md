#Pre-requisite

##Teensy for Arduino IDE
https://www.pjrc.com/teensy/td_download.html

##FlexCAN_T4
https://github.com/tonton81/FlexCAN_T4

##Odrive Teensy CAN library
https://github.com/G-Levine/ODriveTeensyCAN/tree/master

Just need to change line 25 in ODriveTeensyCAN.cpp from 
FlexCAN_T4<CAN0, RX_SIZE_256, TX_SIZE_16> Can0; 
to
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> Can0;
and you should be good to go.

#Tool

##Odrivetool
pip3 install --upgrade odrive

#Documentation

##Odrive 
https://docs.odriverobotics.com/v/latest/index.html
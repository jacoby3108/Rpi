#!/bin/sh

################################################
# Pin 17 is used to  controlling the led state
# Pin 22 is used for reading the phototransistor
################################################

#Define pin 17 as output 

echo "17" > /sys/class/gpio/export
echo "out" > /sys/class/gpio/gpio17/direction

#Define  Pin  22 as input 

echo "22" > /sys/class/gpio/export
echo "in" > /sys/class/gpio/gpio22/direction

# Define useful aliases

export LED="/sys/class/gpio/gpio17/value"
export SENS="/sys/class/gpio/gpio22/value"

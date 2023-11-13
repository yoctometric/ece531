# ECE 531 (Advanced Operating Systems) Final Project

Code by Willow Cunningham, built on top of an operating system by Dr. Vincent Weaver.

## Building / Running

0. git clone this project
1. Install genromfs-0.5.2 into ```./genromfs-0.5.2/```
2. run ```make``` in this directory
3. copy ```.kernel/kernel7.img``` onto an sd card that has been loaded with raspbian
4. slot the SD card into an RPI 3b and power it on


## Overview

Code in this project not written by the professor includes:

1. ```kernel/include/lib/i2c.h```
2. ```kernel/lib/i2c.c```
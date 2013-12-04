#!/usr/bin/python

import spidev
import time
import os

def CISS_make_filename(sensor_name):
	epoch = time.time();
	return sensor_name + '&' + str(epoch)

# Function to read data from MCP3008 chip
# Channel must be an integer 0-7
def ReadChannel(channel):
  adc = spi.xfer2([1,(8+channel)<<4,0])
  print("adc[1]: {}, adc[2]: {}".format(adc[1], adc[2]))
  data = (adc[1]&3 << 8) + adc[2]
  return data

# Open SPI bus
spi = spidev.SpiDev()
spi.open(0,0)

#define delay between readings
delay = 1

while True:
  # Read the FSR data
  ldr_level = ReadChannel(0)

  # Print out results
  print("--------------------------------------------")
  print("LDR: {}".format(ldr_level))

  # Wait before repeating loop
  time.sleep(delay)

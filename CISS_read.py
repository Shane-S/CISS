#!/usr/bin/python
from __future__ import print_function
import spidev
import time
import os

def CISS_make_reading_file(sensor_name, reading):
  epoch = time.time()
  newfile = open(sensor_name + '&' + str(epoch), 'w')
  print(str(reading), file = newfile)
  newfile.close()

# Open SPI bus
spi = spidev.SpiDev()
spi.open(0,0)

# Function to read data from MCP3008 chip
# Channel must be an integer 0-7
def ReadChannel(channel):
  adc = spi.xfer2([1,(8+channel)<<4,0])
  data = (adc[1]&3 << 8) + adc[2]
  return data

#define delay between readings
delay = 1

while True:
  # Read the LDR data
  ldr_level = ReadChannel(0)

  # Print out results
  print("--------------------------------------------")
  print("LDR: {}".format(ldr_level))

  # Wait before repeating loop
  time.sleep(delay)

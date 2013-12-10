#!/usr/bin/python
from __future__ import print_function
import spidev
import time
import os

# Makes a file in the form '[sensor name]&[epoch in ms]' with the reading
# as its contents
def CISS_make_reading_file(sensor_name, reading):
  epoch = long((datetime.datetime.utcnow() - datetime.datetime(1970, 1, 1)).total_seconds() * 1000)
  newfile = open('./sensor_data' + sensor_name + '&' + str(epoch), 'w')
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

# Open SPI bus
spi = spidev.SpiDev()
spi.open(0,0)

#define delay between readings
delay = 3

while True:
  # Read the LDR data
  ldr_level = ReadChannel(0)

  # Write the file
  CISS_make_reading_file('Light', ldr_level)
 
  # Wait before repeating loop
  time.sleep(delay)

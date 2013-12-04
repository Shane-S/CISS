import time
import RPi.GPIO as GPIO

#	+R on 23
#	+G on 24
#	+B on 25
#	LEDSETUP() must be called first

def LEDSETUP():
	GPIO.setmode(GPIO.BCM)
	GPIO.setup(23, GPIO.OUT)
	GPIO.setup(24, GPIO.OUT)
	GPIO.setup(25, GPIO.OUT)

def LED_OFF():
	GPIO.output(23, GPIO.LOW)
	GPIO.output(24, GPIO.LOW)
	GPIO.output(25, GPIO.LOW)

def LED_RED():
	GPIO.output(23, GPIO.LOW)
	GPIO.output(24, GPIO.HIGH)
	GPIO.output(25, GPIO.HIGH)

def LED_GREEN():
	GPIO.output(23, GPIO.HIGH)
	GPIO.output(24, GPIO.LOW)
	GPIO.output(25, GPIO.HIGH)

def LED_BLUE():
	GPIO.output(23, GPIO.HIGH)
	GPIO.output(24, GPIO.HIGH)
	GPIO.output(25, GPIO.LOW)

GPIO.cleanup()
LEDSETUP()
LED_RED()
time.sleep(2)
LED_BLUE()
time.sleep(2)
LED_GREEN()
#GPIO.output(24, GPIO.HIGH)
#GPIO.output(23, GPIO.HIGH)
#GPIO.output(25, GPIO.LOW)
time.sleep(2)
LED_OFF()
GPIO.cleanup()

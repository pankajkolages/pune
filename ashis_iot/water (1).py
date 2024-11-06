#water simple code
import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(16,GPIO.IN)
GPIO.setup(4,GPIO.OUT)

while True:
    if GPIO.input(16):
        print("led on")
        GPIO.output(4,True)
    else:
        GPIO.output(4,False)

GPIO.cleanup()










#chatgpt program
import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)  # Use BCM GPIO numbering
GPIO.setwarnings(False)  # Suppress GPIO warnings
GPIO.setup(16, GPIO.IN)  # Set pin 16 as input
GPIO.setup(4, GPIO.OUT)  # Set pin 4 as output

try:
    while True:
        if GPIO.input(16):  # Check if input on pin 16 is high
            print("LED on")
            GPIO.output(4, True)  # Turn LED on
        else:
            GPIO.output(4, False)  # Turn LED off
        time.sleep(0.1)  # Short delay to avoid rapid toggling

except KeyboardInterrupt:
    print("Exiting program")

finally:
    GPIO.cleanup()  # Clean up GPIO settings on exit

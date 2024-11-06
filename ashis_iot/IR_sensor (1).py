
import RPi.GPIO as GPIO
import time

sensor = 16  # IR sensor pin
led = 12     # LED pin
buzzer = 18  # Buzzer pin

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)  # Suppress initial warnings
GPIO.setup(sensor, GPIO.IN)  # Set up IR sensor as input
GPIO.setup(led, GPIO.OUT)    # Set up LED as output
GPIO.output(led, False)      # Initialize LED to off
GPIO.setup(buzzer, GPIO.OUT) # Set up Buzzer as output
GPIO.output(buzzer, False)   # Initialize Buzzer to off

try:
    while True:
        if GPIO.input(sensor):  # If sensor detects an object
            GPIO.output(led, True)       # Turn on LED
            GPIO.output(buzzer, True)    # Turn on Buzzer
            print("Object detected")

            # Wait until object is no longer detected to prevent continuous buzzing
            while GPIO.input(sensor):
                time.sleep(0.2)  # Small delay to reduce CPU load

        else:
            GPIO.output(led, False)      # Turn off LED
            GPIO.output(buzzer, False)   # Turn off Buzzer
            print("Object not detected")

except KeyboardInterrupt:
    print("Exiting program")

finally:
    GPIO.cleanup()  # Clean up GPIO settings on exit




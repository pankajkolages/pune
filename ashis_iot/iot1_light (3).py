#single led
import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)  # Set the pin numbering system
GPIO.setwarnings(False)  # Disable warnings
GPIO.setup(12, GPIO.OUT)  # Set pin 12 as an output pin

try:
    while True:
        print("LED on")
        GPIO.output(12, GPIO.HIGH)  # Turn LED on
        time.sleep(1)
        
        print("LED off")
        GPIO.output(12, GPIO.LOW)  # Turn LED off
        time.sleep(1)

except KeyboardInterrupt:
    print("Exiting program")
finally:
    GPIO.cleanup()  # Clean up GPIO settings


#led and buzzer
import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(12,GPIO.OUT)
GPIO.setup(19,GPIO.OUT)

try:
    while True:
        print("light and buzzer on")
        GPIO.output(12,GPIO.HIGH)
        GPIO.output(19,GPIO.HIGH)
        time.sleep(1)

        print("light and buzzer of")
        GPIO.output(12,GPIO.LOW)
        GPIO.output(19,GPIO.LOW)
        time.sleep(1)

except KeyboardInterrupt:
    print("exiting program")

finally:
    GPIO.cleanup()


# #two led
# import RPi.GPIO as GPIO
# import time

# GPIO.setmode(GPIO.BCM)
# GPIO.setwarnings(False)
# GPIO.setup(12,GPIO.OUT)

# try:
#     while True:
#         print("led on")
#         GPIO.output(12,GPIO.HIGH)
#         GPIO.output(19,GPIO.HIGH)
#         time.sleep(1)

#         print("led of")
#         GPIO.output(12,GPIO.LOW)
#         GPIO.output(19,GPIO.low)
#         time.sleep(1)

# except KeyboardInterrupt:
#     print("exiting program")

# finally:
#     GPIO.cleanup()


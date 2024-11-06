# import adafruit_dht
# import board
# import time
# import RPi.GPIO as GPIO

# # Set up the DHT11 sensor on GPIO pin 4
# dht_device = adafruit_dht.DHT11(board.D4)


# # Set up GPIO mode and pins
# GPIO.setmode(GPIO.BCM)
# GPIO.setup(16, GPIO.OUT)    # Set GPIO 18 as output for LED

# try:
#     while True:
#         # Get temperature and humidity readings
#         temperature_c = dht_device.temperature  # Read temperature in Celsius
#         temperature_f = temperature_c * (9 / 5) + 32  # Convert to Fahrenheit
#         humidity = dht_device.humidity  # Read humidity percentage

#         # Display temperature and humidity readings
#         print("Temp: {:.1f}C / {:.1f}F    Humidity: {}%".format(temperature_c, temperature_f, humidity))

#         # Control LED based on humidity
#         if humidity > 20:  # If humidity is greater than 20%
#             print("LED on")
#             GPIO.output(16, True)  # Turn LED on
#         else:
#             GPIO.output(16, False)  # Turn LED off

#         time.sleep(2.0)  # Delay between readings

# except RuntimeError as err:
#     # Handle errors from the DHT sensor (common for this sensor type)
#     print("Error:", err.args[0])
#     time.sleep(2.0)  # Delay to allow the sensor to stabilize

# except KeyboardInterrupt:
#     print("Program interrupted by user")

# finally:
#     GPIO.cleanup()  # Clean up GPIO settings on exit


import adafruit_dht
import board
import time
import RPi.GPIO as GPIO

dht_device=adafruit_dht.DHT11(board.D4)

GPIO.setmode(GPIO.BCM)
GPIO.setup(16,GPIO.OUT)

try:
    while True:
        temperature_c=dht_device.temperature
        temperature_f=temperature_c*(9/5) + 32
        humidity = dht_device.humidity

        print("Temp:{:.1f}C / {:.1f}F humidity:{}%".format(temperature_c,temperature_f,humidity))

        if humidity>20:
            GPIO.output(16,True)
        else:
            GPIO.output(16,False)
        
        time.sleep(2.0)

except RuntimeError as err:
    print("error:",err.args[0])
    
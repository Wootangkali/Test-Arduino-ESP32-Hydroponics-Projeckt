import network
from umqtt.robust import MQTTClient
import time
import os
import gc
import sys
from machine import Pin
from machine import Timer
import hcsr04


ultrasonic = hcsr04.HCSR04(trigger_pin=13, echo_pin=15, echo_timeout_us=1000000)

                                             ##EMMAD channel##
# WiFi connection information
wifiSSID = 'MT-Link_C99F10'
wifiPassword = '03168605380'

                                            ##FOR WIFI CONNECTION##
# turn off the WiFi Access Point
ap_if = network.WLAN(network.AP_IF)
ap_if.active(False)

# connect the device to the WiFi network
wifi = network.WLAN(network.STA_IF)
wifi.active(True)
wifi.connect(wifiSSID, wifiPassword)

# wait until the device is connected to the WiFi network
MAX_ATTEMPTS = 20
attempt_count = 0
while not wifi.isconnected() and attempt_count < MAX_ATTEMPTS:
    attempt_count += 1
    time.sleep(1)

if attempt_count == MAX_ATTEMPTS:
    print('could not connect to the WiFi network')
    sys.exit()






                                         ## create a random MQTT clientID ##
randomNum = int.from_bytes(os.urandom(3), 'little')
myMqttClient = bytes("client_"+str(randomNum), 'utf-8')
print(myMqttClient)

THINGSPEAK_URL = b"mqtt.thingspeak.com" 
client = MQTTClient(client_id=myMqttClient, 
                    server=THINGSPEAK_URL, 
                    user='HScQEBINGxAhNxcQLBs0ACk', 
                    password='Xy0qRsITNLeE9Y', 
                    ssl=False)


try:            
    client.connect()
except Exception as e:
    print('could not connect to MQTT server {}{}'.format(type(e).__name__, e))
    sys.exit()



THINGSPEAK_CHANNEL_ID = b'1578015'
THINGSPEAK_CHANNEL_WRITE_API_KEY = b'0JAWI8LI5BOK6ULW'
PUBLISH_PERIOD_IN_SEC = 30 

while True:
    try:
        
        distance = ultrasonic.distance_cm()
        freeHeapInBytes = gc.mem_free()
        credentials = bytes("channels/{:s}/publish/{:s}".format(THINGSPEAK_CHANNEL_ID, THINGSPEAK_CHANNEL_WRITE_API_KEY), 'utf-8')  
        payload = bytes("field3={}" .format(str(distance)), 'utf-8')
        print(payload)
        client.publish(credentials, payload)
        time.sleep(PUBLISH_PERIOD_IN_SEC)
    except KeyboardInterrupt:
        print('Ctrl-C pressed...exiting')
        client.disconnect()
        sys.exit()   


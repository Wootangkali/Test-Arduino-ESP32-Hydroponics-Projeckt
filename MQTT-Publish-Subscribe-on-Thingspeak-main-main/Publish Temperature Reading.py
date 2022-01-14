import network
from umqtt.robust import MQTTClient
import time
import os
import gc
import sys
import dht
#                                             EMMAD channel
# WiFi connection information
wifiSSID = 'MT-Link_C99F10'
wifiPassword = '03168605380'
d = dht.DHT11(machine.Pin(15))

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
  
# create a random MQTT clientID 
randomNum = int.from_bytes(os.urandom(3), 'little')
myMqttClient = bytes("client_"+str(randomNum), 'utf-8')
print(myMqttClient)
# connect to Thingspeak MQTT broker
# connection uses unsecure TCP (port 1883)
# 
# To use a secure connection (encrypted) with TLS: 
#   set MQTTClient initializer parameter to "ssl=True"
#   Caveat: a secure connection uses about 9k bytes of the heap
#         (about 1/4 of the micropython heap on the ESP8266 platform)
THINGSPEAK_URL = b"mqtt.thingspeak.com" 
#THINGSPEAK_USER_ID = b'emmad997'
#THINGSPEAK_MQTT_API_KEY = b'348X545RWPWFGY3A'
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

# publish free heap statistics to Thingspeak using MQTT
THINGSPEAK_CHANNEL_ID = b'1578015'
THINGSPEAK_CHANNEL_WRITE_API_KEY = b'0JAWI8LI5BOK6ULW'
PUBLISH_PERIOD_IN_SEC = 30 
while True:
    try:
        d.measure()
        t = d.temperature()
        h = d.humidity()
        print(t,h)
        #payload = "field1=" + str(t) + "&field2=" + str(h)
        
        freeHeapInBytes = gc.mem_free()
        credentials = bytes("channels/{:s}/publish/{:s}".format(THINGSPEAK_CHANNEL_ID, THINGSPEAK_CHANNEL_WRITE_API_KEY), 'utf-8')  
        payload = bytes("field1={}&field2={}" .format(str(t), str(h)), 'utf-8')
        print(payload)
        #payload = bytes("field1={:.1f}\n".format(freeHeapInBytes), 'utf-8')
        client.publish(credentials, payload)
        time.sleep(PUBLISH_PERIOD_IN_SEC)
    except KeyboardInterrupt:
        print('Ctrl-C pressed...exiting')
        client.disconnect()
        sys.exit()   

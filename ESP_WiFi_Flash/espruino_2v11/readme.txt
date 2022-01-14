 _____                 _                                                        
|   __|___ ___ ___ _ _|_|___ ___                                                
|   __|_ -| . |  _| | | |   | . |                                               
|_____|___|  _|_| |___|_|_|_|___|                                               
          |_|                                                               
   Copyright 2015 Gordon Williams
                                               
http://www.espruino.com

--------------------------------------------------------------

There are a few different binaries in this ZIP file, for different
types of Microcontroller:

espruino_2v11_pico_1r3.bin 
   - AT command WiFi support (includes all features)
espruino_2v11_pico_1r3_cc3000.bin 
   - CC3000 WiFi networking (without debugger, AT Command WiFi, vector font)
espruino_2v11_pico_1r3_wiznet.bin  
   - WIZNET W5500 ethernet (without debugger, AT Command WiFi, vector font)
 
   - The firmware image for Espruino Pico Boards.
     We'd strongly suggest that you use the Web IDE to flash this.
     Each image is for a different type of networking device.
     If you don't need networking, use espruino_2v11_pico_1r3.bin

espruino_2v11_espruino_1r3.bin  
   - No networking, includes all other features
espruino_2v11_espruino_1r3_at.bin  
   - AT command WiFi (without vector font)
espruino_2v11_espruino_1r3_wiznet.bin   
   - WIZNET W5500 ethernet (without crypto lib, debugger, vector font)

   - The firmware image for Original Espruino Boards
     We'd strongly suggest that you use the Web IDE to flash this.
     Each image is for a different type of networking device.
     If you don't need networking, use espruino_2v11_espruino_1r3.bin

espruino_2v11_wifi.bin  
   - The firmware image for Espruino WiFi Boards
     We'd strongly suggest that you use the Web IDE to flash this.

espruino_2v11_puckjs.zip
   - The firmware image for Espruino Puck.js Devices
     See http://www.espruino.com/Puck.js#firmware-updates for more information

espruino_2v11_pixljs.zip
   - The firmware image for Espruino Pixl.js Devices
     See http://www.espruino.com/Pixl.js#firmware-updates for more information

espruino_2v11_banglejs.zip
   - The firmware image for Espruino Bangle.js 1 Devices
     See http://www.espruino.com/Bangle.js#firmware-updates for more information

espruino_2v11_banglejs2.zip
   - The firmware image for Espruino Bangle.js 2 Devices
     See http://www.espruino.com/Bangle.js2#firmware-updates for more information

espruino_2v11_mdbt42q.zip
   - The firmware image for Espruino MDBT42Q modules
     See http://www.espruino.com/MDBT42Q#firmware-updates for more information

espruino_2v11_stm32l496gdiscovery.bin
   - STM32F496GDISCOVERY board

espruino_2v11_stm32vldiscovery.bin
   - STM32VLDISCOVERY board

espruino_2v11_stm32f4discovery.bin
   - STM32F4DISCOVERY board

espruino_2v11_nucleof401re.bin
   - ST NUCLEO-F401RE board

espruino_2v11_nucleof411re.bin
   - ST NUCLEO-F411RE board

espruino_2v11_microbit1/2.hex
   - Espruino for the BBC micro:bit 1 or 2 - just copy the correct file onto the
     flash drive that appears when you plug the micro:bit in.

espruino_2v11_Wio_LTE.zip
   - The firmware image for Seed Wio LTE Devices
     See http://www.espruino.com/WioLTE for more information

espruino_2v11stm32l496gdiscovery.bin
   - The firmware image for the STM32L496G Discovery Board
     See http://www.espruino.com/STM32L496GDISCOVERY for more information

espruino_2v11rak8211.hex
   - The firmware image for the RAK8211 iTracker
     See http://www.espruino.com/RAK8211 for more information

espruino_2v11rak8212.hex
   - The firmware image for the RAK8212 iTracker
     See http://www.espruino.com/RAK8212 for more information

espruino_2v11smartibot.zip
   - The firmware image for the Smartibot robot board
     See http://www.espruino.com/Smartibot for more information

ESP8266 / ESP32
---------------

See http://www.espruino.com/EspruinoESP8266 for more info

espruino_2v11_esp8266_combined_512.bin
   - ESP8266 'combined' port for 512k devices like ESP01
       Flash with: esptool.py write_flash 0 espruino_2v11_esp8266_combined_512.bin

espruino_2v11_esp8266_4mb_combined_4096.bin
   - ESP8266 'combined' port for 4MB devices like ESP12
       Flash with: esptool.py write_flash 0 espruino_2v11_esp8266_combined_4096.bin

espruino_2v11_esp8266
   - ESP8266 port as separate files - see README in directory for more information

espruino_2v11_esp8266_4mb
   - ESP8266 port for 4mb devices as separate files - see README in directory for more information

espruino_2v11_esp32.zip
   - The firmware image for ESP32 Devices
     See http://www.espruino.com/ESP32 for more information




For more information on devices, and on how to flash these binary files on to 
each device, please see our website, http://www.espruino.com

NOTES:

* On the STM32F4DISCOVERY the default USART is USART2 (because
USART1 shares some pins with USB). This means you must connect
serial connections to PA2/PA3 NOT PA9/PA10 as you would for
the STM32VLDISCOVERY.


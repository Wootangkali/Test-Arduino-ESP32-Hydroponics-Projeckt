# Mega2560-AutoReset-Serial-Optiboot
Długo szukałem rozwiązania zdalnego programowania na lokalu Arduino bez wpinania się bezpośrednio do płytki.

- geneza - programowanie poprzez sieć LAN - socket TCP/UDP na adresie IP - RX,TX z adaptera WIFI/LAN do Arduino.
- Prosty skrypt detekcji nagłówka sekwencji startu programowania dla bootloadera Optiboot.
- Układ resetu z wyjście Arduino np D12 - R1K -> ULN2004 (do GND)> -<dioda_shotky< - Pin Reset Arduino
- Zmieniony Bootloader w Mega 2560 na Optiboot
- Moduły do komunikacji z Arduino Mega:
- WiFi - ESP8266 z esp-link - posiada opcje resetowania ale trzeba użyć Megaload. 
- LAN - Eport PRO EP20PRO linux (hi-flying)- tryb Serial
- TCP/UDP to IP Socket - Virtual port pod Windows 10 - Net Burner Virtual Com Port wersja 2.1 (nie działa zmiana Baud Rate)

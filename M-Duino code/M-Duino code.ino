/*
   Copyright (c) 2019 Boot&Work Corp., S.L. All rights reserved

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

// M-Duino code



#include <WifiModule.h>

void setup() {
  Serial.begin(19200UL);
  WifiModule.begin(19200UL);
  // Initialize the output variables as outputs
  pinMode(Q0_0, OUTPUT);
  pinMode(Q0_1, OUTPUT);
  // Set outputs to LOW
  digitalWrite(Q0_0, LOW);
  digitalWrite(Q0_1, LOW);
}

void loop(){
  int order;
  if (WifiModule.available()){
    order=WifiModule.read();
    Serial.println(order);
   
    switch(order){
      case 0:
        digitalWrite(Q0_0, LOW);
        break;
      case 1:
        digitalWrite(Q0_0, HIGH);
        break;
      case 8:
        digitalWrite(Q0_1, LOW);
        break;
      case 9:
        digitalWrite(Q0_1, HIGH);
        break;
    }
  }
}
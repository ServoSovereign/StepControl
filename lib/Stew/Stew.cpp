#include "Stew.h"

String getSerialString(){
    String received = "";
    while(Serial.available() == 0)
        delay(50);
    delay(20);
    while(Serial.available() > 0){
        char c = Serial.read();
        if (c == '\n' || c == '\r') break;
        received += c;
    }
    return received;
}
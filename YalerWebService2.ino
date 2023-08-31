// Copyright (c) 2014, Yaler GmbH, Switzerland
// All rights reserved

#include <SPI.h>
#include <Ethernet.h>
#include <YalerEthernetServer.h>

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
//String dataTemp;
String dataFinal;
//char y;


// Enter a MAC address for your controller below.
// Some Ethernet shields have a MAC address printed on a sticker
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0F, 0x42, 0x63 };

// Local EthernetServer at http://LOCAL_IP/ (e.g. http://192.168.0.7/)
//EthernetServer server(80);

YalerEthernetServer server("try.yaler.net", 80, "gsiot-sw4f-0884");

void setup() {
  Serial.begin(9600);
   // reserve 200 bytes for the inputString:
  inputString.reserve(200); 
  
  Serial.println("Aquiring IP address...");
  
  if (Ethernet.begin(mac) == 0) 
    {
       Serial.println("DHCP failed."); 
    } 
  else 
    {
       Serial.println(Ethernet.localIP());
       server.begin(); 
    }

}


void loop() {
EthernetClient client = server.available();    
  // print the string when a newline arrives:
  
  if (stringComplete) 
    {
      Serial.print(inputString); 
      // clear the string:
      dataFinal=inputString;
      inputString = "";
      stringComplete = false;  
    }

   if (client && client.connected()) {
    client.find("\r\n\r\n"); // Consume incoming request
    sendResponse(client);
    delay(100); // Give the Web browser time to receive the data
   client.stop();
  }

}  // loop end brace

 
 
void sendResponse(EthernetClient client) {
  
 client.print(dataFinal);  
 dataFinal="";
}  


void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    inputString += inChar;
    if (inChar == byte(0x0a)) {
      stringComplete = true;
    } 
  }
}






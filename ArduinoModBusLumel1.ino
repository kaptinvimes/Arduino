

// Include these libraries for using the RS-485 and Modbus functions
#include <RS485.h>
#include <ModbusMaster485.h>
#include <SPI.h>

// Instantiate ModbusMaster object as slave ID 1
ModbusMaster485 node(1);

// Define one address for reading
#define address 7505  // current display
// Define the number of bytes to read
#define bytesQty 2

void setup()
{
  pinMode(5, OUTPUT);
  digitalWrite(5, LOW);  
  
byte array[4] = {0,0,0,0};
  // Power on the USB for viewing data in the serial monitor
  Serial.begin(9600);
  delay(100);
  // Initialize Modbus communication baud rate
  node.begin(9600);

  // Print hello message
  Serial.println("Modbus communication over RS-485");
  delay(100);
  
}


void loop()
{
char display[9];
char tempAr1[3];
char tempAr2[3];
char tempAr3[3];
char tempAr4[3];
String hex1;
String hex2;
String hex3;
String hex4;
int result =  node.readHoldingRegisters(address, bytesQty); 
if (result != 0) { Serial.println("Communication error");   
delay(1000); } 
else {
String current=String(node.getResponseBuffer(0),HEX);    // first 16 bits of 32 bit register in Hex
String current1=String(node.getResponseBuffer(1),HEX);   // last 16 bits of 32 bit register in Hex
String currentDisplayValue=current+current1;             // reconstruct 32 bit register in Hex
hex1=currentDisplayValue.substring(0, 2); // will be byte 1
hex2=currentDisplayValue.substring(2, 4); // will be byte 2 
hex3=currentDisplayValue.substring(4, 6); // will be byte 3
hex4=currentDisplayValue.substring(6, 8); // will be byte 4 
hex1.toCharArray(tempAr1,3); // convert to character array
hex2.toCharArray(tempAr2,3); // convert to character array
hex3.toCharArray(tempAr3,3); // convert to character array
hex4.toCharArray(tempAr4,3); // convert to character array
int f1=strtol(tempAr1,NULL,16); // convert to decimal int
int f2=strtol(tempAr2,NULL,16); // convert to decimal int
int f3=strtol(tempAr3,NULL,16); // convert to decimal int
int f4=strtol(tempAr4,NULL,16); // convert to decimal int
byte array[4] = {f1,f2,f3,f4};
Serial.print(convert(array),4);
Serial.print("\n");
delay(1000);    
  }
  node.clearResponseBuffer();
}




typedef union {
 byte array[4];
 float value;
} ByteToFloat;

float convert(byte* data) {
 ByteToFloat converter;
 for (byte i = 0; i < 4; i++){
   converter.array[3-i] = data[i]; //or converter.array[i] = data[i]; depending on endianness 
 }
 return converter.value;
}


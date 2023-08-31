// 25/02/2016
// 07555611202 number used on main unit
// Include the GSM library
#include <GSM.h>
// PIN Number
#define PINNUMBER ""
// initialize the library instance
GSM gsmAccess;
GSMVoiceCall vcs;
// Array to hold the number for the incoming call
char number[13];  // Holds the emitting number
int alarmOut1 = 8;
int alarmOut2 = 9;
int alarmOut3 = 10;
int alarmOut4 = 11;
int alarmOut5 = 12;
int clearAlarms = 13;
int alarm = 0;
int anyAlarmActive = 0;
int active = LOW;
int inactive = HIGH;

//-----Setup--------------------------------------------------------
void setup() {

  // initialize digital pins.
  pinMode(alarmOut1, OUTPUT);
  pinMode(alarmOut2, OUTPUT);
  pinMode(alarmOut3, OUTPUT);
  pinMode(alarmOut4, OUTPUT);
  pinMode(alarmOut5, OUTPUT);
  pinMode(clearAlarms, INPUT_PULLUP);
  pinMode(clearAlarms, INPUT);
  digitalWrite(alarmOut1, LOW);
  digitalWrite(alarmOut2, LOW);
  digitalWrite(alarmOut3, LOW);
  digitalWrite(alarmOut4, LOW);
  digitalWrite(alarmOut5, LOW);

  // initialize serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("Receive Voice Call");

  // connection state
  boolean notConnected = true;
  // Start GSM shield
  // If your SIM has PIN, pass it as a parameter of begin() in quotes
  while (notConnected) {
    if (gsmAccess.begin(PINNUMBER) == GSM_READY) {
      notConnected = false;
    } else {
      Serial.println("Not connected");
      delay(1000);
    }
  }

  // This makes sure the modem correctly reports incoming events
  vcs.hangCall();
  Serial.println("Waiting for a call");
}
//------Begin Main Loop---------------------------------------------

void loop() {

  // Check the status of the voice call
  switch (vcs.getvoiceCallStatus()) {
    case IDLE_CALL: // Nothing is happening
    break;
    case RECEIVINGCALL: // Yes! Someone is calling us
          Serial.println("RECEIVING CALL");
          // Retrieve the calling number
          vcs.retrieveCallingNumber(number, 13);
          String callingNumber (number);   
          callingNumber.trim();
          
          if (callingNumber == "07555611200") alarm = 1;
          if (callingNumber == "07555611201") alarm = 2;
          if (callingNumber == "07555610919") alarm = 3;
          if (callingNumber == "07555611236") alarm = 4;
          if (callingNumber == "07464460788") alarm = 5;
          if (callingNumber == "07411036793") alarm = 6;

          // Print the calling number
          Serial.print("Number ");         
          Serial.print(number);
          Serial.print("\n");
          Serial.print("Calling number ");            
          Serial.print(callingNumber);
          Serial.print("\n");
          Serial.print("Alarm ");            
          Serial.print(alarm);
          Serial.print("\n");
          vcs.hangCall();
          Serial.println("Hanging up and waiting for the next call.");
          callingNumber="";
          number[0]=0;
     break;
  }
  delay(1000);

  //------Check for active alarms---------------------------------------------

  switch (alarm)
  {
    case 1:
      digitalWrite(alarmOut1, HIGH);
      alarm = 0;      
      delay(500);
    break;
    
    case 2:
      digitalWrite(alarmOut2, HIGH);
      alarm = 0;      
      delay(500);
    break;

    case 3:
      digitalWrite(alarmOut3, HIGH);
      alarm = 0;      
      delay(500);
    break;

    case 4:
      digitalWrite(alarmOut4, HIGH);
      alarm = 0;      
      delay(500);
    break;

    case 5:
      digitalWrite(alarmOut5, HIGH);
      alarm = 0;      
      delay(500);
    break;

    case 6:
      digitalWrite(alarmOut1, HIGH);
      digitalWrite(alarmOut2, HIGH);
      digitalWrite(alarmOut3, HIGH);
      digitalWrite(alarmOut4, HIGH);
      digitalWrite(alarmOut5, HIGH);
      delay(5000);
      digitalWrite(alarmOut1, LOW);
      digitalWrite(alarmOut2, LOW);
      digitalWrite(alarmOut3, LOW);
      digitalWrite(alarmOut4, LOW);
      digitalWrite(alarmOut5, LOW);
      alarm = 0;
      delay(500);
    break;

    default:
      alarm = 0;
  }
       /*   Serial.print(number);
          Serial.print("\n");
          Serial.print(alarm);
          Serial.print("\n");*/
//------------------------------------------------------------------  
  //             Clear Output Alarms

  if (digitalRead(clearAlarms) == LOW)
      {
          delay(10000);
          if (digitalRead(clearAlarms) == LOW) clearAllOutputs();
      }
      
}

//------End Main Loop-----------------------------------------------

void clearAllOutputs() 
{
  digitalWrite(alarmOut1, LOW);
  digitalWrite(alarmOut2, LOW);
  digitalWrite(alarmOut3, LOW);
  digitalWrite(alarmOut4, LOW);
  digitalWrite(alarmOut5, LOW);
  digitalWrite(clearAlarms, HIGH);
  alarm = 0;
}



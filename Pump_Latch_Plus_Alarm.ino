//
// 22/05/2016

// 8 Way Alarm Unit -  8 way relay board HIGH TO ACTIVATE (Normally Open Inputs)
// External relay now LOW on test
// 5 second delay before test activated
// Changes to test button checking

// Set Vars

int pumpRun = false;
int on = LOW;
int off = HIGH;

int lowLevel = 0;
int highLevel = 1;
int bundHigh = 2;
int alarmIn4 = 3; // spare
int alarmIn5 = 4; // spare
int alarmIn6 = 5; // spare
int alarmIn7 = 6; // spare
int alarmIn8 = 7; // spare
int dayTankLowLamp = 9;
int dayTankHighLamp = 8;
int bundHighLamp = 10;
int pumpControlRelay = 11;
int pumpStopLamp = 12;
int pumpRunLamp = 13;
int alarmOut7 = 14; // spare
int alarmOut8 = 15; // spare
int mute = 18;
int test = 19;
int sounder = 17;
int external = 16;
int mutePushed = 0;
int alarm1Active = 0;
int alarm2Active = 0;
int alarm3Active = 0;
int alarm4Active = 0;
int alarm5Active = 0;
int alarm6Active = 0;
int alarm7Active = 0;
int alarm8Active = 0;
int alarm1Muted = 0;
int alarm2Muted = 0;
int alarm3Muted = 0;
int alarm4Muted = 0;
int alarm5Muted = 0;
int alarm6Muted = 0;
int alarm7Muted = 0;
int alarm8Muted = 0;

// the setup routine runs once when you press reset:

void setup() {

  pinMode(lowLevel, INPUT_PULLUP);
  pinMode(lowLevel, INPUT);
  pinMode(highLevel, INPUT_PULLUP);
  pinMode(highLevel, INPUT);
  pinMode(bundHigh, INPUT_PULLUP);
  pinMode(bundHigh, INPUT);
  pinMode(alarmIn4, INPUT_PULLUP);
  pinMode(alarmIn4, INPUT);
  pinMode(alarmIn5, INPUT_PULLUP);
  pinMode(alarmIn5, INPUT);
  pinMode(alarmIn6, INPUT_PULLUP);
  pinMode(alarmIn6, INPUT);
  pinMode(alarmIn7, INPUT_PULLUP);
  pinMode(alarmIn7, INPUT);
  pinMode(alarmIn8, INPUT_PULLUP);
  pinMode(alarmIn8, INPUT);

  pinMode(dayTankLowLamp, OUTPUT);
  pinMode(dayTankHighLamp, OUTPUT);
  pinMode(bundHighLamp, OUTPUT);
  pinMode(pumpControlRelay, OUTPUT);
  pinMode(pumpStopLamp, OUTPUT);
  pinMode(pumpRunLamp, OUTPUT);
  pinMode(alarmOut7, OUTPUT);
  pinMode(alarmOut8, OUTPUT);

  pinMode(mute, INPUT_PULLUP);
  pinMode(mute, INPUT);
  pinMode(test, INPUT_PULLUP);
  pinMode(test, INPUT);
  pinMode(sounder, OUTPUT);
  pinMode(external, OUTPUT);

  digitalWrite(lowLevel, on);
  digitalWrite(highLevel, off);
  digitalWrite(bundHigh, off);
  digitalWrite(alarmIn4, off);
  digitalWrite(alarmIn5, off);
  digitalWrite(alarmIn6, off);
  digitalWrite(alarmIn7, off);
  digitalWrite(alarmIn8, off);

  digitalWrite(dayTankLowLamp, off);
  digitalWrite(dayTankHighLamp, off);
  digitalWrite(bundHighLamp, off);
  digitalWrite(pumpControlRelay, off);
  digitalWrite(pumpStopLamp, off);
  digitalWrite(pumpRunLamp, off);
  digitalWrite(alarmOut7, off);
  digitalWrite(alarmOut8, off);

  digitalWrite(mute, off);
  digitalWrite(test, off);
  digitalWrite(sounder, off);
  digitalWrite(external, off);

  // Initial Test
  testOutputs();
}

//************************************************************

void loop() {




  //             ALARM 1 LOW LEVEL LAMP - NORMALLY CLOSED INPUT

  if (digitalRead(lowLevel) == on)  /////////////////////////////
  {
  //  alarm1Active = 1;
    digitalWrite(dayTankLowLamp, on);
 //   digitalWrite(external, on);
    pumpRun = true;
  }
  else
  {
    digitalWrite(dayTankLowLamp, off);
    alarm1Active = 0;
    alarm1Muted = 0;

  }

  //             ALARM 2  HIGH LEVEL LAMP - NORMALLY OPEN INPUT

  if (digitalRead(highLevel) == on)       // ALARM
  {
  //  alarm2Active = 1;
    digitalWrite(dayTankHighLamp, on);
   // digitalWrite(external, on);
    pumpRun = false;

  }
  else
  {
    digitalWrite(dayTankHighLamp, off);  // NORMAL
    alarm2Active = 0;
    alarm2Muted = 0;
  }

  //             ALARM 3  TANK BUND HIGH LEVEL - NORMALLY OPEN INPUT

  if (digitalRead(bundHigh) == on)    // ALARM
  {
    alarm3Active = 1;
    digitalWrite(bundHighLamp, on);
    digitalWrite(external, on);
  }
  else
  {
    digitalWrite(bundHighLamp, off);     // NORMAL
    alarm3Active = 0;
    alarm3Muted = 0;
  }


//*******************************************************************
  //             PUMP CONTROL 

switch (pumpRun) {

  case true:
  digitalWrite(pumpControlRelay, on);
  digitalWrite(pumpStopLamp, off);
  digitalWrite(pumpRunLamp, on);
    break;

  case false && digitalRead(lowLevel) == off :
  digitalWrite(pumpControlRelay, off);
  digitalWrite(pumpStopLamp, on);
  digitalWrite(pumpRunLamp, off);
    break;

}









//*******************************************************************



  //             ALARM 7 SPARE

  if (digitalRead(alarmIn7) == on)
  {
    alarm7Active = 1;
    digitalWrite(alarmOut7, on);
    digitalWrite(external, on);
  }
  else
  {
    digitalWrite(alarmOut7, off);
    alarm7Active = 0;
    alarm7Muted = 0;
  }

  //             ALARM 8 SPARE

  if (digitalRead(alarmIn8) == on)
  {
    alarm8Active = 1;
    digitalWrite(alarmOut8, on);
    digitalWrite(external, on);
  }
  else
  {
    digitalWrite(alarmOut8, off);
    alarm8Active = 0;
    alarm8Muted = 0;
  }

  //         TEST button pressed

  if (digitalRead(test) == on)
  {
    delay(2500); //wait 2.5 seconds
    if (digitalRead(test) == on)
    {
      delay(2000); //wait 2.5 seconds
      testOutputs();
    }
  }

  //           MUTE button pressed

  if (digitalRead(mute) == on)
  {
    mutePushed = true;
    digitalWrite(sounder, off);
    digitalWrite(mute, off);

    if (alarm1Active == 1) alarm1Muted = 1;
    if (alarm2Active == 1) alarm2Muted = 1;
    if (alarm3Active == 1) alarm3Muted = 1;
    if (alarm4Active == 1) alarm4Muted = 1;
    if (alarm5Active == 1) alarm5Muted = 1;
    if (alarm6Active == 1) alarm6Muted = 1;
    if (alarm7Active == 1) alarm7Muted = 1;
    if (alarm8Active == 1) alarm8Muted = 1;

  }
  else
  {
    mutePushed = 0;
  }


  // sounder and external control

  if (alarm1Active == 1 && alarm1Muted == 0) digitalWrite(sounder, on);
  if (alarm2Active == 1 && alarm2Muted == 0) digitalWrite(sounder, on);
  if (alarm3Active == 1 && alarm3Muted == 0) digitalWrite(sounder, on);
  if (alarm4Active == 1 && alarm4Muted == 0) digitalWrite(sounder, on);
  if (alarm5Active == 1 && alarm5Muted == 0) digitalWrite(sounder, on);
  if (alarm6Active == 1 && alarm6Muted == 0) digitalWrite(sounder, on);
  if (alarm7Active == 1 && alarm7Muted == 0) digitalWrite(sounder, on);
  if (alarm8Active == 1 && alarm8Muted == 0) digitalWrite(sounder, on);
  if (alarm1Active == 0 && alarm2Active == 0 && alarm3Active == 0 && alarm4Active == 0  && alarm5Active == 0 && alarm6Active == 0 && alarm7Active == 0 && alarm8Active == 0) {
    digitalWrite(sounder, off);
    digitalWrite(external, off);
  }

}

//         TEST button pressed

void testOutputs() {
  digitalWrite(sounder, on);
  digitalWrite(external, on);
  digitalWrite(dayTankLowLamp, on);
  delay(500);
  digitalWrite(dayTankLowLamp, off);
  digitalWrite(dayTankHighLamp, on);
  delay(500);
  digitalWrite(dayTankHighLamp, off);
  digitalWrite(bundHighLamp, on);
  delay(500);
  digitalWrite(bundHighLamp, off);
  //digitalWrite(pumpControlRelay, on);
  //delay(500);
  //digitalWrite(pumpControlRelay, off);
  digitalWrite(pumpStopLamp, on);
  delay(500);
  digitalWrite(pumpStopLamp, off);
  digitalWrite(pumpRunLamp, on);
  delay(500);
  digitalWrite(pumpRunLamp, off);
  digitalWrite(alarmOut7, on);
  delay(500);
  digitalWrite(alarmOut7, off);
  digitalWrite(alarmOut8, on);
  delay(500);
  digitalWrite(alarmOut8, off);
  digitalWrite(sounder, off);
  digitalWrite(external, off);
}


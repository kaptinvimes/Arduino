

// 29/04/2015
// Saved by Simulator for Arduino V0.98
// 4 Way Alarm Unit -  4 way relayboard HIGH TO ACTIVATE
// Output relay and lamp per channel/10min external sounder reactivation after mute pushed.

// Set Vars

//*********** mute timer *******************
long interval = 60000 * 10; // 10 minutes
long previousMillis = 0;

int muteTimerActive = false;
//*********** mute timer *******************

int alarmIn1 = 0;
int alarmIn2 = 1;
int alarmIn3 = 2;
int alarmIn4 = 3;
int alarmOut1 = 9;
int alarmOut2 = 8;
int alarmOut3 = 10;
int alarmOut4 = 11;
int alarmOut5 = 12;
int alarmOut6 = 13;
int alarmOut7 = 14;
int alarmOut8 = 15;
int mute = 18;
int test = 19;
int sounder = 16;
int external = 17;
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
int active = LOW;
int inactive = HIGH;

extern volatile unsigned long timer0_millis;   // millis reset


void setup() {
  // initialize digital pins.

  pinMode(alarmIn1, INPUT_PULLUP);
  pinMode(alarmIn1, INPUT);
  pinMode(alarmIn2, INPUT_PULLUP);
  pinMode(alarmIn2, INPUT);
  pinMode(alarmIn3, INPUT_PULLUP);
  pinMode(alarmIn3, INPUT);
  pinMode(alarmIn4, INPUT_PULLUP);
  pinMode(alarmIn4, INPUT);


  pinMode(alarmOut1, OUTPUT);
  pinMode(alarmOut2, OUTPUT);
  pinMode(alarmOut3, OUTPUT);
  pinMode(alarmOut4, OUTPUT);
  pinMode(alarmOut5, OUTPUT);
  pinMode(alarmOut6, OUTPUT);
  pinMode(alarmOut7, OUTPUT);
  pinMode(alarmOut8, OUTPUT);

  pinMode(mute, INPUT_PULLUP);
  pinMode(mute, INPUT);
  pinMode(test, INPUT_PULLUP);
  pinMode(test, INPUT);
  pinMode(sounder, OUTPUT);
  pinMode(external, OUTPUT);

  digitalWrite(alarmIn1, inactive);
  digitalWrite(alarmIn2, inactive);
  digitalWrite(alarmIn3, inactive);
  digitalWrite(alarmIn4, inactive);
  digitalWrite(alarmOut1, HIGH);
  digitalWrite(alarmOut2, HIGH);
  digitalWrite(alarmOut3, HIGH);
  digitalWrite(alarmOut4, HIGH);
  digitalWrite(alarmOut5, HIGH);
  digitalWrite(alarmOut6, HIGH);
  digitalWrite(alarmOut7, HIGH);
  digitalWrite(alarmOut8, HIGH);

  digitalWrite(mute, inactive);
  digitalWrite(test, inactive);
  digitalWrite(sounder, inactive);
  digitalWrite(external, inactive);

  //   Serial.begin(9600);


  // Initial Test
 // testOutputs();
}


void loop() {
  //Serial.println(timer0);
  unsigned long currentMillis = millis();

  // check for initial active alarms

  //             ALARM 1

  if (digitalRead(alarmIn1) == active)
  {
    alarm1Active = 1;
    digitalWrite(alarmOut1, active);
    digitalWrite(alarmOut2, active);
    digitalWrite(external, active);
  }
  else
  {
    digitalWrite(alarmOut1, inactive);
    digitalWrite(alarmOut2, inactive);
    alarm1Active = 0;
    alarm1Muted = 0;

  }

  //             ALARM 2

  if (digitalRead(alarmIn2) == active)
  {
    alarm2Active = 1;
    digitalWrite(alarmOut3, active);
    digitalWrite(alarmOut4, active);
    digitalWrite(external, active);
  }
  else
  {
    digitalWrite(alarmOut3, inactive);
    digitalWrite(alarmOut4, inactive);
    alarm2Active = 0;
    alarm2Muted = 0;
  }

  //             ALARM 3

  if (digitalRead(alarmIn3) == active)
  {
    alarm3Active = 1;
    digitalWrite(alarmOut5, active);
    digitalWrite(alarmOut6, active);
    digitalWrite(external, active);
  }
  else
  {
    digitalWrite(alarmOut5, inactive);
    digitalWrite(alarmOut6, inactive);
    alarm3Active = 0;
    alarm3Muted = 0;
  }

  //             ALARM 4

  if (digitalRead(alarmIn4) == active)
  {
    alarm4Active = 1;
    digitalWrite(alarmOut7, active);
    digitalWrite(alarmOut8, active);
    digitalWrite(external, active);
  }
  else
  {
    digitalWrite(alarmOut7, inactive);
    digitalWrite(alarmOut8, inactive);
    alarm4Active = 0;
    alarm4Muted = 0;
  }



  //         TEST button pressed

  if (digitalRead(test) == active)
  {
    testOutputs();
  }


  //           MUTE button pressed

  if (digitalRead(mute) == active)
  {
    mutePushed = true;

    // ********** timer *************
    muteTimerActive = true;
    previousMillis = currentMillis;
    // ********** timer *************

    digitalWrite(sounder, inactive);
    digitalWrite(mute, inactive);


    if (alarm1Active == 1) alarm1Muted = 1;
    if (alarm2Active == 1) alarm2Muted = 1;
    if (alarm3Active == 1) alarm3Muted = 1;
    if (alarm4Active == 1) alarm4Muted = 1;

  }
  else
  {
    mutePushed = 0;
  }

  // ********** timer *************
  currentMillis = millis();
  if (((currentMillis - previousMillis) > interval) && muteTimerActive == true)
  {
    if (alarm1Active == 1 ) digitalWrite(sounder, active);
    if (alarm2Active == 1 ) digitalWrite(sounder, active);
    if (alarm3Active == 1 ) digitalWrite(sounder, active);
    if (alarm4Active == 1 ) digitalWrite(sounder, active);
    //   previousMillis = currentMillis;
  }

  // ********** timer *************
  // sounder and external control

  if (alarm1Active == 1 && alarm1Muted == 0) digitalWrite(sounder, active);
  if (alarm2Active == 1 && alarm2Muted == 0) digitalWrite(sounder, active);
  if (alarm3Active == 1 && alarm3Muted == 0) digitalWrite(sounder, active);
  if (alarm4Active == 1 && alarm4Muted == 0) digitalWrite(sounder, active);

  if (alarm1Active == 0 && alarm2Active == 0 && alarm3Active == 0 && alarm4Active == 0)
  {
    digitalWrite(sounder, inactive);
    digitalWrite(external, inactive);
    muteTimerActive = false;
  }

  if (millis() > 3024000000)  // reset after 35 days
  {
    noInterrupts ();
    timer0_millis = 0;
    interrupts ();
    previousMillis = 0;

    digitalWrite(alarmOut6, active);
    delay(1000);
    digitalWrite(alarmOut6, inactive);
    digitalWrite(alarmOut4, active);
    delay(1000);
    digitalWrite(alarmOut4, inactive);
    digitalWrite(alarmOut2, active);
    delay(1000);
    digitalWrite(alarmOut2, inactive);

  }
}
//         TEST button pressed

void testOutputs() {
  digitalWrite(sounder, active);
  digitalWrite(alarmOut1, active);
  delay(500);
  digitalWrite(alarmOut1, inactive);
  digitalWrite(alarmOut2, active);
  delay(500);
  digitalWrite(alarmOut2, inactive);
  digitalWrite(alarmOut3, active);
  delay(500);
  digitalWrite(alarmOut3, inactive);
  digitalWrite(alarmOut4, active);
  delay(500);
  digitalWrite(alarmOut4, inactive);
  digitalWrite(alarmOut5, active);
  delay(500);
  digitalWrite(alarmOut5, inactive);
  digitalWrite(alarmOut6, active);
  delay(500);
  digitalWrite(alarmOut6, inactive);
  digitalWrite(alarmOut7, active);
  delay(500);
  digitalWrite(alarmOut7, inactive);
  digitalWrite(alarmOut8, active);
  delay(500);
  digitalWrite(alarmOut8, inactive);
  digitalWrite(sounder, inactive);
}


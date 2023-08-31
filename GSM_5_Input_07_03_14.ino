
// 07/03/2014
// Saved by Simulator for Arduino V0.98
// 5 Way Alarm Unit -  5 way relayboard HIGH TO ACTIVATE
// Binary Input - 3 in/5 out

// Set Vars


int alarmIn1=0;
int alarmIn2=1;
int alarmIn3=2;
int alarmIn4=3;
int alarmIn5=4;
int alarmOut1=9;
int alarmOut2=8;
int alarmOut3=10;
int alarmOut4=11;
int alarmOut5=12;
int mute=18;
int test=19;
int sounder=17;
int external=16;
int mutePushed=0;
int alarm1Active=0;
int alarm2Active=0;
int alarm3Active=0;
int alarm4Active=0;
int alarm5Active=0;
int alarm1Muted=0;
int alarm2Muted=0;
int alarm3Muted=0;
int alarm4Muted=0;
int alarm5Muted=0;
int readInput1;
int readInput2;
int readInput3;
int readInput4;
int inputValue=0;
int anyAlarmActive=0;
int active=LOW;
int inactive=HIGH;

// the setup routine runs once when you press reset:

void setup() {                
  // initialize digital pins.

  pinMode(alarmIn1,INPUT_PULLUP); 
  pinMode(alarmIn1,INPUT); 
  pinMode(alarmIn2,INPUT_PULLUP); 
  pinMode(alarmIn2,INPUT);
  pinMode(alarmIn3,INPUT_PULLUP);  
  pinMode(alarmIn3,INPUT);
  pinMode(alarmIn4,INPUT_PULLUP);  
  pinMode(alarmIn4,INPUT); 
  pinMode(alarmIn5,INPUT_PULLUP);  
  pinMode(alarmIn5,INPUT);    
  pinMode(alarmOut1,OUTPUT); 
  pinMode(alarmOut2,OUTPUT); 
  pinMode(alarmOut3,OUTPUT); 
  pinMode(alarmOut4,OUTPUT); 
  pinMode(alarmOut5,OUTPUT); 
  pinMode(mute,INPUT_PULLUP); 
  pinMode(mute,INPUT); 
  pinMode(test,INPUT_PULLUP); 
  pinMode(test,INPUT);
  pinMode(sounder,OUTPUT); 
  pinMode(external,OUTPUT);
  digitalWrite(alarmIn1,inactive);
  digitalWrite(alarmIn2,inactive); 
  digitalWrite(alarmIn3,inactive);
  digitalWrite(alarmIn4,inactive);
  digitalWrite(alarmOut1,HIGH);
  digitalWrite(alarmOut2,HIGH); 
  digitalWrite(alarmOut3,HIGH);
  digitalWrite(alarmOut4,HIGH);
  digitalWrite(alarmOut5,HIGH);
  digitalWrite(mute,inactive); 
  digitalWrite(test,inactive);
  digitalWrite(sounder,inactive);
  digitalWrite(external,inactive); 

  // Initial test
  testOutputs();
}

//**********************************************************


// the loop routine runs over and over again forever:

void loop() {

  //*************************************************************************

  do {  


    // Check for active alarms

    readInput1=0;
    readInput2=0;
    readInput3=0;
    readInput4=0;
    inputValue=0;

    readInput4=digitalRead(alarmIn4);
    readInput3=digitalRead(alarmIn3);
    readInput2=digitalRead(alarmIn2);
    readInput1=digitalRead(alarmIn1);


    if (readInput1==1 && readInput2==1 && readInput3==1 && readInput4==1) inputValue=0;
    if (readInput1==0 && readInput2==1 && readInput3==1 && readInput4==1) inputValue=1;
    if (readInput1==1 && readInput2==0 && readInput3==1 && readInput4==1) inputValue=2;
    if (readInput1==1 && readInput2==1 && readInput3==0 && readInput4==1) inputValue=3;  
    if (readInput1==1 && readInput2==1 && readInput3==1 && readInput4==0) inputValue=4;
    if (readInput1==0 && readInput2==1 && readInput3==1 && readInput4==0) inputValue=5;


    switch (inputValue)
    {
    case 1:
      alarm1Active=1;
      anyAlarmActive=1;
      digitalWrite(alarmOut1,active);
      digitalWrite(external,active);
      digitalWrite(sounder,active);
      delay(7000);
      break;

    case 2:
      alarm2Active=1;
      anyAlarmActive=1;
      digitalWrite(alarmOut2,active);
      digitalWrite(external,active);
      digitalWrite(sounder,active);
      delay(7000);
      break;

    case 3:
      alarm3Active=1;
      anyAlarmActive=1;
      digitalWrite(alarmOut3,active);
      digitalWrite(external,active);
      digitalWrite(sounder,active);
      delay(7000);
      break;

    case 4:
      alarm4Active=1;
      anyAlarmActive=1;
      digitalWrite(alarmOut4,active);
      digitalWrite(external,active);
      digitalWrite(sounder,active);
      delay(7000);
      break;

    case 5:
      alarm5Active=1;
      anyAlarmActive=1;
      digitalWrite(alarmOut5,active);
      digitalWrite(external,active);
      digitalWrite(sounder,active);      
      delay(7000);       
      break;

    default:
      alarm1Muted=0;
      alarm2Muted=0;
      alarm3Muted=0;
      alarm4Muted=0;
      alarm5Muted=0; 
    }



    //             Clear Output Alarms

    if (digitalRead(alarmIn5) == active)
    {    
      delay(10000);
      if (digitalRead(alarmIn5) == active) clearAllOutputs();
    }

    //  MUTE button pressed

    if (digitalRead(mute)==active)

    {    
      mutePushed=true; 
      digitalWrite(sounder,inactive);
      digitalWrite(mute,inactive);
      if (alarm1Active==1) alarm1Muted=1;
      if (alarm2Active==1) alarm2Muted=1;
      if (alarm3Active==1) alarm3Muted=1;
      if (alarm4Active==1) alarm4Muted=1;
      if (alarm5Active==1) alarm5Muted=1;
    }
    else
    {
      mutePushed=0;
    }


  } 
  while(anyAlarmActive||2) ;


  //**************************************************

  // Sounder and external control

  if (alarm1Active==1 && alarm1Muted==0) digitalWrite(sounder,active);
  if (alarm2Active==1 && alarm2Muted==0) digitalWrite(sounder,active);
  if (alarm3Active==1 && alarm3Muted==0) digitalWrite(sounder,active);
  if (alarm4Active==1 && alarm4Muted==0) digitalWrite(sounder,active);
  if (alarm5Active==1 && alarm5Muted==0) digitalWrite(sounder,active);

  if (alarm1Active==0 && alarm2Active==0 && alarm3Active==0 && alarm4Active==0 && alarm5Active==0) {
    digitalWrite(sounder,inactive);
    digitalWrite(external,inactive);
  }

  if (anyAlarmActive==1 )clearAllInputs();

}



//*****************************************************************************************************************************
// TEST

void testOutputs() {
  digitalWrite(sounder,active);
  digitalWrite(alarmOut1,active);
  delay(500);   
  digitalWrite(alarmOut1,inactive);    
  digitalWrite(alarmOut2,active);
  delay(500);   
  digitalWrite(alarmOut2,inactive);      
  digitalWrite(alarmOut3,active);
  delay(500);   
  digitalWrite(alarmOut3,inactive);  
  digitalWrite(alarmOut4,active);
  delay(500);   
  digitalWrite(alarmOut4,inactive);  
  digitalWrite(alarmOut5,active);
  delay(500);   
  digitalWrite(alarmOut5,inactive);    
  digitalWrite(test,inactive);
  digitalWrite(sounder,inactive);
}

// Clear all inputs

void clearAllInputs() {

  digitalWrite(alarmIn1,inactive);
  digitalWrite(alarmIn2,inactive); 
  digitalWrite(alarmIn3,inactive);
  digitalWrite(alarmIn4,inactive);
  anyAlarmActive=0;
}

// Clear all outputs

void clearAllOutputs() {

  digitalWrite(alarmOut1,HIGH);
  digitalWrite(alarmOut2,HIGH); 
  digitalWrite(alarmOut3,HIGH);
  digitalWrite(alarmOut4,HIGH);
  digitalWrite(alarmOut5,HIGH);
  digitalWrite(external,inactive);
  digitalWrite(sounder,inactive);
  digitalWrite(alarmIn4,inactive);
  alarm1Active=0;
  alarm2Active=0;
  alarm3Active=0;
  alarm4Active=0;
  alarm5Active=0;
  alarm1Muted=0;
  alarm2Muted=0;
  alarm3Muted=0;
  alarm4Muted=0;
  alarm5Muted=0;
  anyAlarmActive=0;
}









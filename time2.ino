
//  09/09/19
// Shutdown after Alarm - leaving Beacon only operating

//----------------------------------------------------------------------------------

#include <avr/sleep.h>
#include <avr/wdt.h>


//const long onTime = 180000; // (/1000)/60 = ca 3.00 minutes ON
//const int offTime = 450;  // x 8 = 1 hour OFF
//const int offTime = 900;  // x 8 = 2 hour OFF
//-------------------------watchdog interrupt---------------------------------------

//
ISR (WDT_vect)
{
  wdt_disable();  // disable watchdog
}  // end of WDT_vect

//-------------------------Pin Assign-----------------------------------------------

//in

int channelOne = 0;
int channelTwo = 1;
int channelThree = 2;
int timePeriod = 4;  // delay 3 minutes/60 minutes links adjacent to 328P


//out
int alarmOneSet = 8;			//9
int alarmOneReset = 9;			//8
int alarmTwoSet = 11;			//10
int alarmTwoReset = 10;			//11
int alarmThreeSet = 13;			//12
int alarmThreeReset = 12;		//13
int beaconSet = 15;				//14
int beaconReset = 14;			//15
int power = 16;


// opto-isolators invert i/o

int active = LOW;
int inactive = HIGH;
int set = HIGH;
int reset = HIGH;
long sleepTime = 0;

//----------------------------------------------------------------------------------

void setup () {

  // input

  pinMode(channelOne, INPUT);
  pinMode(channelTwo, INPUT);
  pinMode(channelThree, INPUT);
  pinMode(timePeriod, INPUT_PULLUP);

  // output

  pinMode(alarmOneSet, OUTPUT);
  pinMode(alarmOneReset, OUTPUT);
  pinMode(alarmTwoSet, OUTPUT);
  pinMode(alarmTwoReset, OUTPUT);
  pinMode(alarmThreeSet, OUTPUT);
  pinMode(alarmThreeReset, OUTPUT);
  pinMode(beaconSet, OUTPUT);
  pinMode(beaconReset, OUTPUT);
  pinMode(power, OUTPUT);



  // Reset all Relays to Normal Condition (All Off)


  resetAllRelays();
  delay(5000); // Settle

  if (digitalRead(timePeriod) == LOW) sleepTime = 8;
  if (digitalRead(timePeriod) == HIGH) sleepTime = 900; // 2 hours



}
//**********************************BEGIN********************************************

void loop ()
{

  Awake ();

  for (long i = 0; i <= sleepTime; i++)  Sleep();	        // wdt wakes every 8 seconds so 450*8=3600/60 minutes = 1 hour  or 20 ca = 3minutes

}

//**********************************END*********************************************

//------------------------Awake Period-----------------------------------------------


void Awake()
{
  digitalWrite(power, active); // turn on OSA/SET/Other

  delay(120000); // Wait 2 minutes then check for any alarms   2 minutes = 120000



  //            Channel One

  if (digitalRead(channelOne) == active)
  {
    alarmOneActive();
    beaconActive();
  }

  /*  //          Channel Two

    if (digitalRead(channelTwo) == active)
    {
  	  alarmTwoActive();
  	  beaconActive();
    }

    //            Channel Three

    if (digitalRead(channelThree) == active)
    {
  	  alarmThreeActive();
  	  beaconActive();
    }
  */

  digitalWrite(power, inactive); // turn off OSA/SET/Other - Go back to sleep
  sleepTime = 1875000;
}



//------------------------Sleep Period----------------------------------------------

void Sleep()
{

  // disable ADC
  ADCSRA = 0;

  // clear various "reset" flags
  MCUSR = 0;
  // allow changes, disable reset
  WDTCSR = bit (WDCE) | bit (WDE);
  // set interrupt mode and an interval
  WDTCSR = bit (WDIE) | bit (WDP3) | bit (WDP0);    // set WDIE, and 8 seconds delay
  wdt_reset();  // pat the dog

  set_sleep_mode (SLEEP_MODE_PWR_DOWN);
  noInterrupts ();           // timed sequence follows
  sleep_enable();

  // turn off brown-out enable in software
  MCUCR = bit (BODS) | bit (BODSE);
  MCUCR = bit (BODS);

  interrupts ();             // guarantees next instruction executed
  sleep_cpu ();

  // After Wakeup Cancel Sleep as a precaution
  sleep_disable();

}

//---------------------Reset all Latch Relays -------------------------------------


void resetAllRelays()
{
  digitalWrite (alarmOneSet, LOW);  // on			    Latch Relay 1
  delay(100) ;
  digitalWrite (alarmOneSet, HIGH); // off

  digitalWrite (alarmOneReset, LOW);  // on
  delay(100) ;
  digitalWrite (alarmOneReset, HIGH); // off
  delay(100) ;


  digitalWrite (alarmTwoSet, LOW);  // on         Latch Relay 2
  delay(100) ;
  digitalWrite (alarmTwoSet, HIGH); // off

  digitalWrite (alarmTwoReset, LOW);  // on
  delay(100) ;
  digitalWrite (alarmTwoReset, HIGH); // off


  digitalWrite (alarmThreeSet, LOW);  // on       Latch Relay 3
  delay(100) ;
  digitalWrite (alarmThreeSet, HIGH); // off

  digitalWrite (alarmThreeReset, LOW);  // on
  delay(100) ;
  digitalWrite (alarmThreeReset, HIGH); // off


  digitalWrite (beaconSet, LOW);  // on			      Latch Relays 4 & 5
  delay(100) ;
  digitalWrite (beaconSet, HIGH); // off

  digitalWrite (beaconReset, LOW);  // on
  delay(100) ;
  digitalWrite (beaconReset, HIGH); // off

  delay(100) ;
  digitalWrite(power, inactive);

}




//------------------------Alarm One Enable-------------------------------------------

void alarmOneActive()
{
  digitalWrite (alarmOneSet, LOW);  // on
  delay(1000);
  digitalWrite (alarmOneSet, HIGH);  //off      Set Latch Relay 1
}

//------------------------Alarm Two Enable-------------------------------------------

void alarmTwoActive()
{
  digitalWrite (alarmTwoSet, LOW);  // on
  delay(1000);
  digitalWrite (alarmTwoSet, HIGH);  //off      Set Latch Relay 2
}

//------------------------Alarm Three Enable-----------------------------------------

void alarmThreeActive()
{
  digitalWrite (alarmThreeSet, LOW);  // on
  delay(1000);
  digitalWrite (alarmThreeSet, HIGH);  //off    Set Latch Relay 3
}

//------------------------Beacon/Global Enable----------------------------------------

void beaconActive()
{
  digitalWrite (beaconSet, LOW);  // on
  delay(1000);
  digitalWrite (beaconSet, HIGH);  //off      Set Latch Relays 4 & 5
}


#include <GSM.h>

// initialize the library instance
GSM gsmAccess; // include a 'true' parameter for debug enabled
GSM_SMS sms;

char mob1[12] = "07411036793";
char mob2[12] = "07411036793";
char mob3[12] = "07411036793";
char mob4[12] = "07411036793";
char mob5[12] = "07411036793";
char mob6[12] = "07411036793";
char mob7[12] = "07411036793";
char mob8[12] = "07411036793";
char mob10[12] = "07411036793";
char mob11[12] = "07411036793";
char mob12[12] = "07411036793";
char mob13[12] = "07411036793";
char mob14[12] = "07411036793";
char mob15[12] = "07411036793";
char mob16[12] = "07411036793";
String msg1 = "Alarm ";
String msg2 = " Active ";


int msgSent[17] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int msgCount = 2;
int a1 = 0;
int a2 = 1;
int a3 = 4;
int a4 = 5;
int a5 = 6;
int a6 = 8;
int a7 = 9;
int a8 = 10;
int a9 = 11;
int a10 = 12;
int a11 = 13;
int a12 = 14;
int a13 = 15;
int a14 = 16;
int a15 = 17;
int a16 = 18;
int active = LOW;
int inactive = HIGH;

void setup()
{
  pinMode(a1, INPUT);
  pinMode(a2, INPUT);
  pinMode(a3, INPUT);
  pinMode(a4, INPUT);
  pinMode(a5, INPUT);
  pinMode(a6, INPUT);
  pinMode(a7, INPUT);
  pinMode(a8, INPUT);
  pinMode(a9, INPUT);
  pinMode(a10, INPUT);
  pinMode(a11, INPUT);
  pinMode(a12, INPUT);
  pinMode(a13, INPUT);
  pinMode(a14, INPUT);
  pinMode(a15, INPUT);
  pinMode(a16, INPUT);

  Serial.begin(9600);
  Serial.println("Init");
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);
  delay(12000);
  digitalWrite(7, LOW);
  delay(1000);

  // connection state
  boolean notConnected = true;

  // Start GSM shield
  // If your SIM has PIN, pass it as a parameter of begin() in quotes
  while (notConnected)
  {
    if (gsmAccess.begin() == GSM_READY)
    {
      notConnected = false;
    }
    else
    {
      Serial.println("Not connected");
      delay(1000);
    }
  }
  delay (1000);

  sms.beginSMS(mob1);
  sms.print("GSM Active");
  sms.endSMS();
  delay (1000);
}
//*********************************************

void loop()
{
  if (digitalRead(a1) == active && msgSent[1] < msgCount) {sendMessage(1);}
  if (digitalRead(a2) == active && msgSent[2] < msgCount) {sendMessage(2);}
  if (digitalRead(a3) == active && msgSent[3] < msgCount) {sendMessage(3);}
  if (digitalRead(a4) == active && msgSent[4] < msgCount) {sendMessage(4);}
  if (digitalRead(a5) == active && msgSent[5] < msgCount) {sendMessage(5);}
  if (digitalRead(a6) == active && msgSent[6] < msgCount) {sendMessage(6);}
  if (digitalRead(a7) == active && msgSent[7] < msgCount) {sendMessage(7);}
  if (digitalRead(a8) == active && msgSent[8] < msgCount) {sendMessage(8);}
  if (digitalRead(a9) == active && msgSent[9] < msgCount) {sendMessage(9);}
  if (digitalRead(a10) == active && msgSent[10] < msgCount) {sendMessage(10);}
  if (digitalRead(a11) == active && msgSent[11] < msgCount) {sendMessage(11);}
  if (digitalRead(a12) == active && msgSent[12] < msgCount) {sendMessage(12);}
  if (digitalRead(a13) == active && msgSent[13] < msgCount) {sendMessage(13);}
  if (digitalRead(a14) == active && msgSent[14] < msgCount) {sendMessage(14);}
  if (digitalRead(a15) == active && msgSent[15] < msgCount) {sendMessage(15);}
  if (digitalRead(a16) == active && msgSent[16] < msgCount) {sendMessage(16);}
}

void sendMessage(int aN) 
{
    sms.beginSMS(mob1);
    sms.print(msg1 + aN + msg2);
    sms.endSMS();
    msgSent[aN]++;
}

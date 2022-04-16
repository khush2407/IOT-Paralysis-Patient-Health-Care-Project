#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
int fire=10;
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
SoftwareSerial mySerial(11,12);
const int voltageSensor = A2;
int Short = A1;
int Break = A0;

 float vOUT = 0.0;
float vIN = 0.0;
float R1 = 30000.0;
float R2 = 7500.0;
int value = 0;


void setup()
{
  Serial.begin(9600);
   lcd.begin(16, 2);
   pinMode(fire,INPUT);
   pinMode(Short,INPUT);
   pinMode(Break,INPUT);
   pinMode(A5,OUTPUT);
  // Print a message to the LCD.
  lcd.print("  Transmisson");
  lcd.setCursor(0,1);
  lcd.print("Line Fault Det.");
  delay(2000);
  lcd.clear();
    lcd.print("Made By eBhoot");
  lcd.setCursor(0,1);
  lcd.print("  ELectronics");
  delay(2000);
  
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  delay(3000);
  start1();
  
}


void loop()
{
  lcd.clear();
  int c = digitalRead(fire);
  int d = analogRead(Short);
  int e = analogRead(Break);
  Serial.print("Short");
  Serial.println(d);
  Serial.print("Break");
  Serial.println(e);
  value = analogRead(voltageSensor);
  vOUT = (value * 5.0) / 1024.0;
  vIN = vOUT / (R2/(R1+R2));
   digitalWrite(A5,LOW);
  //Serial.print("Input Vol= ");
  //Serial.println(vIN);
  lcd.setCursor(0,0);
  lcd.print("Input Vol=         ");
  lcd.setCursor(12,0);
  lcd.print(vIN);
  delay(100);
    if(c==LOW)
    {
      digitalWrite(A5,HIGH);
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print("Fire Detect");
      fire1();
      delay(1000);
      
      }
    if(d>600)
    {
      digitalWrite(A5,HIGH);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Short Circuit");
      lcd.setCursor(0,1);
      lcd.print("Detected");
      SendMessage();
      
      }
    if(e<600)
    {
      lcd.clear();
      digitalWrite(A5,HIGH);
      lcd.setCursor(0,0);
      lcd.print("Supply LIne is");
      lcd.setCursor(0,1);
      lcd.print("Breaked");
      breaked();
      
      }  

       if(vIN>8)
    {
      lcd.clear();
      digitalWrite(A5,HIGH);
      lcd.setCursor(0,0);
      lcd.print("Over Votage ");
      lcd.setCursor(0,1);
      lcd.print("Detected");
      overvotage();
      
      }  
  
  
      
      
  
 
}


 void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+919265130755\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("Short Circuit Detected  at Location XYZ");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
 void start1()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+919265130755\"\r"); // Replace x with mobile number 919725113007
  delay(1000);
  mySerial.println("Transmisson Line Fault Detection System Started");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
 void breaked()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+919265130755\"\r"); // Replace x with mobile number 919725113007
  delay(1000);
  mySerial.println("Line Breaked System Started");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
 void fire1()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+919265130755\"\r"); // Replace x with mobile number 919725113007
  delay(1000);
  mySerial.println("Fire Aleart Detected");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
void overvotage()
{

   mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+919265130755\"\r"); // Replace x with mobile number 919725113007
  delay(1000);
  mySerial.println("Over VOltage Deteced");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  
  }

  

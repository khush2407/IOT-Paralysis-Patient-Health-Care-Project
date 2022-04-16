#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>j k

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial mySerial(D5,D6);

#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "66Qy5_E94901_kt_0guOdwrFJjFxZ1g5";

#define FIREBASE_HOST "iot-par-default-rtdb.firebaseio.com"                         // the project name address from firebase id
#define FIREBASE_AUTH "xlL6nRysQTe3riQa8rFb1i68vTNccWN0vv0ld2Su"   
FirebaseData fbdo;                                                                        // the secret key generated from firebase

char ssid[] = "sherwin";           //WIFI Name
char pass[] = "12345678";           //WIFI Password


void setup()
{
    Serial.begin(9600);

    Blynk.begin(auth, ssid, pass);
  // Connect to WiFi
  pinMode(D3,OUTPUT);
  digitalWrite(D3,LOW);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) 
  {
     delay(500);
     Serial.print("*");
  }
  lcd.begin();

  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Smart Devie For");
  lcd.setCursor(0,1);
  lcd.print("Paralysis Patient");
  delay(2000);
  Serial.println("");
  Serial.println("WiFi connection Successful");
  Serial.print("The IP Address of ESP8266 Module is: ");
  Serial.print(WiFi.localIP());// Print the IP address

    Serial.begin(9600);
     mySerial.begin(9600);   // Setting the baud rate of GSM Module  
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);   
}

int st=0;
void loop()
{
   if (Firebase.getInt(fbdo, "/Status")) {
   if  (fbdo.dataType() == "int") {
      int val = fbdo.intData();
      if (val != st) {
        st = val;
        
      }
    }
  } 
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Smart Devie For");
  lcd.setCursor(0,1);
  lcd.print("Paralysis Patient");  
  
   if(st==0)
   {

  lcd.clear();
   lcd.setCursor(0,0);
  lcd.print("Smart Devie For");
  lcd.setCursor(0,1);
  lcd.print("Paralysis Patient");
    Blynk.virtualWrite(V1,st); 
    st0();
    
    }
    else if(st==1)
   {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("I want to");
  lcd.setCursor(0,1);
  lcd.print(" Drink Water   "); 
   Blynk.virtualWrite(V1,st); 
   st1();
   
    }
    else if(st==2)
   {
   lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("I want to Go");
  lcd.setCursor(0,1);
  lcd.print("  Washroom");  
   Blynk.virtualWrite(V1,st); 
   st2();
    }
    else if(st==3)
   {

    lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("There is A ");
  lcd.setCursor(0,1);
  lcd.print("Problem in My Back");
   Blynk.virtualWrite(V1,st); 
   st3();

     
 
    }
    else if(st==4)
   {

    lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Hello I ");
  lcd.setCursor(0,1);
  lcd.print("Want Food");  
   Blynk.virtualWrite(V1,st); 
   st4();
 
    }
    else if(st==5)
   {
    
    lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("I got  ");
  lcd.setCursor(0,1);
  lcd.print("injured");  
   Blynk.virtualWrite(V1,st); 
   st5();
 
    
    }
//   else if(st==5)
//   {
//    
//    }
    

}





void st0()
 {
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+919016649359\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("Short Circuit Detected  at Location XYZ");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
 void st1()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+919016649359\"\r"); // Replace x with mobile number 919725113007
  delay(1000);
  mySerial.println("Transmisson Line Fault Detection System Started");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
 void st2()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
   mySerial.println("AT+CMGS=\"+919016649359\"\r"); // Replace x with mobile number 919725113007
  delay(1000);
  mySerial.println("Line Breaked System Started");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
 void st3()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+919016649359\"\r"); // Replace x with mobile number 919725113007
  delay(1000);
  mySerial.println("Fire Aleart Detected");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
void st4()
{

   mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
   mySerial.println("AT+CMGS=\"+919016649359\"\r"); // Replace x with mobile number 919725113007
  delay(1000);
  mySerial.println("Over VOltage Deteced");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  
  }
void st5()
{

   mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"++919016649359\"\r"); // Replace x with mobile number 919725113007
  delay(1000);
  mySerial.println("Over VOltage Deteced");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  
  }
  

  

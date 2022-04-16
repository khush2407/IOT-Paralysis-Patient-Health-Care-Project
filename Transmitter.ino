#include <common.h>
#include <FirebaseESP8266.h>
#include <FirebaseFS.h>
#include <Utils.h>

#include <Wire.h>

// MPU6050 Slave Device Address
const uint8_t MPU6050SlaveAddress = 0x68;

// Select SDA and SCL pins for I2C communication 
const uint8_t scl = D2;
const uint8_t sda = D3;
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>



#define FIREBASE_HOST "iot-par-default-rtdb.firebaseio.com"                         // the project name address from firebase id
#define FIREBASE_AUTH "xlL6nRysQTe3riQa8rFb1i68vTNccWN0vv0ld2Su"   
FirebaseData fbdo;                                                                        // the secret key generated from firebase

char ssid[] = "sherwin";           //WIFI Name
char pass[] = "12345678";           //WIFI Password

// sensitivity scale factor respective to full scale setting provided in datasheet 
const uint16_t AccelScaleFactor = 16384;
const uint16_t GyroScaleFactor = 131;

// MPU6050 few configuration register addresses
const uint8_t MPU6050_REGISTER_SMPLRT_DIV   =  0x19;
const uint8_t MPU6050_REGISTER_USER_CTRL    =  0x6A;
const uint8_t MPU6050_REGISTER_PWR_MGMT_1   =  0x6B;
const uint8_t MPU6050_REGISTER_PWR_MGMT_2   =  0x6C;
const uint8_t MPU6050_REGISTER_CONFIG       =  0x1A;
const uint8_t MPU6050_REGISTER_GYRO_CONFIG  =  0x1B;
const uint8_t MPU6050_REGISTER_ACCEL_CONFIG =  0x1C;
const uint8_t MPU6050_REGISTER_FIFO_EN      =  0x23;
const uint8_t MPU6050_REGISTER_INT_ENABLE   =  0x38;
const uint8_t MPU6050_REGISTER_ACCEL_XOUT_H =  0x3B;
const uint8_t MPU6050_REGISTER_SIGNAL_PATH_RESET  = 0x68;

int16_t AccelX, AccelY, AccelZ, Temperature, GyroX, GyroY, GyroZ;

void setup() {
  Serial.begin(9600);
  Wire.begin(sda, scl);
  MPU6050_Init();

   WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) 
  {
     delay(500);
     Serial.print("*");
  }
  
  Serial.println("");
  Serial.println("WiFi connection Successful");
  Serial.print("The IP Address of ESP8266 Module is: ");
  Serial.print(WiFi.localIP());// Print the IP address
  pinMode(D7,INPUT);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);  
}

void loop() {
  double Ax, Ay, Az, T, Gx, Gy, Gz;
  
  Read_RawValue(MPU6050SlaveAddress, MPU6050_REGISTER_ACCEL_XOUT_H);
  
  //divide each with their sensitivity scale factor
  Ax = (double)AccelX/AccelScaleFactor;
  Ay = (double)AccelY/AccelScaleFactor;
  Az = (double)AccelZ/AccelScaleFactor;
  T = (double)Temperature/340+36.53; //temperature formula
  Gx = (double)GyroX/GyroScaleFactor;
  Gy = (double)GyroY/GyroScaleFactor;
  Gz = (double)GyroZ/GyroScaleFactor;
//
 Serial.print("Ax: "); Serial.print(Ax*100);
  Serial.print(" Ay: "); Serial.print(Ay*100);
  Serial.print(" Az: "); Serial.print(Az*100);
//  Serial.print(" T: "); Serial.print(T);
 // Serial.print(" Gx: "); Serial.print(Gx);
 // Serial.print(" Gy: "); Serial.print(Gy);
 // Serial.print(" Gz: "); Serial.print(Gz);
  Serial.print(" Button");Serial.println(digitalRead(D7));
  delay(500);

  if(digitalRead(D7)==LOW) 
    {
      Firebase.setInt(fbdo, "/Status",5);  //0=stop
      
      }  
   else
   {   

  if(Ay*100 < 0 && Ay*100 > -10)
  {
    Serial.println("Mid");
     Firebase.setInt(fbdo, "/Status",0);  //0=stop
    
    }
    if(Az*100 < -50 && Ay*100 > -70)
  {
    Serial.println("Right");
     Firebase.setInt(fbdo, "/Status",1);  //0=stop
    
    }
   if(Ay*100 < -50 && Ay*100 > -60)
  {
    Serial.println("Back");
     Firebase.setInt(fbdo, "/Status",2);  //0=stop
    
    }
    if(Az*100 < 50 && Az*100 > 35)
  {
    Serial.println("left");
     Firebase.setInt(fbdo, "/Status",3);  //0=stop
    
    }
    if(Ay*100 <80&& Ay*100 >65)
  {
    Serial.println("For");
    Firebase.setInt(fbdo, "/Status",4);  //0=stop
    
    }

   }
  
      
}

void I2C_Write(uint8_t deviceAddress, uint8_t regAddress, uint8_t data){
  Wire.beginTransmission(deviceAddress);
  Wire.write(regAddress);
  Wire.write(data);
  Wire.endTransmission();
}

// read all 14 register
void Read_RawValue(uint8_t deviceAddress, uint8_t regAddress){
  Wire.beginTransmission(deviceAddress);
  Wire.write(regAddress);
  Wire.endTransmission();
  Wire.requestFrom(deviceAddress, (uint8_t)14);
  AccelX = (((int16_t)Wire.read()<<8) | Wire.read());
  AccelY = (((int16_t)Wire.read()<<8) | Wire.read());
  AccelZ = (((int16_t)Wire.read()<<8) | Wire.read());
  Temperature = (((int16_t)Wire.read()<<8) | Wire.read());
  GyroX = (((int16_t)Wire.read()<<8) | Wire.read());
  GyroY = (((int16_t)Wire.read()<<8) | Wire.read());
  GyroZ = (((int16_t)Wire.read()<<8) | Wire.read());
}

//configure MPU6050
void MPU6050_Init(){
  delay(150);
  I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_SMPLRT_DIV, 0x07);
  I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_PWR_MGMT_1, 0x01);
  I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_PWR_MGMT_2, 0x00);
  I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_CONFIG, 0x00);
  I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_GYRO_CONFIG, 0x00);//set +/-250 degree/second full scale
  I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_ACCEL_CONFIG, 0x00);// set +/- 2g full scale
  I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_FIFO_EN, 0x00);
  I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_INT_ENABLE, 0x01);
  I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_SIGNAL_PATH_RESET, 0x00);
  I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_USER_CTRL, 0x00);
}

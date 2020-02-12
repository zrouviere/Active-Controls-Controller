#include "sd_card_RT.h"
#include "BMP388_RT.h"
#include "BME680_RT.h"
#include "GPS_RT.h"
#include "BNO055_RT.h"
#include "Triple.h"
#include <String.h>
void openFile();
void printAll();
File logger;




bool debug = TRUE;

void setup() {
  if (debug){
    Serial.begin(115200);
    initSD_debug();
    initBMP388_debug();
    initBME680_debug();
    initGPS_debug();
    initBNO055_debug();
  }
  else{
    initSD();
    initBMP388();
    initBME680();
    initGPS();
    initBNO055();
    
    }
    openFile();


  //TODO: Set init indicator to true
}

//Each sensor has prewritten functions to get the data ex. bme680_getTemperature stored in header files
//FOR GPS: you must call GPS.getDATA() (refer to GPS_print() function in GPS_RT.h)
//gps_update(); must be called in order to update GPS data

void loop() {
  gps_update();
  if (debug)
    printAll();
  
  
  delay(10000);
}

void openFile(){
  
  //If the file is new, we want to put the proper headers.
  bool isNewFile = false;
    String fileName = "logger.csv";
   if (!SD.exists(fileName)) {
     isNewFile = true;
  }

  logger = SD.open(fileName, FILE_WRITE);

  if(isNewFile){
    //TODO: Make and implement file format
   
    
  }
  
 
   if(!logger){
    Serial.println("File Unable to open!");
   }
}


void printAll(){
  Serial.println ("----------GPS DATA----------");
  gps_print();
  Serial.println ("----------BME680 DATA----------");
  Serial.println ("Pressure: " + String(bme680_getPressure()) +" hPa");
  Serial.println ("Altitude: " + String(bme680_getAltitude()) +" m");
  Serial.println ("Temperature: " + String(bme680_getTemperature()) +" C");
  Serial.println ("Humidity: " + String(bme680_getHumidity()) +"%");  
  Serial.println ("Gas: " + String(bme680_getGas()) +" Kohms");  

  Serial.println ("----------BMP388 DATA----------");
  Serial.println ("Pressure: " + String(bmp388_getPressure()) +" hPa");  
   Serial.println ("Altitude: " + String(bmp388_getAltitude()) +" m");
  Serial.println ("Temperature: " + String(bmp388_getTemperature()) +" C");

  Serial.println ("----------BNO055 DATA----------");
  Serial.println ("Acceleration: x: " + String(bno055_getAcceleration().x) + " y: " + String(bno055_getAcceleration().y)  + " z: " + String(bno055_getAcceleration().z)+ " m/s^2");
  Serial.println ("Orientation: x: " + String(bno055_getOrientation().x) + " y: " + String(bno055_getOrientation().y)  + " z: " + String(bno055_getOrientation().z)+ " degrees");
  Serial.println ("Gravity: x: " + String(bno055_getGravity().x) + " y: " + String(bno055_getGravity().y)  + " z: " + String(bno055_getGravity().z)+ " m/s^2");
  Serial.println ("Angular Velocity: x: " + String(bno055_getAngularVelocity().x) + " y: " + String(bno055_getAngularVelocity().y)  + " z: " + String(bno055_getAngularVelocity().z)+ " rad/s");
  Serial.println ("Linear Acceleration: x: " + String(bno055_getLinearAcceleration().x) + " y: " + String(bno055_getLinearAcceleration().y)  + " z: " + String(bno055_getLinearAcceleration().z)+ " m/s^2");
  Serial.println ("Magnetism: x: " + String(bno055_getMagnetism().x) + " y: " + String(bno055_getMagnetism().y)  + " z: " + String(bno055_getMagnetism().z)+ " uT");
 

  Serial.println ("----------END DATA----------");
  Serial.println ();
  
  
}

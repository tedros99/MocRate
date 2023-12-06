// E Paper Dependencies
#include <SPI.h>
#include "epd4in2.h"
#include "imagedata.h"
#include "epdpaint.h"
#include <SparkFun_Bio_Sensor_Hub_Library.h>
#include <Wire.h>

#define COLORED     0
#define UNCOLORED   1

// Bio Sensor Initialization
int resPin = 4;
int mfioPin = 13;

SparkFun_Bio_Sensor_Hub bioHub(resPin, mfioPin); 

bioData body;  
// ^^^^^^^^^
// What's this!? This is a type (like int, byte, long) unique to the SparkFun
// Pulse Oximeter and Heart Rate Monitor. Unlike those other types it holds
// specific information on your heartrate and blood oxygen levels. BioData is
// actually a specific kind of type, known as a "struct". 
// You can choose another variable name other than "body", like "blood", or
// "readings", but I chose "body". Using this "body" varible in the 
// following way gives us access to the following data: 
// body.heartrate  - Heartrate
// body.confidence - Confidence in the heartrate value
// body.oxygen     - Blood oxygen level
// body.status     - Has a finger been sensed?


Epd epd;

// Arduino Startup Routine
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // if (epd.Init() != 0) {
  //   Serial.print("e-Paper init failed");
  //   return;
  // }
	// //Serial.print(UNCOLORED);
  // /* This clears the SRAM of the e-paper display */
  // epd.ClearFrame();

  // /**
  //   * Due to RAM not enough in Arduino UNO, a frame buffer is not allowed.
  //   * In this case, a smaller image buffer is allocated and you have to 
  //   * update a partial display several times.
  //   * 1 byte = 8 pixels, therefore you have to set 8*N pixels at a time.
  //   */
  // unsigned char image[750];
  // Paint paint(image, 200, 28);    //width should be the multiple of 8 

  // Serial.print("Starting paint");
  // paint.Clear(UNCOLORED);
  // paint.DrawStringAt(0, 0, "Bazinga", &Font24, COLORED);
  // epd.SetPartialWindow(paint.GetImage(), 100, 40, paint.GetWidth(), paint.GetHeight());

  // /* This displays the data from the SRAM in e-Paper module */
  // epd.DisplayFrame();

  // // Reset
  // delay(2000);
  
  // epd.ClearFrame();
  // epd.DisplayFrame();

  // Bio Sensor Startup
  Wire.begin();
  Serial.print("Wire started");
  int result = bioHub.begin();
  if (result == 0) // Zero errors!
    Serial.println("Sensor started!");
  else
    Serial.println("Could not communicate with the sensor!");
 
  Serial.println("Configuring Sensor...."); 
  int error = bioHub.configBpm(MODE_ONE); // Configuring just the BPM settings. 
  if(error == 0){ // Zero errors!
    Serial.println("Sensor configured.");
  }
  else {
    Serial.println("Error configuring sensor.");
    Serial.print("Error: "); 
    Serial.println(error); 
  }

  // Data lags a bit behind the sensor, if you're finger is on the sensor when
  // it's being configured this delay will give some time for the data to catch
  // up. 
  Serial.println("Loading up the buffer with data....");
  // delay(4000); 
}

// Main Routine
void loop() {
  // Information from the readBpm function will be saved to our "body"
  // variable.  
  body = bioHub.readBpm();
  Serial.print("Heartrate: ");
  Serial.println(body.heartRate); 
  Serial.print("Confidence: ");
  Serial.println(body.confidence); 
  Serial.print("Oxygen: ");
  Serial.println(body.oxygen); 
  Serial.print("Status: ");
  Serial.println(body.status); 

  //delay(1000);

  if (epd.Init() != 0) {
    Serial.print("e-Paper init failed");
    return;
  }
	//Serial.print(UNCOLORED);
  /* This clears the SRAM of the e-paper display */
  epd.ClearFrame();

  /**
    * Due to RAM not enough in Arduino UNO, a frame buffer is not allowed.
    * In this case, a smaller image buffer is allocated and you have to 
    * update a partial display several times.
    * 1 byte = 8 pixels, therefore you have to set 8*N pixels at a time.
    */
  unsigned char image[750];
  Paint paint(image, 200, 28);    //width should be the multiple of 8 

  Serial.print("Starting paint");
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 0, ("BPM: " + String(body.heartRate)).c_str(), &Font24, COLORED);
  epd.SetPartialWindow(paint.GetImage(), 100, 40, paint.GetWidth(), paint.GetHeight());

  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 0, ("Conf: " + String(body.confidence)).c_str(), &Font24, COLORED);
  epd.SetPartialWindow(paint.GetImage(), 100, 80, paint.GetWidth(), paint.GetHeight());

  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 0, ("Oxygen: " + String(body.oxygen)).c_str(), &Font24, COLORED);
  epd.SetPartialWindow(paint.GetImage(), 100, 120, paint.GetWidth(), paint.GetHeight());

  Serial.println(body.status);
  String finalStatus = "";
  switch (body.status) {
    case 0:
      finalStatus = "NO OBJ";
      break;
    case 1:
      finalStatus = "OBJ DETECTED";
      break;
    case 2:
      finalStatus = "NOT FINGER";
      break;
    case 3:
      finalStatus = "MEASURING";
      break;
    default:
      finalStatus = "UNKNOWN";
      break;
  }

  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 0, finalStatus.c_str(), &Font24, COLORED);
  epd.SetPartialWindow(paint.GetImage(), 100, 160, paint.GetWidth(), paint.GetHeight());

  /* This displays the data from the SRAM in e-Paper module */
  epd.DisplayFrame();
  
  Serial.print("Finishing paint");
}

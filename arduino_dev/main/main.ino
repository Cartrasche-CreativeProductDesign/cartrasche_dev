#include <SoftwareSerial.h>

void setup()
{
  // Serial for Raspberry Pi
  Serial.begin(9600);
  initialize_bldc();
  Serial.println("Arduino is ready");
}


void loop()
{

  if (Serial.available())
  { // Read flag from Raspberry Pi
    Serial.println("TEST");
  }

  bldc_control(10);

}

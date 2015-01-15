// Set up connection to Access Point and print incoming data.
// This Example is in the public domain.

#include <SoftwareSerial.h>
int wiflyTxPin=10; // the pin that sends data to the Wifly
int wiflyRxPin=11; // the pin that receives data from the the Wifly

SoftwareSerial softSerial(wiflyRxPin,wiflyTxPin); // make a software serial that will handle communication to Wifly

#include <WiFlyHQ.h>
WiFly wifly;  // This object will do all the configuration

void setup()
{ 
  Serial.begin(115200);

  //Setup the Wifly. Replace <HardwareSerial> by <SoftwareSerial> if you use one.
  wifly.setupForUDP<SoftwareSerial>(
  &softSerial,   // the serial you want to use (this can also be a software serial). Connect Wifly to this Serial.
  28800,     // if you use a hardware serial, I would recommend the full 115200. 28800 is the maximum that works reliably with a software serial.
  true,	      // should we try some other baudrates if the currently selected one fails?
  "wally",    // Your Wifi Name (SSID)
  "robomint", // Your Wifi Password 
  "WiFly",    // Device name for identification in the network
  0,          // IP Adress of the Wifly. if 0 (without quotes), it will use dhcp to get an ip. Incoming packets must go to the IP adress shown during setup.
  8000,                   // WiFly receive port -  incoming packets have to be sent there
  "255.255.255.255",      // Where to send outgoing Osc messages. "255.255.255.255" will send to all hosts in the subnet
  8001,                   // outgoing port - outgoing packets will be sent there
  true	// show debug information on Serial
  );
  wifly.printStatusInfo(); // test connectivity and print some debug information (this is slow)
}


void loop()
{
  // just print everything that arrived on the serial monitor.
  if (wifly.available() > 0) {
    Serial.write(wifly.read());
  }
}


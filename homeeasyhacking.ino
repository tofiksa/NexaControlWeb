/*
 * Example program using the HomeEasy class.
 */

#include "HomeEasy.h"
#include <Bridge.h>
#include <Process.h>
#include <HttpClient.h>

HomeEasy homeEasy;
Process script;
String lightson = "on";
String lightsoff = "off";

/**
 * Set up the serial interface and the HomeEasy class.
 */
void setup()
{
	Serial.begin(9600);

  

	homeEasy = HomeEasy();
  Bridge.begin();

  //SerialUSB.begin(9600);
  
	//homeEasy.registerSimpleProtocolHandler(printSimpleResult);
	//homeEasy.registerAdvancedProtocolHandler(printAdvancedResult);
	
	homeEasy.init();
  //while (!SerialUSB);
}


/**
 * No processing is required in the loop for receiving.
 */
void loop()
{
  delay(1000); //3600000
  HttpClient client;
  client.get("http://localhost/ascii.txt");

  unsigned long sender = 87729750; //20620886
  unsigned int recipient = 0;
  bool command = true;
  bool group = false;
  String dataString = "";

  while (client.available()) {
    char c = client.read();
    dataString += c;
    
    if (lightson == dataString) {
      Serial.println(c);
      command = true;      
      homeEasy.sendAdvancedProtocolMessage(sender, recipient, command, group);
    } else if (lightsoff == dataString) {
      Serial.println(c);
      command = false;
      homeEasy.sendAdvancedProtocolMessage(sender, recipient, command, group);      
    }
  }
}

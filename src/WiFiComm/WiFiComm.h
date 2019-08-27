


#ifndef WiFiComm_h
#define WiFiComm_h

#include <SPI.h>
#include <WiFiNINA.h>
#include "WiFiServer.h"


class WiFiComm
{
	public:
		int led =  LED_BUILTIN;
		int status = WL_IDLE_STATUS;
		WiFiServer server = NULL;

	
        WiFiComm();
        
		void init(int led, const char *ssid, const char *pass);
		
		int getStatus();	
				
		WiFiClient getClient();		
};

#endif
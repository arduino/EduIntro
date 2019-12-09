


#ifndef WiFiComm_h
#define WiFiComm_h

//#if defined(ARDUINO_ARCH_MEGAAVR)
#if defined(AVR_UNO_WIFI_REV2)
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

        String getSSID();

        IPAddress getIP();
				
		WiFiClient getClient();		
};

#endif

#endif

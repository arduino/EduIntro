
#include "WiFiComm.h"

//#if defined(ARDUINO_ARCH_MEGAAVR)
#if defined(AVR_UNO_WIFI_REV2)

WiFiComm::WiFiComm () {
	server = WiFiServer(80);

}

void WiFiComm::init(int led, const char *ssid, const char *pass){
	
	//while (!Serial) {;} // wait for serial port to connect. Needed for native USB port only
	
	Serial.println("Access Point Web Server");
	pinMode(led, OUTPUT);      // set the LED pin mode

	  // check for the WiFi module:
	if (WiFi.status() == WL_NO_MODULE) {
		Serial.println("Communication with WiFi module failed!");
		// don't continue
		while (true);
	}
	
	String fv = WiFi.firmwareVersion();
	if (fv < "1.0.0") {
		Serial.println("Please upgrade the firmware");
	}
	
	// by default the local IP address of will be 192.168.4.1
	// you can override it with the following:
	// WiFi.config(IPAddress(10, 0, 0, 1));

	// print the network name (SSID);
	Serial.print("Creating access point named: ");
	Serial.println(ssid);
	
	// Create open network. Change this line if you want to create an WEP network:
	status = WiFi.beginAP(ssid);
	
	if (status != WL_AP_LISTENING) {
		Serial.println("Creating access point failed");
		// don't continue
		while (true);
	}
	
	// wait 10 seconds for connection:
	delay(10000);
	
	// start the web server on port 80
	server.begin();
	
}

String WiFiComm::getSSID() {
    return WiFi.SSID();
}

IPAddress WiFiComm::getIP() {
    return WiFi.localIP();
}

int WiFiComm::getStatus(){
	return WiFi.status();
}

WiFiClient WiFiComm::getClient() {
	return server.available();
}

#endif

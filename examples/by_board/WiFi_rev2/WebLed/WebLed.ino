/*
  WebLed

  WiFi Web Server LED Blink

  A simple web server that lets you blink an LED via the web.
  This sketch will create a new access point (with no password).
  It will then launch a new server and print out the IP address
  to the Serial monitor. From there, you can open that address in a web browser
  to turn on and off the LED on pin 13.

  If the IP address of your board is yourAddress:
    http://yourAddress/H turns the LED on
    http://yourAddress/L turns it off

  Adapted to EduIntro by C. Rodriguez, and D. Cuartielles (2019)

  Created by Tom Igoe (2012)
*/

#include <EduIntro.h>

// network related info
const char ssid[] = "ArduinoWiFi";   // your network SSID (name). Must have 8 or more characters.
const char pass[] = "";       // your network password (use for WPA, or use as key for WEP). optional, but if set, must have 8 or more characters.
int keyIndex = 0;       // your network key Index number (needed only for WEP)

// misc variables
WiFiComm MyWiFi;
int led = LED_BUILTIN;
int status = WL_IDLE_STATUS;
boolean firstTime = true;

void setup() {
  // initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {};

  MyWiFi.init(led, ssid, pass);

  // you're connected now, so print out the status
  printWiFiStatus();
  Serial.print("\t SSID:");
  Serial.println(MyWiFi.getSSID());
}

void loop() {
  // compare the previous status to the current status
  if (status != MyWiFi.getStatus()) {
    // it has changed update the variable
    status = MyWiFi.getStatus();

    if (status == WL_AP_CONNECTED) {
      // a device has connected to the AP
      Serial.println("Device connected to AP");
    } else {
      if (!firstTime) {
        // a device has disconnected from the AP, and we are back in listening mode
        Serial.println("Device disconnected from AP");
      }
    }
  }

  WiFiClient client = MyWiFi.getClient();   // listen for incoming clients

  if (client) {                             // if you get a client,
    firstTime = false;
    Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("Click <a href=\"/H\">here</a> turn the LED on<br>");
            client.print("Click <a href=\"/L\">here</a> turn the LED off<br>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          }
          else {      // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        }
        else if (c != '\r') {    // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(led, HIGH);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(led, LOW);                // GET /L turns the LED off
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }

}


void printWiFiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(MyWiFi.getSSID());

  // print your WiFi shield's IP address:
  IPAddress ip = MyWiFi.getIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print where to go in a browser:
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}

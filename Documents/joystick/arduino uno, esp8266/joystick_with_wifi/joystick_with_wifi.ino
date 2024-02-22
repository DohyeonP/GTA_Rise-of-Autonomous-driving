#include <SoftwareSerial.h>

SoftwareSerial espSerial(2, 3); // RX, TX

// Function declarations
void sendCommand(String command);
void sendData(String data);
void waitForResponse();

void setup() {
  Serial.begin(115200); // Arduino serial communication setup
  espSerial.begin(115200); // ESP8266 serial communication setup
  
  // ESP8266 initialization
  sendCommand("AT+RST");
  delay(2000);
  
  // Set to single connection mode
  sendCommand("AT+CIPMUX=0");
  
  // Connect to Wi-Fi
  sendCommand("AT+CWJAP=\"aiot5\",\"aiot51234\"");
  delay(5000); // Wait for Wi-Fi connection

// Set static IP address
//sendCommand("AT+CIPSTA=\"10.10.15.201\"");

  // Start TCP connection
  sendCommand("AT+CIPSTART=\"UDP\",\"10.10.15.88\",12344");
}

void loop() {
  // Send data
  int x1 = analogRead(A0);
  int y1 = analogRead(A1);
  int x2 = analogRead(A2);
  int y2 = analogRead(A3);
  sendData(x1, y1, x2, y2);
  delay(10); // 5-second interval for data transmission
}

void sendCommand(String command) {
  espSerial.println(command);
  waitForResponse();
}

void sendData(int x1, int y1, int x2, int y2) {
  // Construct data string with variables
  String data = "x1(" + String(x1) + "),y1(" + String(y1) + "),x2(" + String(x2) + "),y2(" + String(y2) + ")";
  
  // Initiate data transmission command
  sendCommand("AT+CIPSEND=" + String(data.length() + 2)); // +2 to account for potential two-digit values
  
  delay(100);
  
  // Actual data transmission
  espSerial.println(data);
  //delay(100);
}

void waitForResponse() {
  delay(10);
  while (espSerial.available() > 0) {
    char c = espSerial.read();
    Serial.print(c);
  }
  Serial.println();
}

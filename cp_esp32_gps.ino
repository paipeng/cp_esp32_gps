#include <SoftwareSerial.h>
#include <TinyGPSPlus.h>
#define ATGM336H_TX_PIN 16 // TX pin of BT JDY16 -> RX pin of ESP32
#define ATGM336H_RX_PIN 17 // RX pin of BT JDY16 -> TX pin of ESP32

#define ATGM336H_GPS_BAND 9600
// The TinyGPSPlus object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(ATGM336H_TX_PIN, ATGM336H_RX_PIN);

void setup() {
  Serial.begin(115200);

  Serial.println("Serial inited");
  delay(2000);

  ss.begin(9600);
  Serial.println("software-serial inited");
  Serial.print(F("Testing TinyGPSPlus library v. ")); 
  Serial.println(TinyGPSPlus::libraryVersion());
	
}

void loop() {
  updateSerial();
}


void updateSerial() {
  // This sketch displays information every time a new sentence is correctly encoded.
	while (ss.available() > 0) {
		if (gps.encode(ss.read())) {
			displayInfo();
		}
	}

	if (millis() > 5000 && gps.charsProcessed() < 10) {
		Serial.println(F("No GPS detected: check wiring."));
		while(true);
	}
}


void displayInfo() {
	Serial.print(F("Location: ")); 
	if (gps.location.isValid()) {
		Serial.print(gps.location.lat(), 6);
		Serial.print(F(","));
		Serial.print(gps.location.lng(), 6);
	} else {
		Serial.print(F("INVALID"));
	}

	Serial.print(F("  Date/Time: "));
	if (gps.date.isValid()) {
		Serial.print(gps.date.month());
		Serial.print(F("/"));
		Serial.print(gps.date.day());
		Serial.print(F("/"));
		Serial.print(gps.date.year());
	} else {
		Serial.print(F("INVALID"));
	}

	Serial.print(F(" "));
	if (gps.time.isValid()) {
		if (gps.time.hour() < 10) Serial.print(F("0"));
		Serial.print(gps.time.hour());
		Serial.print(F(":"));
		if (gps.time.minute() < 10) Serial.print(F("0"));
		Serial.print(gps.time.minute());
		Serial.print(F(":"));
		if (gps.time.second() < 10) Serial.print(F("0"));
		Serial.print(gps.time.second());
		Serial.print(F("."));
		if (gps.time.centisecond() < 10) Serial.print(F("0"));
		Serial.print(gps.time.centisecond());
    
	} else {
		Serial.print(F("INVALID"));
	}

	Serial.println();
}
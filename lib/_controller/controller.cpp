

/*
	NOTE: these SDKs deliberately ignore error handling.  someone else's code is hard enough to read, let alone recognizing key logic
	from boilerplate error handling.  Error handling is an important part of firmware, but I left it out here so you can focus on getting 
	your arms around the system logic.  Once you are comfortable, wrap your code in all of the error handling that you feel is appropriate.
*/

#include "Arduino.h"

#include "controller.h"

#include "ca_cert.h"
#include "device_id.h"
#include "mqtt.h"
#include "wifi_tools.h"



/* 
To override the CA_CERT to point your device to a different MQTT broker, create your own CA cert variable and define CA_CERT to point to that variable name: 
	const char YOUR_CERT[] = "-----BEGIN CERTIFICATE-----\n"
		"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n"
		"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n"
		"-----END CERTIFICATE-----\n";

	#define CA_CERT YOUR_CERT
*/
#ifndef CA_CERT
    #define CA_CERT OHIOIOT_CA_CERT
#endif


// Override the following with build flags in platformio if you want something different

#ifndef MQTT_HOST
    #define MQTT_HOST "test-mqtt.ohioiot.com"
#endif

#ifndef MQTT_PORT
    #define MQTT_PORT 8883
#endif

char wifi_ssid[WIFI_SSID_LEN];	// are these LEN defined anywhere?
char wifi_pass[WIFI_PASS_LEN];


Controller::Controller() {}

Controller controller;









void Controller::setup(const char * wifi_ssid, const char * wifi_pass, const char * mqtt_user, const char * mqtt_pass) {

    char deviceID[9];
    device_id.get_or_set(deviceID);

	wifi_tools.begin(wifi_ssid, wifi_pass);

	Serial.print("\tusing MQTT host: ");	Serial.println(MQTT_HOST);
	Serial.print("\tusing MQTT port: ");	Serial.println(MQTT_PORT);

	mqtt.setup(MQTT_HOST, MQTT_PORT, mqtt_user, mqtt_pass, deviceID, CA_CERT); 

}


void Controller::loop() {

	// do something that doesn't require MQTT

	if (wifi_tools.is_connected) {

		mqtt.maintain();

		if (mqtt.is_connected) {

			// do something that requires MQTT

		}


	} else {

		mqtt.report_disconnect();

	}


}



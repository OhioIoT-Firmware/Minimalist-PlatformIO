#include "Arduino.h"

#include "credentials.h"
#include "controller.h"
#include "mqtt.h"



// REGULAR SUBSCRIPTIONS AND MESSAGE HANDLING Part 1 ----------------------------------
//
// Topics this device listens to.  Two shorthands save you typing:
//
//     ~/        becomes   your-mqtt-user/
//     ~/~/      becomes   your-mqtt-user/this-device-id/
//
// So "~/~/inbox" below arrives as   your-mqtt-user/a1b2c3d4e/inbox
//
// Rename these, add your own, or leave just the nullptr if you don't need any.

static const char * subscription_list[] = {
	"~/~/inbox",			// anything sent to this one device
	"~/~/config",			// a second topic, to show the list takes several
	nullptr					// keep this
};


// Runs for every message that arrives on a topic above.
// `topic` is the full expanded topic; `payload` is the message body.
void messageHandler(char * topic, char * payload) {
	Serial.println(payload);	// replace this with something more interesting when you are ready
}






void setup() {

	Serial.begin(115200);
	Serial.println("\n\n\n+++++++++++  DEVICE BOOT  ++++++++++++++++++++++++++++++++++\n");

	controller.setup(WIFI_SSID, WIFI_PASS, MQTT_USER, MQTT_PASS);

	// REGULAR SUBSCRIPTIONS AND MESSAGE HANDLING Part 2 -----------------------------------
	mqtt.set_subscriptions(subscription_list);
	mqtt.set_callback(messageHandler);


	// your own setup code goes here

}




void loop() {

	controller.loop();

	// Keep this loop non-blocking — no delay().  The controller needs to run
	// often to hold the WiFi and MQTT connections up.  For periodic work,
	// compare millis() against a timestamp you saved last time round.

	if (mqtt.is_connected) {

		// your own code here — publish readings, read sensors, and so on
		
	}

}



#include "Arduino.h"

#include "credentials.h"
#include "controller.h"

#include "mqtt.h"




/* 
	1A) If you want any direct subscriptions, put them here.  You want direct subscriptions for messages that aren't coming
	from the app.  In-app commands are automatically subscribed to in Scaler and Champion.
*/
static const char * subscription_list[] = {
	"~/~/whatever",
    nullptr
};

/*
	2A)  If you are subscribing to custom topics, you need a function that gets called when those messages come in.  This works
	in every tier.  Define a function here, in the global space, and inject it with mqtt.set_callback() below.
*/
void messageHandler(char * topic, char * payload) {
    Serial.println("\n\tWE GOT A GENERAL MESSAGE:");
    Serial.print("\ttopic: ");
    Serial.print(topic);
    Serial.print("\t\tpayload: ");
    Serial.println(payload);
}






void setup() {

    Serial.begin(115200);
    Serial.println("\n\n\n+++++++++++  DEVICE BOOT  ++++++++++++++++++++++++++++++++++\n");

    controller.setup(WIFI_SSID, WIFI_PASS, MQTT_USER, MQTT_PASS);     

    // 1B)
	mqtt.set_subscriptions(subscription_list);

	/*
		2B)  Inject your function here.  Works in every tier — this is the raw
		message hook.  In Scaler/Champion the framework router runs first and
		only un-routed messages reach this handler.
	*/
    mqtt.set_callback(messageHandler);


}




void loop() {

	controller.loop();

    if (mqtt.is_connected) {

		// do something
		
    }

}





// TODO: Device ID randomness. _create_code() uses random(36) with no randomSeed(). On the ESP32 Arduino core random() is backed by the hardware RNG (esp_random()), so this is almost certainly fine — but given that a collision in an 8-char ID would be catastrophic in a multi-tenant system, it's worth a one-line confirmation that your core version routes random() to the HW RNG and not a deterministic newlib PRNG. If you ever have doubt, seed from esp_random() explicitly before the loo

// TODO: events.increment() writes NVS on every wifi retry. wifi_retries increments each time reconnect() fires, which is every RECONNECT_INTERVAL (10 s) while offline — and each increment is a putUInt. A device stuck offline overnight writes the same key thousands of times. NVS has wear leveling, but this is the kind of thing that quietly kills flash on a long-deployed fleet. Consider accumulating retries/drops in RAM and flushing to NVS only on a clean reconnect (or on a timer), rather than on every attempt.

// TODO:  do we need to lock the partition scheme as well?

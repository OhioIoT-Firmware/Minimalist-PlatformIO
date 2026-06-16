

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



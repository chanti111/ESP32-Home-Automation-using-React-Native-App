#include <WiFi.h>

#include <Firebase_ESP_Client.h>

// WIFI

#define WIFI_SSID "chanti"

#define WIFI_PASSWORD "ravikumar"

// FIREBASE

#define API_KEY ""

#define DATABASE_URL ""

// FIREBASE OBJECTS

FirebaseData fbdo;

FirebaseAuth auth;

FirebaseConfig config;

// LED PIN

int led1 = 23;

void setup()
{
  Serial.begin(115200);

  pinMode(led1, OUTPUT);

  // WIFI CONNECT

  WiFi.begin(
    WIFI_SSID,
    WIFI_PASSWORD
  );

  Serial.print("Connecting");

  while (
    WiFi.status() != WL_CONNECTED
  ) {

    Serial.print(".");

    delay(1000);
  }

  Serial.println("");

  Serial.println("WiFi Connected");

  Serial.println(WiFi.localIP());

  // FIREBASE CONFIG

  config.api_key = API_KEY;

  config.database_url =
  DATABASE_URL;

  config.signer.test_mode = true;

  config.timeout.serverResponse =
  10000;

  // SSL BUFFER FIX

  fbdo.setBSSLBufferSize(
    4096,
    1024
  );

  Firebase.begin(
    &config,
    &auth
  );

  Firebase.reconnectWiFi(true);

  Serial.println("Firebase Started");
}

void loop()
{
  if (
    Firebase.RTDB.getInt(
      &fbdo,
      "/led1"
    )
  ) {

    int ledState =
    fbdo.intData();

    digitalWrite(
      led1,
      ledState
    );

    Serial.print("LED STATE: ");

    Serial.println(ledState);
  }

  else {

    Serial.println("Firebase Error");

    Serial.println(
      fbdo.errorReason()
    );
  }

  delay(1000);
}

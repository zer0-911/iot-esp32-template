#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#ifdef __cplusplus
extern "C"
{
#endif
  uint8_t temprature_sens_read();
#ifdef __cplusplus
}
#endif
uint8_t temprature_sens_read();
// Masukan ssid dan password dari router
const char *ssid = "Hiya";
const char *password = "1234567890";
// Alamat IP server dengan portnya
unsigned long lastTime = 0;
unsigned long timerDelay = 1000;
void setup()
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}
void loop()
{
  if ((millis() - lastTime) > timerDelay)
  {
    // cek koneksi
    if (WiFi.status() == WL_CONNECTED)
    {
      WiFiClient client;
      HTTPClient http;
      float temp = (temprature_sens_read() - 32) / 1.8;
      char serverName[100];
      sprintf(serverName, "http://192.168.204.93:5000/esp?temperature=%3.2f",
              temp); // Setting IP Address and Port as per your server
      http.begin(client, serverName);
      // kirimkan HTTP POST
      int httpResponseCode = http.POST("");
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      http.end();
    }
    else
    {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}
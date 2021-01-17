#include "esp_camera.h"
#include <ArduinoWebsockets.h>
#include <WiFi.h>
#include <WiFiMulti.h>

using namespace websockets;

typedef struct {
  const char *name;
  const char *pwd;
} WiFiItem_t;

const char* websockets_server_host = "10.0.0.6";
const uint16_t websockets_server_port = 80;

WiFiItem_t WiFiTable[] = {
  { "WiFiName1", "" },
  { "WiFiName2", "12345678" },
  { "WiFiName3", "87654321" }
};

const unsigned int WiFiCnt = sizeof(WiFiTable) / sizeof(WiFiItem_t);

WebsocketsClient client;
WiFiMulti wifiMulti;

#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27

#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22


void setup_camera() {
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  config.frame_size = FRAMESIZE_QVGA;
  config.jpeg_quality = 10;
  config.fb_count = 1;
  

  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }

}

void setup_wifi() {

  for (uint8_t t = 3; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }


  for (uint8_t i = 0; i < WiFiCnt; i++) {
    Serial.printf("Add AP %s %s\n", WiFiTable[i].name, WiFiTable[i].pwd);
    wifiMulti.addAP(WiFiTable[i].name, WiFiTable[i].pwd);
  }

}

void setup() {
  Serial.begin(115200);

  setup_camera();

  setup_wifi();
}



void capture_video() {
  camera_fb_t * fb = NULL;

  fb = esp_camera_fb_get();
  if (NULL == fb) {
    Serial.println(F("Camera capture failed"));
  } else {
    client.sendBinary((const char *)fb->buf, fb->len);
    esp_camera_fb_return(fb);
    fb = NULL;
  }
}

void loop() {

  uint8_t wifiState = wifiMulti.run();
  if ((wifiState != WL_CONNECTED)) {
    Serial.printf("[WiFi] connected to wifi failed. ret %d\n", wifiState);
    delay(1000);
    return;
  }

  if (client.available()) {
    capture_video();
    client.poll();
  } else {
    Serial.println("Connected to Wifi, Connecting to server.");

    bool connected = client.connect(websockets_server_host, websockets_server_port, "/video");
    if (connected) {
      Serial.println("Connected!");
    } else {
      Serial.println("Not Connected!");
    }

    // run callback when messages are received
    client.onMessage([&](WebsocketsMessage message) {
      Serial.print("Got Message: ");
      Serial.println(message.data());
    });
  }
}

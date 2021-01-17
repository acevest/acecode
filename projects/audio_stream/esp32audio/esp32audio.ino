#include <ArduinoWebsockets.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2s.h"
#include "esp_system.h"

#define SAMPLE_RATE (8000)

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



void setup_max9814() {
  i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX | I2S_MODE_TX | I2S_MODE_DAC_BUILT_IN | I2S_MODE_ADC_BUILT_IN),
    .sample_rate = SAMPLE_RATE,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
    .communication_format = (i2s_comm_format_t)(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB),
    .intr_alloc_flags = 0,
    .dma_buf_count = 16,
    .dma_buf_len = 60
  };


  Serial.println("using ADC_builtin");
  i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);

  // 使用ESP32的GPIO36, 也就是ADC0、SVP引脚来采样
  i2s_set_adc_mode(ADC_UNIT_1, ADC1_CHANNEL_0);
}

const int audioBufSize = 1024;
char audioBuf[audioBufSize];

bool webSocketConnected = false;

void capture_audio() {
  i2s_read_bytes(I2S_NUM_0, (char *)audioBuf, audioBufSize, portMAX_DELAY);

  // 只要单声道数据
  uint16_t *buf = (uint16_t *)audioBuf;
  int to = 0;
  for (int i = 0; i < audioBufSize / 2; i += 2) {
    buf[to] = buf[i];
    to++;
  }
  if (webSocketConnected && client.available()) {
    Serial.println("before send");
    client.sendBinary((const char *)audioBuf, audioBufSize / 2);
    Serial.println("read and send audio data");
  } else {
    if (!webSocketConnected) {
      Serial.println("websocket not connected");
    }
    if (client.available()) {
      Serial.println("client not available");
    }
  }
}



void setup() {
  Serial.begin(115200);

  setup_max9814();

  setup_wifi();
}

void loop() {

  uint8_t wifiState = wifiMulti.run();
  if ((wifiState != WL_CONNECTED)) {
    Serial.printf("[WiFi] connected to wifi failed. ret %d\n", wifiState);
    delay(1000);
    return;
  }

  if (client.available()) {
    capture_audio();
    client.poll();
  } else {
    Serial.println("Connected to Wifi, Connecting to server.");

    webSocketConnected = client.connect(websockets_server_host, websockets_server_port, "/audio");
    if (webSocketConnected) {
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

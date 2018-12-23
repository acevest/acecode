#include <stdio.h>
#include <stdlib.h>
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "driver/gpio.h"
#include "rom/ets_sys.h"

const int WIFI_CONNECTED_BIT = BIT0;
static EventGroupHandle_t wifi_event_group;

const int led_pin = GPIO_NUM_16;
void led_blink_task(void *pvParameters)
{
    printf("Blinker Task Running...\n");
    gpio_set_direction(led_pin, GPIO_MODE_OUTPUT);
    while(1) {
        gpio_set_level(led_pin, !gpio_get_level(led_pin));
        int r = rand() % 500;
        vTaskDelay(r/portTICK_RATE_MS);
    }
}

static esp_err_t event_handler(void *ctx, system_event_t *event)
{
    switch(event->event_id) {
    case SYSTEM_EVENT_STA_GOT_IP:
        printf("got ip: %s\n", ip4addr_ntoa(&event->event_info.got_ip.ip_info.ip));
        xEventGroupSetBits(wifi_event_group, WIFI_CONNECTED_BIT);
        break;
    case SYSTEM_EVENT_STA_START:
        esp_wifi_connect();
        break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
        esp_wifi_connect();
        xEventGroupClearBits(wifi_event_group, WIFI_CONNECTED_BIT);
        printf("disconnected\n");
        break;
    default:
        printf("unsupport event id %x\n", event->event_id);
        break;
    };
    return ESP_OK;
}

void wifi_init_sta() {
    printf("esp wifi init STA start...\n");

    tcpip_adapter_init();
    ESP_ERROR_CHECK(esp_event_loop_init(event_handler, NULL));

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    wifi_config_t wifi_config = {
        .sta = {
            .ssid     = CONFIG_ESP_WIFI_SSID,
            .password = CONFIG_ESP_WIFI_PASSWORD,
        },
    };

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    printf("esp wifi init STA finished...\n");
}

void wifi_task(void *pvParameters)
{
    wifi_init_sta();
    //while(true) {
    //    vTaskDelay(100/portTICK_RATE_MS);
    //}
    vTaskDelete(NULL);
}

void init() {
    wifi_event_group = xEventGroupCreate();
}

void app_main(void)
{
    printf("SDK version:%s\n", esp_get_idf_version());

    init();
    //wifi_init_sta();

    xTaskCreate(led_blink_task, "Blink", 512,  NULL, 2, NULL);
    xTaskCreate(wifi_task,      "WiFi",  4096, NULL, 2, NULL);

    for (int i = 10; i >= 0; i--) {
        printf("Restarting in %d seconds...\n", i);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    printf("main task exited...\n");
}

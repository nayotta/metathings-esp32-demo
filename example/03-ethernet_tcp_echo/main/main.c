#include "esp_err.h"
#include "esp_log.h"
#include "string.h"

#include "lwip/netdb.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "nvs.h"

#include "mt_ethernet.h"

// global config ==============================================================

static const char *TAG = "ESP32_ETHERNET_MAIN";

int LIGHT_PIN = 14;
int LIGHT_PIN_ON_LEVEL = 0;

char *TCP_HOST_ADDR = "10.1.1.237";
uint32_t TCP_HOST_PORT = 6000;

// global func ================================================================

void app_main() {
  esp_err_t err = ESP_OK;
  char rx_buf[128];
  struct sockaddr_in dest_addr;
  ESP_LOGI(TAG, "%4d %s start", __LINE__, __func__);

  // 启动网络服务
  mt_ethernet_task(LIGHT_PIN, LIGHT_PIN_ON_LEVEL);

  // tcp echo
  dest_addr.sin_addr.s_addr = inet_addr(TCP_HOST_ADDR);
  dest_addr.sin_family = AF_INET;
  dest_addr.sin_port = htons(TCP_HOST_PORT);

  // create socket
  int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
  if (sock < 0) {
    ESP_LOGE(TAG, "%4d %s socket error", __LINE__, __func__);
    return;
  }
  ESP_LOGI(TAG, "%4d %s Socket created, connecting to %s:%d", __LINE__,
           __func__, TCP_HOST_ADDR, TCP_HOST_PORT);

  // connect
  while ((err = connect(sock, (struct sockaddr *)&dest_addr,
                        sizeof(dest_addr))) != 0) {
    ESP_LOGE(TAG, "%4d %s Socket connect failed", __LINE__, __func__);
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
  ESP_LOGI(TAG, "%4d %s Socket connect success", __LINE__, __func__);

  // echo(recv and send)
  while (1) {
    int len = recv(sock, rx_buf, sizeof(rx_buf) - 1, 0);
    if (len < 0) {
      ESP_LOGE(TAG, "%4d %s recv failed", __LINE__, __func__);
      return;
    }

    ESP_LOGI(TAG, "%4d %s recv:%s", __LINE__, __func__, rx_buf);

    err = send(sock, rx_buf, len, 0);
    if (err < 0) {
      ESP_LOGE(TAG, "%4d %s send failed", __LINE__, __func__);
      return;
    }
  }
}

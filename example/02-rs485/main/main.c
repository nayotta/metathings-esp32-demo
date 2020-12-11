#include "esp_err.h"
#include "esp_log.h"
#include "string.h"

#include "driver/uart.h"

// global config ==============================================================

static const char *TAG = "MT_RS485_MAIN";

int TX_PIN = 13;
int RX_PIN = 15;
int EN_PIN = 05;
int BAUD_RATE = 115200;
int UART_PORT = 2;

// global func ================================================================

void app_main() {
  uint8_t data[128];
  ESP_LOGI(TAG, "%4d %s start", __LINE__, __func__);
  uart_config_t uart_config = {
      .baud_rate = BAUD_RATE,
      .data_bits = UART_DATA_8_BITS,
      .parity = UART_PARITY_DISABLE,
      .stop_bits = UART_STOP_BITS_1,
      .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
      .rx_flow_ctrl_thresh = 122,
      .source_clk = UART_SCLK_APB,
  };

  uart_driver_install(UART_PORT, 128 * 2, 0, 0, NULL, 0);
  uart_param_config(UART_PORT, &uart_config);
  uart_set_pin(UART_PORT, TX_PIN, RX_PIN, EN_PIN, -1);
  uart_set_mode(UART_PORT, UART_MODE_RS485_HALF_DUPLEX);
  uart_write_bytes(UART_PORT, "Start RS485 UART test.\r\n", 24);

  while (1) {
    int len = uart_read_bytes(UART_PORT, data, sizeof(data),
                              1 * 1000 / portTICK_RATE_MS);
    if (len > 0) {
      printf("recive:%s\n", data);
      uart_write_bytes(UART_PORT, (char *)data, len);
    }
  }
}

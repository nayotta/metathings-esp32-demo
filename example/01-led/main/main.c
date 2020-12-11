#include "esp_err.h"
#include "esp_log.h"
#include "string.h"

#include "lwip/netdb.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"

#include "gpio_light.h"

// global config ==============================================================

static const char *TAG = "MT_LED_MAIN";

int LIGHT_PIN = 12; // led灯脚参考接口说明文档
int LIGHT_PIN_ON_LEVEL = 0;

// global func ================================================================

void app_main() {
  ESP_LOGI(TAG, "%4d %s start", __LINE__, __func__);
  mt_gpio_light_t *handle = mt_gpio_light_new(LIGHT_PIN, LIGHT_PIN_ON_LEVEL);
  mt_gpio_light_task(handle);

  while (true) {
    mt_gpio_light_set_on(handle);
    vTaskDelay(5 * 1000 / portTICK_RATE_MS); //常亮 持续5秒

    mt_gpio_light_set_blink(handle, 500);     // 500ms 快速闪烁
    vTaskDelay(10 * 1000 / portTICK_RATE_MS); //常亮 持续10秒

    mt_gpio_light_set_off(handle);
    vTaskDelay(5 * 1000 / portTICK_RATE_MS); //常灭 持续5秒
  }
}

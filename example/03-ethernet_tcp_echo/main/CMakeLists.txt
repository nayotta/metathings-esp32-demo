
idf_component_register(SRCS "main.c"
                            "../../../lib/gpio_light.c"
                            "../../../lib/mt_ethernet.c"
                       INCLUDE_DIRS "../../../include"
                       REQUIRES esp_eth nvs_flash
                       PRIV_REQUIRES esp_eth)
	
target_link_libraries(${COMPONENT_LIB} PUBLIC "-L ${CMAKE_CURRENT_SOURCE_DIR}/../../../lib")

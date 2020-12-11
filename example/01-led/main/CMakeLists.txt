
idf_component_register(SRCS "main.c"
                            "../../../lib/gpio_light.c"
                            "../../../lib/mt_smartconfig.c"
                            "../../../lib/gpio_button.c"
                            "../../../lib/mt_nvs_storage.c"
                       INCLUDE_DIRS "../../../include")
	
target_link_libraries(${COMPONENT_LIB} PUBLIC "-L ${CMAKE_CURRENT_SOURCE_DIR}/../../../lib")

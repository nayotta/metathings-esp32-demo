#ifndef _MT_ETHERNET_H
#define _MT_ETHERNET_H

#include "esp_eth.h"
#include "esp_eth_phy.h"

#define DEFAULT_ETHERNET_PHY_CONFIG phy_lan8720_default_ethernet_config

void mt_ethernet_task(int light_pin, int light_pin_on_level);

void mt_ethernet_static_task(int light_pin, int light_pin_on_level);

#endif

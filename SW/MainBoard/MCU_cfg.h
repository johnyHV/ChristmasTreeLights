/**
 * @file MCU_cfg.h
 *
 * @brief Konfiguracia procesora
 *
 * @author Miroslav Pivovarsky
 * Contact: miroslav.pivovarsky@gmail.com
 * 
 * @bug: no know bug
 *
 */

#ifndef __MCU_cfg_h_
#define __MCU_cfg_h_

#define SOFTWARE_VERSION              "1.0.1"     ///< verzia firmware

#define NUM_LEDS                      100         ///< pocet LED diod na LED pase
#define LED_BRIGHTNESS                255         ///< maximalny JAS led diod na LED pase
#define LED_TYPE                      WS2812B     ///< typ LED diod na LED pase
#define COLOR_ORDER                   RGB         ///< farebne spektrum LED diod

#define BLUETOOTH_ENABLE              false       ///< Zapnutie/vypnutie podpory bluetooth modulu a komunikacie s nim
#define WIFI_ENABLE                   true        ///< Zapnutie/vypnutie podpory WI-FI modulu a komunikaciu s WI-FI
#define IR_REMOTE_ENABLE              false       ///< Zapnutie/vypnutie podpory IRremote kniznice v kompilacnom procese

#define BLUETOOTH_BAUD_RATE           9600        ///< komunikacna rychlost s bluetooth modulom
#define WIFI_BAUD_RATE                9600        ///< komunikacna rychlost s modulom ESP32
#define COM_PORT_BAUD_RATE            115200      ///< komunikacna rychlost s doskou cez USB port

#define LOOP_REFRESH_TIME             1           ///< refresh time loop slucky

#define LED_STRIP_DATA_PIN            2           ///< GPIO pin pre komunikaciu s LED pasom
#define BUTTON_MODE                   14          ///< GPIO pin pre tlacidlo na zmenu efektu 
#define ESP_GPIO                      15          ///< GPIO pin pre komunikaciu s ESP modulom
#define IR_RX_INPUT                   3           ///< GPIO pin pre IR receiver
#define BLE_RX                        4           ///< GPIO pin pre SW serial s bluetooth RX
#define BLE_TX                        5           ///< GPIO pin pre SW serial s bluetooth TX
#define ESP_RX                        7           ///< GPIO pin pre SW serial s ESP32 RX
#define ESP_TX                        6           ///< GPIO pin pre SW serial s ESP32 TX
#define STATUS_LED                    13          ///< GPIO pin STATUS LED

/* EEPROM ADDRESS */
#define EEPROM_CURRENT_EFFECT         1           ///< Adresa pre ulozenie efektu ktory sa automaticky zapne pri zapnuti elektroniky

#define EEPROM_EFFECT_SPEED_HI        2           ///< Adresa pre ulozenie rychlosti blikania efektov HI bajt
#define EEPROM_EFFECT_SPEED_LOW       3           ///< Adresa pre ulozenie rychlosti blikania efektov LOW bajt

#define EEPROM_RANDOM_TIME_HI         4           ///< Adresa pre ulozenie dlzky svietenia jedneho efektu HI bajt
#define EEPROM_RANDOM_TIME_LOW        5           ///< Adresa pre ulozenie dlzky svietenia jedneho efektu HI bajt

#define EEPROM_AUTO_ON_STATUS         6           ///< Adresa pre ulozenie zapnutia/vypnutia automatickeho zapinania osvetlenia vo vybrany cas
#define EEPROM_AUTO_ON_EFFECT         7           ///< Adresa pre ulozenie efektu ktory sa zapne pri automatickom spusteni vo vybrany cas
#define EEPROM_AUTO_ON_TIME_ON_HOUR   8           ///< Adresa pre ulozenie hodiny zapnutia
#define EEPROM_AUTO_ON_TIME_ON_MIN    9           ///< Adresa pre ulozenie minut zapnutia
#define EEPROM_AUTO_ON_TIME_OFF_HOUR  10          ///< Adresa pre ulozenie hodin vypnutia
#define EEPROM_AUTO_ON_TIME_OFF_MIN   11          ///< Adresa pre ulozenie minut vypnutia

#endif

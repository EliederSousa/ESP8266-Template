/* Uma pequena referência dos pinos digitais do ESP8266. D0 - 16, D1 - 5, D2 - 4, D3 - 0, D4 - 2, D5 - 14, D6 - 12, D7 - 13, D8 - 15, Analog - A0 */

#ifndef _CONFIG_H_
#define _CONFIG_H_

// Defina o pinos aqui.
#define PIN_SENSOR      16      // Pino D0
#define PIN_LED         5       // Pino D1
#define PIN_BOTAO       4       // Pino D2
#define PIN_BUZZER      0       // Pino D3

// Defina aqui as constantes usadas pelo programa.
// Use a variável DEV_ENVIROMENT para definir se a saída serial irá printar informações de debug.
// Para o BAUD_RATE, procure usar valores altos pois isto pode interferir na velocidade do programa.
#define DEV_ENVIROMENT  true
#define BAUD_RATE       115200
#define BEEP_DELAY      200

#endif

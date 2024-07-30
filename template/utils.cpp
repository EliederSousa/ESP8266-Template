#include "utils.h"

void ledOn() {
    digitalWrite( PIN_LED, HIGH );
}

void ledOff() {
    digitalWrite( PIN_LED, LOW );
}

void beep( int time ) {
    digitalWrite( PIN_BUZZER, HIGH );
    delay( time );
    digitalWrite( PIN_BUZZER, LOW );
}

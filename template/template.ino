#include <Arduino.h>
#include "config.h"
#include "state.h"
#include "utils.h"

// ----------------------------------------------------------------
// Variáveis, constantes e função de leitura dos sensores.
// ----------------------------------------------------------------
// Define o estado inicial da máquina de estados.
State currentState      = STATE1;

/**
 * Crie variáveis globais para cada sensor/botão que utilizar como
 * pinMode INPUT/INPUT_PULLUP
 * Crie uma função que faça a leitura de todos os sensores ao ser chamada.
 **/
bool    state_botao     = false;
float   sensor_one      = 0.0;
void readSensors() {
    // INPUT_PULLUP faz com que a leitura de um sensor aberto (botão/switch) sempre seja 1, e fechado em 0.
    // É conveniente que um botão não pressionado retorne 0, não 1, por isso invertemos logicamente a saída do digitalRead de botões.
    state_botao     = !digitalRead(PIN_BOTAO);
    sensor_one      = digitalRead(PIN_SENSOR);
}

/**
 * Função que imprime informações como o estado atual da máquina de estados, valores dos sensores, etc.
 **/
void printSerialData( String state ) {
    Serial.print("[");
    Serial.print( state );
    Serial.println( "] ");
    // Continue aqui a imprimir o que mais desejar para cada estado.
    // Não esqueça, o último print deve ser println para quebrar linha.
}

// ----------------------------------------------------------------
// Funções da máquina de estados.
// ----------------------------------------------------------------
void state1() {
    if( DEV_ENVIROMENT ) printSerialData("STATE1");
    if ( condicao ) {
        currentState = STATE2;
    }
}

void state2() {
    if( DEV_ENVIROMENT ) printSerialData("STATE2");
    if ( condicao ) {
        currentState = STATE1;
    }
}

// ----------------------------------------------------------------
// Setup (declaração dos pinos, inicialização das libs)
// ----------------------------------------------------------------
void setup() {
    // Nunca coloque um Serial.begin dentro de uma condicional que pode ser false!
    Serial.begin( BAUD_RATE );

    // Use DEV_ENVIROMENT para omitir prints. É como um "modo debug".
    if ( DEV_ENVIROMENT ) {
        Serial.println("Iniciando o programa...");
    }

    // Configuração dos pinos
    // Use INPUT para pinos que recebem um sinal de sensores
    // Use OUTPUT para enviar pulsos ou tensões. Usado em sensores, atuadores, leds, motores, etc.
    // Use INPUT_PULLUP para botões
    pinMode( PIN_SENSOR,    INPUT );
    pinMode( PIN_LED,       OUTPUT );
    pinMode( PIN_BUZZER,    OUTPUT );
    pinMode( PIN_BOTAO,     INPUT_PULLUP );

    // Sempre defina os estados iniciais dos pinos OUTPUT.
    digitalWrite( PIN_LED,      LOW );
    digitalWrite( PIN_BUZZER,   LOW );

    // Uso de funções definidas em utils.h
    beep( BEEP_DELAY );
}

// ----------------------------------------------------------------
// Loop principal
// ----------------------------------------------------------------
void loop() {
    // Primeiro, atualize a situação de todos os sensores.
    readSensors();
    // Agora chame o switch que controla a máquina de estados.
    switch( currentState ) {
        case STATE1:
            state1();
            break;
        case STATE2:
            state2();
            break;
        default:
            Serial.println("Erro: estado inexistente!");
    }
}

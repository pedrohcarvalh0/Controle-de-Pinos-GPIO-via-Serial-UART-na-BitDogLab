#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include "pico/bootrom.h"

// Definições das portas GPIO dos LEDs
#define GREEN_LED_PIN 11
#define BLUE_LED_PIN 12
#define RED_LED_PIN 13

// Definição da porta GPIO do BUZZER
#define BUZZER_PIN 21

// Prótótipos das funções
void init_leds_and_buzzer();
void activate_led(uint gpio);
void activate_all_leds();
void disable_all_leds();
void pwm_init_buzzer(uint pin);
void play_note(uint pin, uint frequency, uint duration_ms);
void activate_buzzer();
void trigger_command(char command);

void init_leds_and_buzzer() {

}

void activate_led(uint gpio) {

}

void activate_all_leds() {

}

void disable_all_leds() {
    
}

void pwm_init_buzzer(uint pin) {

}

void play_note(uint pin, uint frequency, uint duration_ms) {

}

void activate_buzzer() {

}

void trigger_command(char command) {

}

int main () {

    return 0;
}
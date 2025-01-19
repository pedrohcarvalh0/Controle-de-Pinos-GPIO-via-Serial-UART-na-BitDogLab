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
    if (frequency == 0) { // Pausa (silêncio)
        pwm_set_gpio_level(pin, 0);
        sleep_ms(duration_ms);
        return;
    }

    uint slice_num = pwm_gpio_to_slice_num(pin);

    // Configurar a frequência da nota
    uint32_t clock_div = clock_get_hz(clk_sys) / (frequency * 4096);
    pwm_set_clkdiv(slice_num, clock_div);
    pwm_set_wrap(slice_num, 4095);

    // Configurar o duty cycle para 50%
    pwm_set_gpio_level(pin, 2048);

    // Temporizar a duração da nota
    sleep_ms(duration_ms);

    // Silenciar o buzzer após a nota
    pwm_set_gpio_level(pin, 0);
    sleep_ms(50); // Pequena pausa entre notas
}

void activate_buzzer() {

}

void trigger_command(char command) {

}

int main () {

    return 0;
}
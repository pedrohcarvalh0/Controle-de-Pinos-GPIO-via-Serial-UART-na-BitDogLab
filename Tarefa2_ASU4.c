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
 
// Estrutura para representar uma nota musical 
typedef struct { 
    uint frequency;  // Frequência da nota (em Hz) 
    uint duration_ms; // Duração da nota (em milissegundos) 
} Note; 
 
// Melodia (notas e durações) 
Note melody[] = { 
    {262, 500},  // Dó (C4) 
    {294, 500},  // Ré (D4) 
    {330, 500},  // Mi (E4) 
    {349, 500},  // Fá (F4) 
    {392, 500},  // Sol (G4) 
    {440, 500},  // Lá (A4) 
    {494, 500},  // Si (B4) 
    {523, 500},  // Dó (C5) 
    {0, 500}     // Pausa 
}; 
 
// Número de notas na melodia 
int melody_length = sizeof(melody) / sizeof(Note); 
 
// Protótipos das funções 
void init_leds_and_buzzer(); 
void activate_led(uint gpio); 
void activate_all_leds(); 
void disable_all_leds(); 
void pwm_init_buzzer(uint pin); 
void play_note(uint pin, uint frequency, uint duration_ms); 
void activate_buzzer(); 
void trigger_command(char command); 
 
void init_leds_and_buzzer() { 
 
    gpio_init(RED_LED_PIN); 
    gpio_set_dir(RED_LED_PIN, GPIO_OUT); 
    gpio_put(RED_LED_PIN, false); 
 
    gpio_init(GREEN_LED_PIN); 
    gpio_set_dir(GREEN_LED_PIN, GPIO_OUT); 
    gpio_put(GREEN_LED_PIN, false); 
 
    gpio_init(BLUE_LED_PIN); 
    gpio_set_dir(BLUE_LED_PIN, GPIO_OUT); 
    gpio_put(BLUE_LED_PIN, false); 
 
    gpio_init(BUZZER_PIN); 
    gpio_set_dir(BUZZER_PIN, GPIO_OUT); 
    gpio_put(BUZZER_PIN, false); 
} 
 
void activate_led(uint gpio) { 
     
    disable_all_leds(); // Garante que apenas um LED esteja ligado 
    gpio_put(gpio, true); 
} 
 
void activate_all_leds() { 
     
    gpio_put(RED_LED_PIN, true); 
    gpio_put(GREEN_LED_PIN, true); 
    gpio_put(BLUE_LED_PIN, true); 
    printf("Todos os LEDs ativados\n"); 
} 
 
void disable_all_leds() { 
 
    gpio_put(RED_LED_PIN, false); 
    gpio_put(GREEN_LED_PIN, false); 
    gpio_put(BLUE_LED_PIN, false); 
} 
 
// Configuração do PWM no pino do buzzer 
void pwm_init_buzzer(uint pin) { 
    gpio_set_function(pin, GPIO_FUNC_PWM); 
    uint slice_num = pwm_gpio_to_slice_num(pin); 
    pwm_config config = pwm_get_default_config(); 
    pwm_init(slice_num, &config, true); 
    pwm_set_gpio_level(pin, 0); 
} 
  
// Função para tocar uma nota 
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
    printf("Tocando melodia...\n"); 
    pwm_init_buzzer(BUZZER_PIN); 
    for (int i = 0; i < melody_length; i++) { 
        play_note(BUZZER_PIN, melody[i].frequency, melody[i].duration_ms); 
    } 
    printf("Melodia concluída.\n"); 
} 
 
 
void trigger_command(char command) { 
    switch (command) { 
        case 'R': // Liga o LED vermelho 
            activate_led(RED_LED_PIN); 
            printf("LED vermelho ativado\n"); 
            break; 
        case 'G': // Liga o LED verde 
            activate_led(GREEN_LED_PIN); 
            printf("LED verde ativado\n"); 
            break; 
        case 'B': // Liga o LED azul 
            activate_led(BLUE_LED_PIN); 
            printf("LED azul ativado\n"); 
            break; 
        case 'W': // Liga todos os LEDs (luz branca) 
            activate_all_leds(); 
            break; 
        case 'O': // Desliga todos os LEDs 
            disable_all_leds(); 
            printf("Todos os LEDs desativados\n"); 
            break; 
        case 'Z': // Aciona o buzzer 
            activate_buzzer(); 
            break; 
        case 'X': // Reinicia o sistema 
            printf("Entrando no modo BOOTSEL. Aguarde...\n"); 
            sleep_ms(500); // Pequena pausa para garantir a saída do texto 
            reset_usb_boot(0, 0); // Reinicia no modo BOOTSEL 
            break; 
        default: 
            printf("Comando inválido: %c\n", command); 
            break; 
    } 
} 
 
int main () { 
    
    stdio_init_all(); 
    init_leds_and_buzzer(); 
 
    printf("Sistema iniciado. Aguardando comandos via UART...\n"); 
    printf("\nComandos disponíveis:\n"); 
    printf("R - Ativa o LED vermelho\n"); 
    printf("G - Ativa o LED verde\n"); 
    printf("B - Ativa o LED azul\n"); 
    printf("W - Ativa TODOS os LEDs\n"); 
    printf("Z - Ativa o BUZZER\n"); 
    printf("X - Reinicia o Sistema\n"); 
 
    while (true) { 
        int ch = getchar_timeout_us(1000000); // Aguarda entrada por 1 segundo 
        if (ch != PICO_ERROR_TIMEOUT) { 
            trigger_command((char)ch); 
        } 
    } 
    return 0; 
} 
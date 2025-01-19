# 🌟 Controle de LEDs e Buzzer com Raspberry Pi Pico 🌟

Este projeto permite controlar LEDs e um buzzer usando o Raspberry Pi Pico, com comandos enviados via UART. O sistema suporta efeitos visuais e sonoros, além de comandos para reinicializar o sistema.

---

## 👨‍💻 Desenvolvedores
- **Felipe Chaves Lacerda**
- **Gabriel Finotti Barros**  
- **Mariana Farias da Silva**  
- **Pablo Vinicius Rodrigues Barboza**  
- **Pedro Henrique Carvalho Felix**  
- **Ramon Leite Petitinga**

---

## 🛠️ Funcionalidades

1. **Controle de LEDs** 💡:
   - Acender LEDs individuais: vermelho, verde ou azul.
   - Acender todos os LEDs simultaneamente (luz branca).
   - Desligar todos os LEDs.

2. **Controle do Buzzer** 🎵:
   - Reproduz uma melodia composta de várias notas musicais.

3. **Reinicialização do Sistema** 🔄:
   - Reinicia o sistema em modo BOOTSEL para atualizar o firmware.

---

## 📋 Requisitos

```plaintext
🔧 Hardware:
- Raspberry Pi Pico.
- LEDs conectados aos pinos GPIO 11, 12 e 13.
- Buzzer conectado ao pino GPIO 21.
- Resistores adequados para proteger os LEDs.

💻 Software:
- SDK do Raspberry Pi Pico configurado.
- Compilador C compatível (como GCC).
- Ferramentas para upload do código para o Pico (como `picotool`).

```
---
## 🧩 Configuração do Hardware
```plaintext
1. Conecte os LEDs:
   - LED Verde no GPIO 11.
   - LED Azul no GPIO 12.
   - LED Vermelho no GPIO 13.
2. Conecte o Buzzer ao GPIO 21.
3. Certifique-se de utilizar resistores adequados para proteger os LEDs.

```
---
## 🚀 Compilação e Upload
```bash
1. Clone o repositório do código:
   git clone <URL_DO_REPOSITORIO>

2. Compile o programa usando CMake:
   mkdir build
   cd build
   cmake ..
   make

3. Envie o arquivo `.uf2` gerado para o Raspberry Pi Pico:
   - Mantenha o botão `BOOTSEL` pressionado enquanto conecta o Pico ao computador.
   - Copie o arquivo `.uf2` gerado para a unidade que será montada.
```
---
## 🎮 Comandos Disponíveis

Os comandos são enviados via UART. Veja a tabela abaixo:

| Comando | Descrição                    |
|---------|------------------------------|
| R       | Ativa o LED Vermelho 🔴       |
| G       | Ativa o LED Verde 🟢          |
| B       | Ativa o LED Azul 🔵           |
| W       | Ativa todos os LEDs (Branco) |
| O       | Desativa todos os LEDs       |
| Z       | Reproduz a melodia no Buzzer 🎵 |
| X       | Reinicia o sistema (BOOTSEL) 🔄 |
---
## 🎥 Demonstração
```plaintext
https://www.youtube.com/watch?v=--p8wdIPwyo
```

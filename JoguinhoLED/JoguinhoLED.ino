#include <Wire.h>
#include <LiquidCrystal_I2C.h> //https://github.com/johnrickman/LiquidCrystal_I2C

// Frequências das notas de Megalovania
int melody[] = {
  659, 659, 987, 493, 466, 440, 392, 659, 392, 440,
  587, 587, 987, 493, 466, 440, 392, 659, 392, 440,
  554, 554, 987, 493, 466, 440, 392, 659, 392, 440,
  523, 523, 987, 493, 466, 440, 392, 659, 392, 440,
  659, 659, 987, 493, 466, 440, 392, 659, 392, 440,
  587, 587, 987, 493, 466, 440, 392, 659, 392, 440,
  554, 554, 987, 493, 466, 440, 392, 659, 392, 440,
  523, 523, 987, 493, 466, 440, 392, 659, 392, 440,
  392, 392, 392, 392, 392, 392, 659, 659,
  392, 392, 392, 392, 440, 466, 440, 392, 659, 392, 440,
  392, 392, 392, 392, 440, 466, 493, 587, 493,
  987, 987, 987, 493, 987, 587,
  493, 493, 493, 493, 466, 440,
  493, 493, 493, 466, 493, 987, 493, 466,
  987, 493, 466, 440, 587, 493, 440, 392, 523, 587,
  392, 659, 392, 440, 466, 440, 392, 659, 392, 440,
  466, 493, 587, 493, 440, 392, 523, 587,
  392, 440, 493, 659, 587,
  493, 523, 587, 523, 659,
  659, 659, 987, 493, 466, 440, 392, 659, 392, 440
};

// Durações das notas em milissegundos
int noteDurations[] = {
  125, 125, 250, 125, 125, 125, 125, 125, 125, 250,
  125, 125, 250, 125, 125, 125, 125, 125, 125, 250,
  125, 125, 250, 125, 125, 125, 125, 125, 125, 250,
  125, 125, 250, 125, 125, 125, 125, 125, 125, 250,
  125, 125, 250, 125, 125, 125, 125, 125, 125, 250,
  125, 125, 250, 125, 125, 125, 125, 125, 125, 250,
  125, 125, 250, 125, 125, 125, 125, 125, 125, 250,
  125, 125, 250, 125, 125, 125, 125, 125, 125, 250,
  125, 125, 125, 125, 125, 125, 125, 250,
  125, 125, 125, 125, 125, 125, 125, 125, 125, 250,
  125, 125, 125, 125, 125, 125, 250, 125,
  250, 250, 250, 125, 250, 125,
  250, 250, 250, 125, 250, 125,
  125, 125, 125, 125, 125, 125, 125, 125,
  125, 125, 125, 125, 250, 125, 125, 125, 125, 250,
  125, 125, 125, 125, 125, 125, 125, 125, 250,
  125, 125, 125, 125, 125, 125, 125,
  125, 125, 125, 250, 125,
  125, 125, 125, 125, 125,
  125, 125, 250, 125, 125, 125, 125, 125, 125, 250
};

// Endereço I2C do LCD (pode variar; verifique o seu display específico)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Definições dos pinos dos LEDs em uma matriz 2x4
const int ledPins[2][4] = {
  {6, 7, 8, 9},
  {10, 11, 12, 13}
};

// Definições dos pinos do joystick
const int pinX = A1; // Pino analógico para o eixo horizontal
const int pinY = A0; // Pino analógico para o eixo vertical
const int pinSW = 2; // Pino digital para o botão (SW)

// Definição do pino do buzzer
const int buzzerPin = 5;

// Variáveis para manter a posição atual e objetivo do LED
int currentRow = 1;
int currentCol = 3;
int targetRow;
int targetCol;

// Variáveis para o jogo
int passos = 0;
unsigned long startTime;
bool gameActive = false;

// Função para configurar os pinos dos LEDs e do botão
void setup() {
  // Configurar pinos dos LEDs como saída
  for (int row = 0; row < 2; row++) {
    for (int col = 0; col < 4; col++) {
      pinMode(ledPins[row][col], OUTPUT);
      digitalWrite(ledPins[row][col], LOW); // Inicialmente desligar todos os LEDs
    }
  }

  // Configurar pino do botão como entrada com pull-up
  pinMode(pinSW, INPUT_PULLUP);

  // Configurar pino do buzzer como saída
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW); // Inicialmente desligar o buzzer

  // Inicializar comunicação serial
  Serial.begin(9600);

  // Inicializar o LCD
  lcd.init();
  lcd.backlight();

  // Mostrar mensagem inicial no LCD
  lcd.setCursor(0, 0);
  lcd.print("  Pronto para  ");
  lcd.setCursor(0, 1);
  lcd.print("    JOGAR!     ");
}

void tocarMegalovania() {
  for (int thisNote = 0; thisNote < sizeof(melody) / sizeof(melody[0]); thisNote++) {
    int noteDuration = noteDurations[thisNote];
    tone(buzzerPin, melody[thisNote], noteDuration);
    delay(noteDuration * 1.30); // Para garantir a separação entre as notas
  }
}

void iniciarJogo() {
  // Apagar todos os LEDs
  for (int row = 0; row < 2; row++) {
    for (int col = 0; col < 4; col++) {
      digitalWrite(ledPins[row][col], LOW);
    }
  }

  // Inicializar posição atual aleatoriamente
  currentRow = random(0, 2);
  currentCol = random(0, 4);
  digitalWrite(ledPins[currentRow][currentCol], HIGH);

  // Inicializar posição objetivo aleatoriamente
  do {
    targetRow = random(0, 2);
    targetCol = random(0, 4);
  } while (targetRow == currentRow && targetCol == currentCol);

  // Inicializar variáveis de jogo
  passos = 0;
  startTime = millis();
  gameActive = true;

  // Mostrar mensagem de início no LCD
  lcd.setCursor(0, 0);
  lcd.print("    VAI!      ");
  lcd.setCursor(0, 1);
  lcd.print("    VAI!      ");
}

void mostrarEstatisticas() {
  unsigned long timeTaken = millis() - startTime;

  // Mostrar pontuação no LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Segundos:" + String(timeTaken/1000) + "  ");
  lcd.setCursor(0, 1);
  lcd.print("Passos:" + String(passos) + "  ");

  // Tocar a melodia de Megalovania
  tocarMegalovania();

  // Resetar variáveis de jogo
  gameActive = false;
}

void piscarObjetivo() {
  if (gameActive) {
    digitalWrite(ledPins[targetRow][targetCol], LOW);
    delay(100);
    digitalWrite(ledPins[targetRow][targetCol], HIGH);
    delay(100);
  }
}

void loop() {
  int xValue = analogRead(pinX); // Ler o valor do eixo horizontal
  int yValue = analogRead(pinY); // Ler o valor do eixo vertical
  int swState = digitalRead(pinSW); // Ler o estado do botão

  if (swState == LOW && !gameActive) {
    iniciarJogo();
    delay(150); // Pequeno atraso para evitar múltiplas detecções do botão
  }

  if (gameActive) {
    // Verificar movimento do joystick para frente e para trás (eixo Y)
    if (yValue > 800) { // Movimento para a frente
      digitalWrite(ledPins[currentRow][currentCol], LOW);
      currentRow = (currentRow + 1) % 2;
      digitalWrite(ledPins[currentRow][currentCol], HIGH);
      passos++;
      delay(50);
    } else if (yValue < 200) { // Movimento para trás
      digitalWrite(ledPins[currentRow][currentCol], LOW);
      currentRow = (currentRow - 1 + 2) % 2;
      digitalWrite(ledPins[currentRow][currentCol], HIGH);
      passos++;
      delay(50);
    } else if (xValue > 600) { // Movimento para a direita
      digitalWrite(ledPins[currentRow][currentCol], LOW);
      currentCol = (currentCol + 1) % 4;
      digitalWrite(ledPins[currentRow][currentCol], HIGH);
      passos++;
      delay(50);
    } else if (xValue < 350) { // Movimento para a esquerda
      digitalWrite(ledPins[currentRow][currentCol], LOW);
      currentCol = (currentCol - 1 + 4) % 4;
      digitalWrite(ledPins[currentRow][currentCol], HIGH);
      passos++;
      delay(50);
    }

    // Verificar se o jogador alcançou o objetivo
    if (currentRow == targetRow && currentCol == targetCol) {
      mostrarEstatisticas();
    }

    // Piscar o LED objetivo
    piscarObjetivo();
  }
}

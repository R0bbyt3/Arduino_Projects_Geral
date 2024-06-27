

#include <Keypad.h>

// Definição das linhas e colunas do keypad
const byte ROWS = 4; // quatro linhas
const byte COLS = 4; // quatro colunas

// Definição dos pinos das linhas e colunas
byte rowPins[ROWS] = {9, 8, 7, 6}; // Conecte às linhas do keypad (R1, R2, R3, R4)
byte colPins[COLS] = {5, 4, 3, 2}; // Conecte às colunas do keypad (C1, C2, C3, C4)

// Definição dos caracteres mapeados para cada botão
char keys[ROWS][COLS] = {
  {'*', '0', '#', 'D'},
  {'7', '8', '9', 'C'},
  {'4', '5', '6', 'B'},
  {'1', '2', '3', 'A'}
};

// Inicialização do keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Definição das notas
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST 0

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    Serial.print("Tecla pressionada: ");
    Serial.println(key);
    handleKeyPress(key);
  }
}

void handleKeyPress(char key) {
  switch (key) {
    case '1':
      Serial.println("Posição: S1");
      tone(13, NOTE_E5);
      break;
    case '2':
      Serial.println("Posição: S2");
      tone(13, NOTE_E6);
      break;
    case '3':
      Serial.println("Posição: S3");
      tone(13, NOTE_B5);
      break;
    case 'A':
      Serial.println("Posição: S4");
      tone(13, NOTE_AS5);
      break;
    case '4':
      Serial.println("Posição: S5");
      tone(13, NOTE_A5);
      break;
    case '5':
      Serial.println("Posição: S6");
      tone(13, NOTE_G5);
      break;
    case '6':
      Serial.println("Posição: S7");
      tone(13, NOTE_D5);
      break;
    case 'B':
      Serial.println("Posição: S8");
      tone(13, NOTE_CS5);
      break;
    case '7':
      Serial.println("Posição: S9");
      tone(13, NOTE_C5);
      break;
    case '8':
      Serial.println("Posição: S10");
      tone(13, NOTE_FS5);
      break;
    case '9':
      Serial.println("Posição: S11");
      tone(13, NOTE_E6);
      break;
    case 'C':
      Serial.println("Posição: S12");
      tone(13, NOTE_B5);
      break;
    case '*':
      Serial.println("Posição: S13");
      tone(13, NOTE_AS5);
      break;
    case '0':
      Serial.println("Posição: S14");
      tone(13, NOTE_A5);
      break;
    case '#':
      Serial.println("Posição: S15");
      tone(13, NOTE_G5);
      break;
    case 'D':
      Serial.println("Posição: S16");
      tone(13, NOTE_D5);
      break;
    default:
      noTone(13);
      break;
  }
  delay(100); // Delay para evitar múltiplos toques
  noTone(13); // Parar o tom
}

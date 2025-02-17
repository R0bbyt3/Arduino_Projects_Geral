// Definição dos pinos
const int buzzerPin = 4;
const int buttonPin = 7;
const int xAxisPin = A1;
const int yAxisPin = A0;

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
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  int xValue = analogRead(xAxisPin);
  int yValue = analogRead(yAxisPin);
  int buttonState = digitalRead(buttonPin);

  // Imprimir valores lidos
  Serial.print("X: ");
  Serial.print(xValue);
  Serial.print(" Y: ");
  Serial.print(yValue);
  Serial.print(" Button: ");
  Serial.println(buttonState);
  

    // Norte (Cima)
    if (yValue < 200 && xValue > 400 && xValue < 600) {
      Serial.println("Direção: Norte - Nota: Mi (E5)");
      tone(buzzerPin, NOTE_E5);
    }
    // Sul (Baixo)
    else if (yValue > 800 && xValue > 400 && xValue < 600) {
      Serial.println("Direção: Sul - Nota: Lá# (A#5)");
      tone(buzzerPin, NOTE_AS5);
    }
    // Leste (Direita)
    else if (xValue > 800 && yValue > 400 && yValue < 600) {
      Serial.println("Direção: Leste - Nota: Ré (D5)");
      tone(buzzerPin, NOTE_D5);
    }
    // Oeste (Esquerda)
    else if (xValue < 200 && yValue > 400 && yValue < 600) {
      Serial.println("Direção: Oeste - Nota: Dó# (C#5)");
      tone(buzzerPin, NOTE_CS5);
    }
    // Nordeste (Cima Direita)
    else if (xValue > 800 && yValue < 200) {
      Serial.println("Direção: Nordeste - Nota: MI (E6)");
      tone(buzzerPin, NOTE_E6);
    }
    // Noroeste (Cima Esquerda)
    else if (xValue < 200 && yValue < 200) {
      Serial.println("Direção: Noroeste - Nota: Si (B5)");
      tone(buzzerPin, NOTE_B5);
    }
    // Sudeste (Baixo Direita)
    else if (xValue > 800 && yValue > 800) {
      Serial.println("Direção: Sudeste - Nota: Lá (A5)");
      tone(buzzerPin, NOTE_A5);
    }
    // Sudoeste (Baixo Esquerda)
    else if (xValue < 200 && yValue > 800) {
      Serial.println("Direção: Sudoeste - Nota: Sol (G5)");
      tone(buzzerPin, NOTE_G5);
    } else {
      noTone(buzzerPin);
    }


  delay(100); // Pequeno delay para evitar leituras repetidas muito rápidas
}

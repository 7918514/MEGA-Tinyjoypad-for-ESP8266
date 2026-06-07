#include "pitches.h"  // Подключаем файл с мелодиями
#include <U8g2lib.h>  // Библиотека для OLED https://github.com/olikraus/u8g2

// Инициализация OLED (SH1106, I2C, 128x64)
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// Пины
#define BUZZER_PIN  15  // D8 — BUZZER
#define BUTTON_PIN  0   // D3 — кнопка

// Переменные
int currentMelody = 0;            // Текущая мелодия (0, 1, 2, 3)
int lastButtonState = HIGH;       // Предыдущее состояние кнопки
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50; // Задержка антидребезга
bool isPlaying = false;           // Флаг воспроизведения

// Названия мелодий для отображения на OLED
const char* melodyNames[] = {
  "Yolka",
  "Twinkle",
  "Jingle Bells",
  "Star Wars"
};

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);

  // Инициализация OLED
  u8g2.begin();
  u8g2.setFont(u8g2_font_helvR14_tr);  // Шрифт

  Serial.begin(115200);
  Serial.println("");
  Serial.println("Система готова. Нажмите кнопку для смены мелодии.");

  // Отображение начального экрана
  displayStartupScreen();
}

void loop() {
  // Проверяем кнопку только если не воспроизводим мелодию
  if (!isPlaying && (millis() - lastDebounceTime) > debounceDelay) {
    int reading = digitalRead(BUTTON_PIN);

    if (reading == LOW) { // Кнопка нажата
      lastDebounceTime = millis();
      currentMelody = (currentMelody + 1) % 4;
      Serial.print("Выбрана мелодия №");
      Serial.println(currentMelody + 1);

      // Отображение названия выбранной мелодии
      displayMelodyName(melodyNames[currentMelody]);

      playMelody(currentMelody); // Воспроизводим новую мелодию
    }
  }
}

// Функция проверки кнопки (не прерывает воспроизведение)
void checkButton() {
  int reading = digitalRead(BUTTON_PIN);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  lastButtonState = reading;
}

// Функция воспроизведения мелодии
void playMelody(int melodyNum) {
  const int* melody;
  const int* noteDurations;
  int numNotes;

  isPlaying = true; // Устанавливаем флаг воспроизведения

  // Выбираем нужную мелодию
  switch (melodyNum) {
    case 0:
      melody = melody1;
      noteDurations = noteDurations1;
      numNotes = melody1Length;
      break;
    case 1:
      melody = melody2;
      noteDurations = noteDurations2;
      numNotes = melody2Length;
      break;
    case 2:
      melody = melody3;
      noteDurations = noteDurations3;
      numNotes = melody3Length;
      break;
    case 3:
      melody = melody4;
      noteDurations = noteDurations4;
      numNotes = melody4Length;
      break;
  }

  // Воспроизведение
  for (int thisNote = 0; thisNote < numNotes; thisNote++) {
    // Проверяем кнопку во время паузы между нотами (для антидребезга)
    checkButton();

    int noteDuration = 1000 / noteDurations[thisNote];

    // Считываем ноту из flash‑памяти
    int currentNote = pgm_read_word(&melody[thisNote]);

    if (currentNote == NOTE_REST) {
      noTone(BUZZER_PIN);
    } else {
      tone(BUZZER_PIN, currentNote, noteDuration);
    }

    delay(noteDuration * 1.3); // Пауза между нотами
    noTone(BUZZER_PIN);        // Отключаем звук
  }

  isPlaying = false;    // Сбрасываем флаг после завершения
  displayReadyScreen(); // Отображаем экран готовности
}

// Отображение экрана готовности
void displayReadyScreen() {
  u8g2.clearBuffer();
  u8g2.setCursor(0, 20);
  u8g2.print("Ready");
  u8g2.setCursor(0, 40);
  u8g2.print("Press button A");
  u8g2.sendBuffer();
}

// Отображение названия текущей мелодии
void displayMelodyName(const char* name) {
  u8g2.clearBuffer();
  u8g2.setCursor(0, 20);
  u8g2.print("Playing:");
  u8g2.setCursor(0, 40);
  u8g2.print(name);
  u8g2.sendBuffer();
}

// Начальный экран при запуске
void displayStartupScreen() {
  u8g2.clearBuffer();
  u8g2.setCursor(0, 32);
  u8g2.print("Melody Player");
  u8g2.sendBuffer();
  delay(1500); // Показываем 1,5 секунды
  displayReadyScreen();
}

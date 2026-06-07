// pitches.h — определения нот и мелодий

// Ноты (частота в Гц)
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_D5  587
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_REST 0

// Мелодия 1: «В лесу родилась ёлочка»
const int melody1[] PROGMEM = {
  NOTE_E4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4,
  NOTE_C4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4,
  NOTE_E4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4,
  NOTE_C4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_D4, NOTE_C4
};
const int noteDurations1[] PROGMEM = {4,4,8,8,4,8,8,4, 4,4,8,8,3,8,4, 4,4,8,8,4,8,8,4, 4,4,8,8,2,2};
const int melody1Length = 30;

// Мелодия 2: «Twinkle Twinkle Little Star»
const int melody2[] PROGMEM = {
  NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4,
  NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4,
  NOTE_G4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4,
  NOTE_G4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4,
  NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4,
  NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4
};
const int noteDurations2[] PROGMEM = {4,4,4,4,4,4,2, 4,4,4,4,4,4,2, 4,4,4,4,4,4,2, 4,4,4,4,4,4,2, 4,4,4,4,4,4,2, 4,4,4,4,4,4,2};
const int melody2Length = 42;

// Мелодия 3: «Jingle Bells»
const int melody3[] PROGMEM = {
  NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4,
  NOTE_G4, NOTE_C4, NOTE_D4, NOTE_E4,
  NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4,
  NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_D4, NOTE_G4
};
const int noteDurations3[] PROGMEM = {8,8,8,8,8,8,4, 8,8,8,4, 8,8,8,8,4, 8,8,8,8,8,8,4,4};
const int melody3Length = 29;

// Мелодия 4: «Звёздные войны» (Main Theme)
const int melody4[] PROGMEM = {
  NOTE_A4, NOTE_REST, NOTE_A4, NOTE_REST, NOTE_A4, NOTE_REST,
  NOTE_F4, NOTE_REST, NOTE_C5, NOTE_REST,
  NOTE_A4, NOTE_REST, NOTE_F4, NOTE_REST, NOTE_C5, NOTE_REST,
  NOTE_A4, NOTE_REST,
  NOTE_E5, NOTE_REST, NOTE_E5, NOTE_REST, NOTE_E5, NOTE_REST,
  NOTE_F5, NOTE_REST, NOTE_C5, NOTE_REST,
  NOTE_A4, NOTE_REST, NOTE_F4, NOTE_REST, NOTE_C5, NOTE_REST,
  NOTE_A4, NOTE_REST
};
const int noteDurations4[] PROGMEM = {
  2, 8, 2, 8, 2, 8,
  4, 8, 4, 8,
  2, 8, 4, 8, 4, 8,
  2, 8,
  2, 8, 2, 8, 2, 8,
  4, 8, 4, 8,
  2, 8, 4, 8, 4, 8,
  2, 8
};
const int melody4Length = 32;

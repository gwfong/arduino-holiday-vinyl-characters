#define PIN_LED_BTN_YEL 12
#define PIN_LED_BTN_GRN 11
#define PIN_LED_BTN_RED 10
#define PIN_LED_NOSE 9
#define PIN_LED_HOLLY_1 7
#define PIN_LED_HOLLY_2 6
#define PIN_LED_HOLLY_3 5

int currLeds = 0;

#define PIN_PIEZO 3
#define REST_BEAT 1.0
#define TEMPO 200.0
#define HALF_TEMPO (TEMPO / 2.0)

#define YEL  (B0000001)
#define GRN  (B0000010)
#define RED  (B0000100)
#define NOSE (B0001000)
#define HLY1 (B0010000)
#define HLY2 (B0100000)
#define HLY3 (B1000000)
#define BTNS (B0000111)
#define HLYS (B1110000)
#define ALL_OFF  (B0000000)
#define ALL_ON   (B1111111)

typedef struct Effect {
  char note;
  float beat;
  int ledPinMask;
} Effect;

Effect effects[] = {
  {'g', 3.0, NOSE}, {'e', 1.0, YEL}, {'f', 1.0, GRN}, {'g', 1.0, RED}, {'C', 2.0, BTNS}, {'b', .25, HLY1}, {'C', .25, HLY2},
  {'D', 1.0, HLY3}, {'C', 1.0, YEL}, {'b', 1.0, GRN}, {'a', 1.0, RED}, {'g', 3.0, ALL_ON}, {'R', REST_BEAT, ALL_OFF},

  {'b', .25, YEL|GRN}, {'C', .25, GRN|RED}, {'D', 1.0, YEL|RED}, {'C', 1.0, YEL|HLY1}, {'b', 1.0, GRN|HLY2}, {'a', .25, RED|HLY3}, {'a', .25, HLYS},
  {'g', 1.0, YEL|RED}, {'C', 1.0, YEL|GRN}, {'e', 1.0, GRN|RED}, {'g', .25, BTNS}, {'a', .25, YEL|HLY1}, {'g', 1.0, GRN|HLY2}, {'f', 1.0, RED|HLY3},
  {'e', 1.0, HLYS}, {'f', 1.0, BTNS}, {'g', 3.0, ALL_ON}, {'R', REST_BEAT, ALL_OFF},

  {'g', 3.0, NOSE}, {'e', 1.0, YEL}, {'f', 1.0, GRN}, {'g', 1.0, RED}, {'C', 2.0, BTNS}, {'b', .25, HLY1}, {'C', .25, HLY2},
  {'D', 1.0, HLY3}, {'C', 1.0, YEL}, {'b', 1.0, GRN}, {'a', 1.0, RED}, {'g', 3.0, ALL_ON}, {'R', REST_BEAT, ALL_OFF},

  {'b', .25, YEL|GRN}, {'C', .25, GRN|RED}, {'D', 1.0, YEL|RED}, {'C', 1.0, YEL|HLY1}, {'b', 1.0, GRN|HLY2}, {'a', .25, RED|HLY3}, {'a', .25, HLYS},
  {'g', 1.0, YEL|RED}, {'C', 1.0, YEL|GRN}, {'e', 1.0, GRN|RED}, {'g', .25, BTNS}, {'a', .25, YEL|HLY1}, {'g', 1.0, GRN|HLY2}, {'f', 1.0, RED|HLY3},
  {'e', 1.0, HLYS}, {'d', 1.0, BTNS}, {'c', 3.0, ALL_ON}, {'R', REST_BEAT, ALL_OFF},

  {'c', 1.0, NOSE}, {'a', 1.0, YEL}, {'a', 1.0, GRN}, {'C', 1.0, RED}, {'C', 1.0, HLY1}, {'b', 1.0, HLY2}, {'a', 1.0, HLY3},
  {'g', 1.0, YEL|HLY1}, {'e', 1.0, GRN|HLY2}, {'f', 1.0, RED|HLY3}, {'a', 1.0, YEL|GRN|HLY1}, {'g', 1.0, GRN|RED|HLY2}, {'f', 1.0, YEL|RED|HLY3}, {'e', 3.0, ALL_ON},
  {'R', REST_BEAT, ALL_OFF},

  {'e', 1.0, YEL|HLY1}, {'d', 1.0, GRN|HLY2}, {'d', 1.0, RED|HLY3}, {'g', 1.0, YEL}, {'g', 1.0, GRN}, {'b', 1.0, RED}, {'b', 1.0, HLY1},
  {'D', 1.0, HLY2}, {'b', .25, HLY3}, {'b', .25, YEL|HLY2}, {'D', 1.0, GRN|HLY3}, {'C', 1.0, RED|HLY1}, {'b', 1.0, YEL|GRN}, {'a', 1.0, GRN|RED},
  {'g', 3.0, BTNS|NOSE},

  {'g', 3.0, HLYS|NOSE},

  {'g', 3.0, NOSE}, {'e', 1.0, YEL}, {'f', 1.0, GRN}, {'g', 1.0, RED}, {'C', 3.0, BTNS},
  {'b', .25, HLY1}, {'C', .25, HLY2}, {'D', 1.0, HLY3}, {'C', 1.0, YEL}, {'b', 1.0, GRN}, {'a', 1.0, RED}, {'g', 3.0, ALL_ON},
  {'R', REST_BEAT, ALL_OFF},

  {'b', .25, YEL|GRN}, {'C', .25, GRN|RED}, {'D', 1.0, YEL|RED}, {'C', 1.0, BTNS}, {'b', 1.0, HLY1|HLY2}, {'a', .25, HLY2|HLY3}, {'a', .25, HLY1|HLY3},
  {'g', 1.0, HLYS}, {'C', 1.0, YEL}, {'e', 1.0, GRN}, {'g', .25, RED}, {'a', .25, BTNS}, {'g', 1.0, HLY1}, {'f', 1.0, HLY2},
  {'e', 1.0, HLY3}, {'d', 1.0, HLYS}, {'c', 3.0, ALL_ON}, {'R', REST_BEAT, ALL_OFF}
};
int numEffects = sizeof(effects) / sizeof(Effect);

int ledPins[] = {
  PIN_LED_BTN_YEL, PIN_LED_BTN_GRN, PIN_LED_BTN_RED, PIN_LED_NOSE, PIN_LED_HOLLY_1, PIN_LED_HOLLY_2, PIN_LED_HOLLY_3
};
int numLedPins = sizeof(ledPins) / sizeof(int);

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < numLedPins; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  pinMode(PIN_PIEZO, OUTPUT);
}

void loop() {

  for (int i = 0; i < numEffects; i++) {
    Effect& effect = effects[i];
    displayLedEffect(effect.ledPinMask);
    playSoundEffect(effect);
  }

  delay(1000);
}

void displayLedEffect(int ledPinMask) {
  for (int i = 0; i < numLedPins; i++) {
    if ((ledPinMask & (1 << i)) > 0) {
      digitalWrite(ledPins[i], HIGH);
    } else {
      digitalWrite(ledPins[i], LOW);
    }
  }
}

void playSoundEffect(Effect& pEffect) {
    if (pEffect.note == 'R') {
      delay(pEffect.beat * TEMPO);
    } else {
      float duration = pEffect.beat * TEMPO;
      playNote(pEffect.note, duration);
    }
    delay(HALF_TEMPO);
}

void playNote(char note, float duration) {
  static char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C', 'D'};
  static int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956, 925 };
  static int numNames = sizeof(names) / sizeof(char);

  Serial.println(note);
      
  // play the tone corresponding to the note name
  for (int i = 0; i < numNames; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}

void playTone(int tone, float duration) {

  long d = long(duration * 1000.0f);
  
  for (long i = 0; i < d; i += tone * 2) {
    digitalWrite(PIN_PIEZO, HIGH);
    delayMicroseconds(tone);
    digitalWrite(PIN_PIEZO, LOW);
    delayMicroseconds(tone);
  }
}

void writeToAllLeds(int val) {
  for (int i = 0; i < numLedPins; i++) {
    digitalWrite(ledPins[i], val);
  }
}



#include <Adafruit_NeoPixel.h>

// Tasten-Pins
#define buttonHelligkeit_hoch 32
#define buttonHelligkeit_runter 33
#define buttonFarbwechsel 25
#define buttonOnOff 26
#define buttonMode 21

// LED-Strip
#define LED_PIN    18
#define NUM_LEDS   40

// Timer
unsigned long previousMillis = 0;
const long interval = 100;  // Intervall für Effekte
int currentLED = 0;
int pulseBrightness = 0;
int pulseStep = 5;  // Schrittweite fürs Pulsieren

// Zustände
int brightness = 100;
bool ledsOn = true;
int colorIndex = 0;
int mode = 0; // 0 = Lauflicht, 1 = alle an, 2 = pulsierend

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// Farben zur Auswahl
uint32_t colors[] = {
  strip.Color(0, 150, 255),   // Blau
  strip.Color(255, 0, 0),     // Rot
  strip.Color(0, 255, 0),     // Grün
  strip.Color(255, 255, 0),   // Gelb
  strip.Color(255, 255, 255)  // Weiß
};
const int numColors = sizeof(colors) / sizeof(colors[0]);

void setup() {
  Serial.begin(9600);

  pinMode(buttonHelligkeit_hoch, INPUT_PULLUP);
  pinMode(buttonHelligkeit_runter, INPUT_PULLUP);
  pinMode(buttonFarbwechsel, INPUT_PULLUP);
  pinMode(buttonOnOff, INPUT_PULLUP);
  pinMode(buttonMode, INPUT_PULLUP);

  strip.begin();
  strip.setBrightness(brightness);
  strip.show();
}

void loop() {
  unsigned long currentMillis = millis();

  if (ledsOn) {
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;

      switch (mode) {
        case 0: // Lauflicht
          strip.clear();
          strip.setPixelColor(currentLED, colors[colorIndex]);
          strip.show();
          currentLED = (currentLED + 1) % NUM_LEDS;
          break;

        case 1: // Alle an (statisch)
          for (int i = 0; i < NUM_LEDS; i++) {
            strip.setPixelColor(i, colors[colorIndex]);
          }
          strip.show();
          break;

        case 2: // Pulsierender Effekt
          pulseBrightness += pulseStep;
          if (pulseBrightness >= brightness || pulseBrightness <= 0) {
            pulseStep = -pulseStep; // Richtung umkehren
            pulseBrightness = constrain(pulseBrightness, 0, brightness);
          }

          strip.clear();
          for (int i = 0; i < NUM_LEDS; i++) {
            uint32_t color = colors[colorIndex];
            uint8_t r = (uint8_t)((color >> 16) & 0xFF);
            uint8_t g = (uint8_t)((color >> 8) & 0xFF);
            uint8_t b = (uint8_t)(color & 0xFF);
            strip.setPixelColor(i, strip.Color(
              (r * pulseBrightness) / 255,
              (g * pulseBrightness) / 255,
              (b * pulseBrightness) / 255
            ));
          }
          strip.show();
          break;
      }
    }
  }

  // --- Tastenabfragen ---

  // Helligkeit erhöhen
  if (digitalRead(buttonHelligkeit_hoch) == LOW) {
    brightness = min(255, brightness + 20);
    strip.setBrightness(brightness);
    strip.show();
    delay(200);
  }

  // Helligkeit verringern
  if (digitalRead(buttonHelligkeit_runter) == LOW) {
    brightness = max(0, brightness - 20);
    strip.setBrightness(brightness);
    strip.show();
    delay(200);
  }

  // Farbe wechseln
  if (digitalRead(buttonFarbwechsel) == LOW) {
    colorIndex = (colorIndex + 1) % numColors;
    delay(200);
  }

  // LEDs ein/aus
  if (digitalRead(buttonOnOff) == LOW) {
    ledsOn = !ledsOn;
    strip.clear();
    strip.show();
    delay(200);
  }

  // Modus wechseln
  if (digitalRead(buttonMode) == LOW) {
    mode = (mode + 1) % 3; // 0 → 1 → 2 → 0 ...
    strip.clear();
    strip.show();
    delay(200);
  }
}

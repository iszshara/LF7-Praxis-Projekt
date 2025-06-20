# Projektname: LED-Modi-Steuerung mit ESP32

## Autoren
- Luis Rennert
- Lucas Kloss

---

## Projektbeschreibung

Dieses Projekt steuert einen adressierbaren LED-Strip (z. B. WS2812B) mit 
einem ESP32 über fünf physische Taster. Über die Tasten lassen sich 
Helligkeit, Farbe, Leuchtmodus und der Ein/Aus-Zustand steuern. 
Es stehen drei Leuchtmodi zur Verfügung:

1. **Lauflicht**: eine LED bewegt sich über den Strip
2. **Alle LEDs an**: alle LEDs leuchten statisch in einer wählbaren Farbe
3. **Pulsierender Modus**: LEDs leuchten alle gleichzeitig und atmen langsam von dunkel zu hell

---

## 🎛Steuerung

| Taste                 | Funktion                         |
|----------------------|----------------------------------|
| `GPIO 32`            | Helligkeit erhöhen               |
| `GPIO 33`            | Helligkeit verringern            |
| `GPIO 25`            | Farbwechsel                      |
| `GPIO 26`            | LEDs ein-/ausschalten            |
| `GPIO 21`            | Leuchtmodus umschalten           |

---

## Hardwareanforderungen

- ESP32-Board (z. B. DevKit)
- Adafruit NeoPixel-kompatibler LED-Strip (WS2812B, APA106 etc.)
- 5x Taster
- Externe 5 V-Stromversorgung (bei längeren LED-Strips empfohlen)

---

## Pinbelegung

| Funktion       | GPIO |
|----------------|------|
| LED-Datenpin   | 18   |
| Taster Helligkeit hoch | 32 |
| Taster Helligkeit runter | 33 |
| Taster Farbwechsel | 25 |
| Taster An/Aus | 26 |
| Taster Moduswechsel | 21 |

---

## Abhängigkeiten

- Arduino IDE oder PlatformIO
- Bibliothek: [Adafruit NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel)

---

## Upload-Anleitung

1. Board: **ESP32 Dev Module**
2. Bibliothek installieren: Adafruit NeoPixel
3. Sketch hochladen
4. Hardware anschließen, Taster testen

---

## Ideen für zukünftige Erweiterungen

- An/Aus Steuerung über Bewegungssensor
- App zur Steuerung entwickeln
- Prototypen umsetzen als reelle Ringlampe
- mehrere Farbmodi (z.B. Lagerfeuer) hinzufügen
- eigene Farben mischen

## Bisheriger Aufbau

![image](https://github.com/user-attachments/assets/58a4455e-2fc0-487c-b0f9-ce8333a37fc1)


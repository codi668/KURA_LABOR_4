#include <Arduino.h>
#include <math.h>

// Definiere den DAC-Pin (hier GPIO25)
const int dacPin = 25; // Kann auch auf 26 gesetzt werden

// Parameter für die Sinuswelle
const float frequency = 1.0;    // Frequenz der Sinuswelle in Hz
const int amplitude = 255;      // Amplitude der Sinuswelle (0-255 für 8-Bit DAC)
const int offset = 128;         // Offset, um die Welle in den positiven Bereich zu verschieben
const float samplingRate = 1000; // Abtastrate in Hz

// Variablen für die Zeit
unsigned long lastTime = 0;
float time = 0;

void setup() {
  // Setze den DAC-Pin auf Output
  pinMode(dacPin, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  
  // Berechne den Sinuswert
  if (currentMillis - lastTime >= (1000 / samplingRate)) {
    lastTime = currentMillis;
    
    // Berechne den Sinuswert und skaliere ihn auf den Bereich [0, 255]
    float sineValue = amplitude * sin(2 * PI * frequency * time) + offset;
    
    // Ausgabe des Sinuswerts auf den DAC
    dacWrite(dacPin, (int)sineValue);

    // Erhöhe die Zeit für den nächsten Zyklus
    time += 1.0 / samplingRate;
  }
}

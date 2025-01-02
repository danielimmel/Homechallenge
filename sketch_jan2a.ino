#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
// Display-Abmessungen
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
 
// OLED-Reset-Pin (nicht verwendet, daher -1)
 
#define OLED_RESET -1
 
// OLED-Objekt erstellen
Adafruit_SSD1306 display
(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
 
 
// Funktion, um einen Smiley zu zeichnen
void drawSmiley(bool wink) {
  display.clearDisplay();
 
  // Mittelpunkt des Displays
  int centerX = SCREEN_WIDTH / 2;
  int centerY = SCREEN_HEIGHT / 2 + 5; // Verschiebe den Mittelpunkt leicht nach unten
 
  int radius = 20; // Radius des Smileys
 
  // Kreis für das Gesicht
  display.drawCircle(centerX, centerY, radius, SSD1306_WHITE);
 
  // Augen
  display.fillCircle(centerX - 7, centerY - 7, 2, SSD1306_WHITE); // Linkes Auge
  if (wink) {
    display.drawLine(centerX + 4, centerY - 7, centerX + 10, centerY - 7, SSD1306_WHITE); // Rechtes zwinkerndes Auge
  } else {
    display.fillCircle(centerX + 7, centerY - 7, 2, SSD1306_WHITE); // Rechtes Auge
  }
 
  // Mund (höher positioniert)
  for (int x = -15; x <= 15; x++) {
    int y = (int)(0.3 * (15 * 15 - x * x) / 15); // Umgedrehte Parabel für nach unten gebogenen Mund
    display.drawPixel(centerX + x, centerY + 6 + y, SSD1306_WHITE); // Mund höher positioniert
  }
 
  display.display();
}
 
void setup() {
  // Serieller Monitor für Debugging
  Serial.begin(115200);
 
  // Display initialisieren
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Ändere die Adresse zu 0x3D, falls nötig
    Serial.println(F("OLED nicht gefunden!"));
    while (true); // Endlosschleife, wenn kein Display erkannt wird
  }
 
  display.clearDisplay(); // Display löschen
}
 
void loop() {
  // Lächelnden Smiley anzeigen
  drawSmiley(false);
  delay(1000); // 1 Sekunde warten
 
  // Zwinkernden Smiley anzeigen
  drawSmiley(true);
  delay(1000); // 1 Sekunde warten
}
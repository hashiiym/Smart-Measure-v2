#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET    -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define TRIG_PIN 5
#define ECHO_PIN 18
#define SOUND_SPEED 0.0343

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("OLED initialization failed! Check I2C wiring."));
    for(;;);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(15, 12);
  display.print("SMART MEASURE v2");
  display.display();
  delay(2000); 
}

void loop() {
  float distanceCm = getStableDistance();

  if (distanceCm == -1) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 10);
    display.print("Reading Error...");
    display.display();
    delay(200);
    return;
  }

  float distanceMeters = distanceCm / 100.0;
  float distanceInches = distanceCm * 0.393701;

  display.clearDisplay();
  
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Distance:");

  display.setTextSize(2);
  display.setCursor(0, 14);
  display.print(distanceMeters, 2); 
  display.print("m");

  display.setTextSize(1);
  display.setCursor(75, 14);
  display.print(distanceInches, 1); 
  display.setCursor(75, 24);
  display.print("inches");

  display.display();
  delay(300); 
}

float getStableDistance() {
  float total = 0;
  int validReadings = 0;

  for (int i = 0; i < 5; i++) {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    long duration = pulseIn(ECHO_PIN, HIGH, 30000); 

    if (duration > 0) { 
      float dist = (duration * SOUND_SPEED) / 2;
      
      if (dist > 2 && dist < 400) { 
        total += dist;
        validReadings++;
      }
    }
    delay(10); 
  }

  if (validReadings > 0) {
    return total / validReadings;
  } else {
    return -1;
  }
}
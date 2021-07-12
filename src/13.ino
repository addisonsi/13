#include "oled-wing-adafruit.h"
SYSTEM_THREAD(ENABLED);
SYSTEM_MODE(MANUAL);
bool runInterrupt = false;
OledWingAdafruit display;
volatile int count = 0;
void isr() { 
  count++;
}
void setup() {
  pinMode(D6, INPUT_PULLUP);
  pinMode(D5, INPUT_PULLUP);
  attachInterrupt(D6, isr, FALLING);
  display.setup();
  display.clearDisplay();
  display.display(); // cause the display to be updated

}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  display.clearDisplay();
  display.loop();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  if(!runInterrupt){
    noInterrupts();
  }
  else{
    interrupts();
  }
  if(!digitalRead(D6)){
    runInterrupt = !runInterrupt;
  }
  display.print("Count: ");
  display.print(count);
  display.display();
  }
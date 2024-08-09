#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Constants
const int HALL_SENSOR_PIN = 2;
const unsigned long UPDATE_INTERVAL = 1000; // Update interval in milliseconds
const int LCD_ADDRESS = 0x3F;
const int LCD_COLUMNS = 16;
const int LCD_ROWS = 2;

// Global variables
volatile unsigned long pulseCount = 0;
unsigned long lastUpdateTime = 0;
float rpm = 0;

// LCD object
LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

// Function prototypes
void initializeLCD();
void initializeHallSensor();
void updateRPM();
void displayRPM();

void countPulse() {
  pulseCount++;
}

void setup() {
  initializeLCD();
  initializeHallSensor();
}

void loop() {
  unsigned long currentTime = millis();
  
  if (currentTime - lastUpdateTime >= UPDATE_INTERVAL) {
    updateRPM();
    displayRPM();
    lastUpdateTime = currentTime;
  }
}

void initializeLCD() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("RPM Meter");
}

void initializeHallSensor() {
  pinMode(HALL_SENSOR_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(HALL_SENSOR_PIN), countPulse, FALLING);
}

void updateRPM() {
  noInterrupts();
  unsigned long currentPulseCount = pulseCount;
  pulseCount = 0;
  interrupts();
  
  unsigned long elapsedTime = millis() - lastUpdateTime;
  rpm = (currentPulseCount / 2.0) * (60000.0 / elapsedTime);
}

void displayRPM() {
  lcd.setCursor(0, 1);
  lcd.print("RPM: ");
  lcd.print(rpm, 1);  // Display RPM with one decimal place
  lcd.print("    "); // Clear any remaining characters
}
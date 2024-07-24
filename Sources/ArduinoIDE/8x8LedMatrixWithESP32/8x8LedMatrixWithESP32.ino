#define OE_PIN   12 // Output Enable pin (active low)
#define DATA_PIN 13 // Serial Data Input
#define LATCH_PIN 14 // Latch Pin
#define CLOCK_PIN 15 // Clock Pin

const unsigned long patternChangeInterval = 1000; // Time in milliseconds to change patterns
unsigned long previousMillis = 0; // Stores the last time the pattern was updated
int currPattern = 0; // Index of the current pattern
const int patternCount = 3;

byte patterns[patternCount][8] = {
  {
    0b10000001, // Pattern 1, Row 1
    0b01000010, // Pattern 1, Row 2
    0b10100101, // Pattern 1, Row 3
    0b10011001, // Pattern 1, Row 4
    0b10011001, // Pattern 1, Row 5
    0b10100101, // Pattern 1, Row 6
    0b01000010, // Pattern 1, Row 7
    0b10000001  // Pattern 1, Row 8
  },
  {
    0b11111111, // Pattern 2, Row 1
    0b00000000, // Pattern 2, Row 2
    0b11111111, // Pattern 2, Row 3
    0b00000000, // Pattern 2, Row 4
    0b11111111, // Pattern 2, Row 5
    0b00000000, // Pattern 2, Row 6
    0b11111111, // Pattern 2, Row 7
    0b00000000  // Pattern 2, Row 8
  },
  {
    0b00011000, // Pattern 3, Row 1
    0b00111100, // Pattern 3, Row 2
    0b01111110, // Pattern 3, Row 3
    0b11111111, // Pattern 3, Row 4
    0b11111111, // Pattern 3, Row 5
    0b01111110, // Pattern 3, Row 6
    0b00111100, // Pattern 3, Row 7
    0b00011000  // Pattern 3, Row 8
  }
};

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing pins...");

  pinMode(OE_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);

  digitalWrite(OE_PIN, LOW); // Enable output
  digitalWrite(LATCH_PIN, LOW); // Initialize Latch

  Serial.println("Pins initialized.");
}

void loop() {
  unsigned long currentMillis = millis(); // Get the current time

  // Check if it's time to change the pattern
  if (currentMillis - previousMillis >= patternChangeInterval) {
    // Save the last time the pattern was updated
    previousMillis = currentMillis;
    // Move to the next pattern
    currPattern = (currPattern + 1) % patternCount;
  }
  // Update the pattern
  displayPattern(patterns[currPattern]);
  //delay(10);
}

void displayPattern(byte pattern[8]) {
  for (int row = 0; row < 8; row++) {
    // Prepare row data (active low)
    byte row_data = ~(1 << row); // Only the current row is active
    // Prepare column data (active low)
    byte col_data = ~pattern[row]; // Columns for the current row in the current pattern

    // Shift out row data
    shiftOut(row_data);
    // Shift out column data
    shiftOut(col_data);

    // Latch the data
    digitalWrite(LATCH_PIN, HIGH);
    //delayMicroseconds(2); // Short delay to ensure data is latched
    digitalWrite(LATCH_PIN, LOW);
    delay(2); 
  }
}

void shiftOut(byte data) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(CLOCK_PIN, LOW);
    digitalWrite(DATA_PIN, data & (1 << (7 - i)) ? HIGH : LOW);
    digitalWrite(CLOCK_PIN, HIGH);
  }
}

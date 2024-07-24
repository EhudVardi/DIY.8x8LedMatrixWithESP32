#define OE_PIN   12 // Output Enable pin (active low)
#define DATA_PIN 13 // Serial Data Input
#define LATCH_PIN 14 // Latch Pin
#define CLOCK_PIN 15 // Clock Pin

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
  byte pattern[8] = {
    0b10000001, // Row 1
    0b01000010, // Row 2
    0b00100100, // Row 3
    0b00011000, // Row 4
    0b00011000, // Row 5
    0b00100100, // Row 6
    0b01000010, // Row 7
    0b10000001  // Row 8
  };

  for (int row = 0; row < 8; row++) {
    // Prepare row data (active low)
    byte row_data = ~(1 << row); // Only the current row is active
    // Prepare column data (active low)
    byte col_data = ~pattern[row]; // Columns for the current row

    // Shift out row data
    shiftOut(row_data);
    // Shift out column data
    shiftOut(col_data);

    // Latch the data
    digitalWrite(LATCH_PIN, HIGH);
    delayMicroseconds(10); // Short delay to allow latching
    digitalWrite(LATCH_PIN, LOW);

    // Small delay for persistence of vision
    delay(2); // Adjust this for better visibility
  }
}

void shiftOut(byte data) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(CLOCK_PIN, LOW);
    digitalWrite(DATA_PIN, data & (1 << (7 - i)) ? HIGH : LOW);
    digitalWrite(CLOCK_PIN, HIGH);
  }
}

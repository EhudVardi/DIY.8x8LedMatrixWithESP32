#define OE_PIN   12 // Output Enable pin (active low)
#define DATA_PIN 13 // Serial Data Input
#define LATCH_PIN 14 // Latch Pin
#define CLOCK_PIN 15 // Clock Pin

#define S1_PIN 2
#define S2_PIN 4
#define KEY_PIN 5

const unsigned long patternChangeInterval = 1000; // Time in milliseconds to change patterns
unsigned long previousMillis = 0; // Stores the last time the pattern was updated
int currPattern = 0; // Index of the current pattern
const int patternCount = 4;

volatile int rotation = 0; // Stores the rotation count
volatile bool buttonPressed = false; // Stores the button state

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
    0b10101010, // Pattern 2, Row 1
    0b10101010, // Pattern 2, Row 2
    0b10101010, // Pattern 2, Row 3
    0b10101010, // Pattern 2, Row 4
    0b10101010, // Pattern 2, Row 5
    0b10101010, // Pattern 2, Row 6
    0b10101010, // Pattern 2, Row 7
    0b10101010  // Pattern 2, Row 8
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

  pinMode(S1_PIN, INPUT_PULLUP);
  pinMode(S2_PIN, INPUT_PULLUP);
  pinMode(KEY_PIN, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(S1_PIN), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(S2_PIN), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(KEY_PIN), keyPress, FALLING);

  digitalWrite(OE_PIN, LOW); // Enable output
  digitalWrite(LATCH_PIN, LOW); // Initialize Latch

  Serial.println("Pins initialized.");
}

void loop() {
  static unsigned long previousMillis = 0;
  unsigned long currentMillis = millis(); // Get the current time

  // Update the current pattern based on the rotation of the encoder
  if (rotation != 0) {
    currPattern = (currPattern + rotation + patternCount) % patternCount;
    rotation = 0;
  }

  // If the button is pressed, pause/resume the pattern change
  if (!buttonPressed && (currentMillis - previousMillis >= patternChangeInterval)) {
    // Save the last time the pattern was updated
    previousMillis = currentMillis;
    // Move to the next pattern
    currPattern = (currPattern + 1) % 3;
  }

  // Update the pattern
  displayPattern(patterns[currPattern]);
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

void updateEncoder() {
  static int lastStateS1 = HIGH;
  int currentStateS1 = digitalRead(S1_PIN);
  int currentStateS2 = digitalRead(S2_PIN);

  if (lastStateS1 == HIGH && currentStateS1 == LOW) {
    if (currentStateS2 == HIGH) {
      rotation++;
    } else {
      rotation--;
    }
  }

  lastStateS1 = currentStateS1;
}

void keyPress() {
  buttonPressed = !buttonPressed; // Toggle button state
}

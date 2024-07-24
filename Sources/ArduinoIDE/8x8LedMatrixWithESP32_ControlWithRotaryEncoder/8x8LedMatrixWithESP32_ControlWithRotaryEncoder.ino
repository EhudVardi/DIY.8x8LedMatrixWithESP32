#define OE_PIN   12 // Output Enable pin (active low)
#define DATA_PIN 13 // Serial Data Input
#define LATCH_PIN 14 // Latch Pin
#define CLOCK_PIN 15 // Clock Pin

#define S1_PIN 2
#define S2_PIN 4
#define KEY_PIN 5

volatile int rotation = 0; // Stores the rotation count
volatile bool buttonPressed = false; // Stores the button state

const unsigned long patternChangeInterval = 1000; // Time in milliseconds to change patterns
unsigned long previousMillis = 0; // Stores the last time the pattern was updated
int currPattern = 0; // Index of the current pattern
const int patternCount = 16;

byte patterns[patternCount][8] = {
  {
    0b00111100, // 0
    0b01100110,
    0b01101110,
    0b01110110,
    0b01100110,
    0b01100110,
    0b00111100,
    0b00000000
  },
  {
    0b00011000, // 1
    0b00111000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b01111110,
    0b00000000
  },
  {
    0b00111100, // 2
    0b01100110,
    0b00000110,
    0b00001100,
    0b00110000,
    0b01100000,
    0b01111110,
    0b00000000
  },
  {
    0b00111100, // 3
    0b01100110,
    0b00000110,
    0b00011100,
    0b00000110,
    0b01100110,
    0b00111100,
    0b00000000
  },
  {
    0b00001100, // 4
    0b00011100,
    0b00111100,
    0b01101100,
    0b01111110,
    0b00001100,
    0b00001100,
    0b00000000
  },
  {
    0b01111110, // 5
    0b01100000,
    0b01111100,
    0b00000110,
    0b00000110,
    0b01100110,
    0b00111100,
    0b00000000
  },
  {
    0b00111100, // 6
    0b01100110,
    0b01100000,
    0b01111100,
    0b01100110,
    0b01100110,
    0b00111100,
    0b00000000
  },
  {
    0b01111110, // 7
    0b01100110,
    0b00000110,
    0b00001100,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00000000
  },
  {
    0b00111100, // 8
    0b01100110,
    0b01100110,
    0b00111100,
    0b01100110,
    0b01100110,
    0b00111100,
    0b00000000
  },
  {
    0b00111100, // 9
    0b01100110,
    0b01100110,
    0b00111110,
    0b00000110,
    0b01100110,
    0b00111100,
    0b00000000
  },
  {
    0b00011000, // A
    0b00111100,
    0b01100110,
    0b01100110,
    0b01111110,
    0b01100110,
    0b01100110,
    0b00000000
  },
  {
    0b01111100, // B
    0b00110010,
    0b00110010,
    0b00111100,
    0b00110010,
    0b00110010,
    0b01111100,
    0b00000000
  },
  {
    0b00111100, // C
    0b01100110,
    0b01100000,
    0b01100000,
    0b01100000,
    0b01100110,
    0b00111100,
    0b00000000
  },
  {
    0b01111000, // D
    0b00110100,
    0b00110010,
    0b00110010,
    0b00110010,
    0b00110100,
    0b01111000,
    0b00000000
  },
  {
    0b01111110, // E
    0b01100000,
    0b01111100,
    0b01100000,
    0b01100000,
    0b01100000,
    0b01111110,
    0b00000000
  },
  {
    0b01111110, // F
    0b01100000,
    0b01111100,
    0b01100000,
    0b01100000,
    0b01100000,
    0b01100000,
    0b00000000
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
    currPattern = (currPattern + 1) % patternCount;
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

#define OE_PIN   4 // Output Enable pin (active low)
#define DATA_1_PIN 13 // Serial Data Input
#define LATCH_1_PIN 2 // Latch Pin
#define CLOCK_1_PIN 15 // Clock Pin
#define DATA_2_PIN 12 // Serial Data Input
#define LATCH_2_PIN 33 // Latch Pin
#define CLOCK_2_PIN 32 // Clock Pin
#define DATA_3_PIN 14 // Serial Data Input
#define LATCH_3_PIN 22 // Latch Pin
#define CLOCK_3_PIN 23 // Clock Pin
#define DATA_4_PIN 27 // Serial Data Input
#define LATCH_4_PIN 26 // Latch Pin
#define CLOCK_4_PIN 25 // Clock Pin

#define DATA_PIN(idx) (idx == 1 ? DATA_1_PIN : (idx == 2 ? DATA_2_PIN : (idx == 3 ? DATA_3_PIN : (idx == 4 ? DATA_4_PIN : -1))))
#define LATCH_PIN(idx) (idx == 1 ? LATCH_1_PIN : (idx == 2 ? LATCH_2_PIN : (idx == 3 ? LATCH_3_PIN : (idx == 4 ? LATCH_4_PIN : -1))))
#define CLOCK_PIN(idx) (idx == 1 ? CLOCK_1_PIN : (idx == 2 ? CLOCK_2_PIN : (idx == 3 ? CLOCK_3_PIN : (idx == 4 ? CLOCK_4_PIN : -1))))


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
  initPins(1);
  initPins(2);
  initPins(3);
  initPins(4);

  digitalWrite(OE_PIN, LOW); // Enable output

  Serial.println("Pins initialized.");
}

void initPins(int idx){
  // set pins mode
  pinMode(DATA_PIN(idx), OUTPUT);
  pinMode(LATCH_PIN(idx), OUTPUT);
  pinMode(CLOCK_PIN(idx), OUTPUT);
  // Initialize Latch
  digitalWrite(LATCH_PIN(idx), LOW);
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
  //displayPattern(patterns[currPattern]);
  displayPattern(1,patterns[1]);
  displayPattern(2,patterns[2]);
  displayPattern(3,patterns[3]);
  displayPattern(4,patterns[4]);
  //delay(10);
}

void displayPattern(int idx, byte pattern[8]) {
  for (int row = 0; row < 8; row++) {
    // Prepare row data (active low)
    byte row_data = ~(1 << row); // Only the current row is active
    // Prepare column data (active low)
    byte col_data = ~pattern[row]; // Columns for the current row in the current pattern
    // Shift out row data, column data, and latch
    sendData(idx, row_data, col_data);
  }
}

void sendData(int idx, byte rowData, byte colData)
{
  shiftOut(rowData, CLOCK_PIN(idx), DATA_PIN(idx));
  shiftOut(colData, CLOCK_PIN(idx), DATA_PIN(idx));
  latch(LATCH_PIN(idx));
}

void shiftOut(byte data, int clockPin, int dataPin) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(clockPin, LOW);
    digitalWrite(dataPin, data & (1 << (7 - i)) ? HIGH : LOW);
    digitalWrite(clockPin, HIGH);
  }
}
void latch(int latchPin) {
    // Latch the data
    digitalWrite(latchPin, HIGH);
    //delayMicroseconds(2); // Short delay to ensure data is latched
    digitalWrite(latchPin, LOW);
}

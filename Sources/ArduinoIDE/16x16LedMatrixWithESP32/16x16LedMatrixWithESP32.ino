#define OE_PIN   4 // Output Enable pin (active low)
#define DATA_1_PIN 13 // Serial Data Input
#define LATCH_1_PIN 2 // Latch Pin
#define CLOCK_1_PIN 15 // Clock Pin

#define DATA_PIN DATA_1_PIN
#define LATCH_PIN LATCH_1_PIN
#define CLOCK_PIN CLOCK_1_PIN


const unsigned long patternChangeInterval = 1000; // Time in milliseconds to change patterns
unsigned long previousMillis = 0; // Stores the last time the pattern was updated
int currPattern = 0; // Index of the current pattern
const int patternCount = 16;

byte patterns[patternCount][32] = {
		{ // 0
				0b00000011, 0b11111100,
				0b00001100, 0b00001100,
				0b00110000, 0b00000011,
				0b01100000, 0b00000001,
				0b01100000, 0b00000001,
				0b11000000, 0b00000001,
				0b11000000, 0b00000001,
				0b11000000, 0b00000001,
				0b11000000, 0b00000001,
				0b11000000, 0b00000001,
				0b01100000, 0b00000001,
				0b01100000, 0b00000001,
				0b00110000, 0b00000011,
				0b00001100, 0b00001100,
				0b00000011, 0b11111100,
				0b00000000, 0b00000000
		},
    { // 1
        0b00000000, 0b11000000,
        0b00000011, 0b11000000,
        0b00001111, 0b11000000,
        0b00001110, 0b11000000,
        0b00000000, 0b11000000,
        0b00000000, 0b11000000,
        0b00000000, 0b11000000,
        0b00000000, 0b11000000,
        0b00000000, 0b11000000,
        0b00000000, 0b11000000,
        0b00000000, 0b11000000,
        0b00000000, 0b11000000,
        0b00000000, 0b11000000,
        0b00000000, 0b11000000,
        0b00001111, 0b11111111,
        0b00001111, 0b11111111
    },
    { // 2
        0b00001111, 0b11000000,
        0b00111000, 0b01111000,
        0b00110000, 0b00011100,
        0b00000000, 0b00000110,
        0b00000000, 0b00000110,
        0b00000000, 0b00001110,
        0b00000000, 0b00011100,
        0b00000000, 0b00111000,
        0b00000000, 0b01110000,
        0b00000000, 0b11100000,
        0b00000001, 0b11000000,
        0b00000011, 0b10000000,
        0b00001110, 0b00000000,
        0b00111000, 0b00000000,
        0b01111111, 0b11111111,
        0b01111111, 0b11111111
    },
    { // 3
				0b01111111, 0b11111110,
				0b11000000, 0b00000011,
				0b10000000, 0b00000011,
				0b00000000, 0b00000011,
				0b00000000, 0b00000011,
				0b00000000, 0b00001110,
				0b00000000, 0b00111100,
				0b00000000, 0b00111110,
				0b00000000, 0b00000111,
				0b00000000, 0b00000011,
				0b00000000, 0b00000011,
				0b00000000, 0b00000011,
				0b11000000, 0b00000110,
				0b01111000, 0b00111100,
				0b00011111, 0b11110000,
				0b00000000, 0b00000000
    },
    { // 4
        0b00000000, 0b00110000,
        0b00000000, 0b01110000,
        0b00000000, 0b11110000,
        0b00000001, 0b10110000,
        0b00000011, 0b00110000,
        0b00000010, 0b00110000,
        0b00000110, 0b00110000,
        0b00001100, 0b00110000,
        0b00011000, 0b00110000,
        0b00010000, 0b00110000,
        0b00110000, 0b00110000,
        0b01100000, 0b00110000,
        0b11111111, 0b11111111,
        0b11111111, 0b11111111,
        0b00000000, 0b00110000,
        0b00000000, 0b00110000
    },
    { // 5
        0b00111111, 0b11111110,
        0b00111111, 0b11111110,
        0b00110000, 0b00000000,
        0b00110000, 0b00000000,
        0b00110000, 0b00000000,
        0b00111111, 0b11111000,
        0b00001111, 0b11111100,
        0b00000000, 0b00001110,
        0b00000000, 0b00000110,
        0b00000000, 0b00000011,
        0b00000000, 0b00000011,
        0b00000000, 0b00000011,
        0b00000000, 0b00000011,
        0b00100000, 0b00000110,
        0b00110000, 0b00001100,
        0b00011111, 0b11111000
    },
    { // 6
        0b00000000, 0b11111100,
        0b00000011, 0b00001100,
        0b00001100, 0b00000011,
        0b00011000, 0b00000001,
        0b00011000, 0b00000001,
        0b00110000, 0b00000001,
        0b00110000, 0b00000001,
        0b01100000, 0b00000001,
        0b01111111, 0b11111001,
        0b01110000, 0b00001110,
        0b01100000, 0b00000111,
        0b11000000, 0b00000011,
        0b11000000, 0b00000011,
        0b11000000, 0b00000011,
        0b01100000, 0b00000011,
        0b00110000, 0b00001110
    },
    { // 7
        0b11111111, 0b11111111,
        0b11111111, 0b11111111,
        0b00000000, 0b00000011,
        0b00000000, 0b00000110,
        0b00000000, 0b00001100,
        0b00000000, 0b00011000,
        0b00000000, 0b00110000,
        0b00000000, 0b01100000,
        0b00000000, 0b11000000,
        0b00000000, 0b10000000,
        0b00000001, 0b00000000,
        0b00000010, 0b00000000,
        0b00000100, 0b00000000,
        0b00001000, 0b00000000,
        0b00010000, 0b00000000,
        0b00100000, 0b00000000
    },
    { // 8
        0b00000011, 0b11111100,
        0b00001100, 0b00001100,
        0b00110000, 0b00000011,
        0b01100000, 0b00000001,
        0b01100000, 0b00000001,
        0b00110000, 0b00000011,
        0b00001100, 0b00001110,
        0b00000011, 0b11111100,
        0b00001100, 0b00001110,
        0b00110000, 0b00000011,
        0b01100000, 0b00000001,
        0b01100000, 0b00000001,
        0b01100000, 0b00000001,
        0b00110000, 0b00000011,
        0b00001100, 0b00001100,
        0b00000011, 0b11111100
    },
    { // 9
        0b00000011, 0b11111100,
        0b00001100, 0b00001100,
        0b00110000, 0b00000011,
        0b01100000, 0b00000001,
        0b01100000, 0b00000001,
        0b01100000, 0b00000001,
        0b00110000, 0b00000011,
        0b00001100, 0b00001111,
        0b00000011, 0b11111111,
        0b00000000, 0b00000011,
        0b00000000, 0b00000011,
        0b00000000, 0b00000011,
        0b00000000, 0b00000011,
        0b00110000, 0b00000010,
        0b00011000, 0b00000110,
        0b00001111, 0b11111000
    },
    { // A
        0b00000000, 0b11111100,
        0b00000011, 0b10001100,
        0b00000110, 0b00000011,
        0b00001100, 0b00000001,
        0b00001100, 0b00000001,
        0b00011000, 0b00000001,
        0b00011000, 0b00000001,
        0b00110000, 0b00000001,
        0b00110000, 0b00000001,
        0b01111111, 0b11111111,
        0b01111111, 0b11111111,
        0b11000000, 0b00000011,
        0b11000000, 0b00000011,
        0b11000000, 0b00000011,
        0b11000000, 0b00000010,
        0b11100000, 0b00000110
    },
    { // B
        0b11111111, 0b11111100,
        0b11111111, 0b11111110,
        0b01100000, 0b00000110,
        0b01100000, 0b00000011,
        0b01100000, 0b00000011,
        0b01100000, 0b00000011,
        0b01100000, 0b00000011,
        0b01100000, 0b00000110,
        0b01111111, 0b11111100,
        0b01100000, 0b00000110,
        0b01100000, 0b00000011,
        0b01100000, 0b00000011,
        0b01100000, 0b00000011,
        0b01100000, 0b00000011,
        0b01100000, 0b00000110,
        0b11111111, 0b11111100
    },
    { // C
        0b00000011, 0b11111100,
        0b00001100, 0b00001100,
        0b00110000, 0b00000011,
        0b01100000, 0b00000001,
        0b01100000, 0b00000001,
        0b01100000, 0b00000001,
        0b11000000, 0b00000001,
        0b11000000, 0b00000000,
        0b11000000, 0b00000000,
        0b11000000, 0b00000000,
        0b01100000, 0b00000001,
        0b01100000, 0b00000001,
        0b01100000, 0b00000001,
        0b00110000, 0b00000011,
        0b00001100, 0b00001100,
        0b00000011, 0b11111100
    },
    { // D
        0b11111111, 0b11110000,
        0b11111111, 0b11111000,
        0b01100000, 0b00001100,
        0b01100000, 0b00000110,
        0b01100000, 0b00000011,
        0b01100000, 0b00000011,
        0b01100000, 0b00000011,
        0b01100000, 0b00000011,
        0b01100000, 0b00000011,
        0b01100000, 0b00000011,
        0b01100000, 0b00000011,
        0b01100000, 0b00000110,
        0b01100000, 0b00001100,
        0b01100000, 0b00011000,
        0b11111111, 0b11110000,
        0b11111111, 0b11100000
    },
    { // E
        0b11111111, 0b11111111,
        0b11111111, 0b11111111,
        0b01100000, 0b00000000,
        0b01100000, 0b00000000,
        0b01100000, 0b00000000,
        0b01100000, 0b00000000,
        0b01111111, 0b11111000,
        0b01111111, 0b11111000,
        0b01100000, 0b00000000,
        0b01100000, 0b00000000,
        0b01100000, 0b00000000,
        0b01100000, 0b00000000,
        0b01100000, 0b00000000,
        0b01100000, 0b00000000,
        0b11111111, 0b11111111,
        0b11111111, 0b11111111
    },
    { // F
        0b11111111, 0b11111111,
        0b11111111, 0b11111111,
        0b01100000, 0b00000000,
        0b01100000, 0b00000000,
        0b01100000, 0b00000000,
        0b01100000, 0b00000000,
        0b01111111, 0b11111000,
        0b01111111, 0b11111000,
        0b01100000, 0b00000000,
        0b01100000, 0b00000000,
        0b01100000, 0b00000000,
        0b01100000, 0b00000000,
        0b01100000, 0b00000000,
        0b01100000, 0b00000000,
        0b01100000, 0b00000000,
        0b01100000, 0b00000000
    }
};


void setup() {
  Serial.begin(115200);
  Serial.println("Initializing pins...");

  // set pins mode
  pinMode(OE_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);

  digitalWrite(LATCH_PIN, LOW); // Initialize Latch
  digitalWrite(OE_PIN, LOW); // Enable output

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

void displayPattern(byte pattern[32]) {
  for (int row = 0; row < 16; row++) {
    int16_t rowData = ~(1 << row);
    int16_t colData = ~((pattern[row * 2] << 8) | pattern[row * 2 + 1]);

    sendData(rowData, colData);
  }
}

void sendData(int16_t rowData, int16_t colData)
{
  byte rowData_highByte = (rowData >> 8) & 0xFF;
  byte rowData_lowByte = rowData & 0xFF;
  byte colData_highByte = (colData >> 8) & 0xFF;
  byte colData_lowByte = colData & 0xFF;
  shiftOut(rowData_highByte, CLOCK_PIN, DATA_PIN);
  shiftOut(rowData_lowByte, CLOCK_PIN, DATA_PIN);
  shiftOut(colData_highByte, CLOCK_PIN, DATA_PIN);
  shiftOut(colData_lowByte, CLOCK_PIN, DATA_PIN);
  latch(LATCH_PIN);
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

// Max Volt = 570 (~300V)
// Min Volt = 350 (~180V)
const short MIN_VOLT = 360;
const short MAX_VOLT = 570;

const short GENERATOR = A0;
const short LINE = A1;

const byte LOOP_DELAY = 5;
const byte VALVE_DELAY = 8;
const byte IGNITION_DELAY = 3;

const byte IGNITION = 10;
const byte VALVE = 11;
const byte SWITCH = 12;
const byte LED = 13;

byte IGNITION_ATTEMPTS = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pins as outputs.
  pinMode(IGNITION, OUTPUT);
  pinMode(VALVE, OUTPUT);
  pinMode(SWITCH, OUTPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(IGNITION, HIGH);
  digitalWrite(VALVE, HIGH);
  digitalWrite(SWITCH, HIGH);
  //Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  // read the input voltages
  digitalWrite(LED, HIGH);
  short line_volt = analogRead(LINE);
  delay(100); // delay to stablize ADC
  short gen_volt = analogRead(GENERATOR);
//  Serial.println("L");
//  Serial.println(line_volt);
//  Serial.println("G");
//  Serial.println(gen_volt);
  digitalWrite(LED, LOW);
  if (line_volt >= MIN_VOLT) {
    IGNITION_ATTEMPTS = 0;
    // switch load to mains.
    digitalWrite(SWITCH, HIGH);
    if (gen_volt >= MIN_VOLT) {
      // cut off gas to generator
      digitalWrite(VALVE, LOW);
      delay(VALVE_DELAY * 1000);
      digitalWrite(VALVE, HIGH);
    }
  } else {
    if (gen_volt < MIN_VOLT) {
      // try to start generator
      if (IGNITION_ATTEMPTS < 2) {
        digitalWrite(SWITCH, HIGH); // switch load to mains.
        digitalWrite(IGNITION, LOW);
        digitalWrite(LED, HIGH);
        delay(IGNITION_DELAY * 1000);
        digitalWrite(IGNITION, HIGH);
        digitalWrite(LED, LOW);
        IGNITION_ATTEMPTS++;
      }
    } else {
      // switch load to generator
      digitalWrite(SWITCH, LOW);
    }
  }
  delay(LOOP_DELAY * 1000);
}

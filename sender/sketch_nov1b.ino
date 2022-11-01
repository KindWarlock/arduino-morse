#define DATA_PIN 9

int TU = 100;
String LETTERS_CODE[] = {".-", "--.."};
char LETTERS[] = {'A', 'Z'};
void setup() {
  Serial.begin(9600);
  pinMode(DATA_PIN, OUTPUT);
  digitalWrite(DATA_PIN, 1);
}

void loop() {
  if (Serial.available() == 1) {
    char letter = Serial.read(); 
    for (int i = 0; i < 2; i++) {
      if (LETTERS[i] == letter) {
        encode(LETTERS_CODE[i]);
      }            
    }
  } 
}

void encode(String dashdot) {
  for (int i = 0; i < dashdot.length(); i++) {
    if (dashdot[i] == '.') {
      digitalWrite(DATA_PIN, false);
      delay(TU);
      Serial.println(".");
    } else {
      digitalWrite(DATA_PIN, false);
      delay(3 * TU);      
      Serial.println("-");
    }
    digitalWrite(DATA_PIN, true);
    delay(TU);
  }
  delay(3 * TU);
  
  Serial.println("Done encoding");
}
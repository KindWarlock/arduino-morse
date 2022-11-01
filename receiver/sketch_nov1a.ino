#define DATA_PIN 2
#define LETTER_SEP 3
#define IDLE_TIME 10

int TU = 100;
long start = 0;

int timings[20];
bool levels[20];
int curr_char = 0;
String dots_dash = "";
String LETTERS_CODE[] = {".-", "--.."};
char LETTERS[] = {'A', 'Z'};

bool is_idle = false;

void process_timing() {
  if (!is_idle){
    timings[curr_char] = round((millis() - start + TU - 1) / TU);
    levels[curr_char] = !digitalRead(DATA_PIN);
    curr_char++;
  } else {
    is_idle = false;  
  }
  start = millis();
}

void process_idle() {
  //Serial.println("idle...");
  if (round((millis() - start + TU - 1) >= IDLE_TIME)) { 
    timings[curr_char] = 7;
    levels[curr_char] = 1;
    curr_char++;
    is_idle = true;
  }
}

void decode_letter() {
  for (int i = 0; i < curr_char; i++) {
    if (!levels[i]) {
      if (timings[i] == 1) {
        dots_dash += '.';                                     
      } else {
        dots_dash += '-';                                     
      }
    }            
  }     
      
  curr_char = 0;
  
  for (int i = 0; i < 2; i++) {
    if (LETTERS_CODE[i] == dots_dash) {
      Serial.print(LETTERS[i]);
    }
  }
  dots_dash = "";    
}

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
  attachInterrupt(0, process_timing, CHANGE); 
}

void loop() {
  process_idle();
  if (!is_idle && timings[curr_char - 1] >= LETTER_SEP && levels[curr_char - 1]) {
    decode_letter();
  }
}

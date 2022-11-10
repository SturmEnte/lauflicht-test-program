const int START_LED = 2;
const int END_LED = 11;

const int BUTTON_LEFT = 12;
const int BUTTON_RIGHT = 13;

const int START_GREEN = A0;
const int END_GREEN = A3;

const int DELAY_S = 200;

unsigned long l0;

int i1 = START_LED;
unsigned long l1;
int mode1 = 0;

int mode2 = 0;
unsigned long l2;

int mode3 = 0;
unsigned long l3;

int ldelay = 0;
int rdelay = 0;

void setup() {
  for(int i = START_LED; i <= END_LED; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);

  l1 = millis();
  l2 = millis();

  Serial.begin(9600);
  Serial.println(A0);
}

int divi = 1;

void loop() {
  if(digitalRead(BUTTON_RIGHT) == LOW && millis() - l0 >= DELAY_S) {
    divi++;
    l0 = millis();
  } else if(digitalRead(BUTTON_RIGHT) == HIGH) {
    divi = 1;
  }
  
  if(mode1 == 0 && millis() - l1 >= DELAY_S / divi && digitalRead(BUTTON_LEFT) == HIGH) {
    digitalWrite(i1, HIGH);
    i1++;
    l1 = millis();
  } else if(mode1 == 1 && millis() - l1 >= DELAY_S / divi && digitalRead(BUTTON_LEFT) == HIGH) {
    digitalWrite(i1, LOW);
    i1--;
    l1 = millis();
  }

  if(i1 == 1) mode1 = 0;
  else if(i1 == 12) mode1 = 1;

  ldelay = analogRead(A5);
  rdelay = analogRead(A4);
  
  if(mode2 == 0 && millis() - l2 > ldelay) {
    for(int i = A2; i <= A3; i++) {
      digitalWrite(i, HIGH);
    }
    mode2 = 1;
    l2 = millis();
  } else if(mode2 == 1 && millis() - l2 > ldelay) {
    for(int i = A2; i <= A3; i++) {
      digitalWrite(i, LOW);
    }
    mode2 = 0;
    l2 = millis();
  }

  if(mode3 == 0 && millis() - l3 > rdelay) {
    for(int i = A0; i <= A1; i++) {
      digitalWrite(i, HIGH);
    }
    mode3 = 1;
    l3 = millis();
  } else if(mode3 == 1 && millis() - l3 > rdelay) {
    for(int i = A0; i <= A1; i++) {
      digitalWrite(i, LOW);
    }
    mode3 = 0;
    l3 = millis();
  }


  if(digitalRead(BUTTON_RIGHT) == LOW) {
    digitalWrite(A0, HIGH);
    digitalWrite(A1, HIGH);
  }

  if(digitalRead(BUTTON_LEFT) == LOW) {
    digitalWrite(A2, HIGH);
    digitalWrite(A3, HIGH);
  }
}

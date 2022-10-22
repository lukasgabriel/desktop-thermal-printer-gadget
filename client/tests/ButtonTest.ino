// Button Test Program

int switchL = 3;
int switchM = 0;
int switchR = 1;

bool lWorks = false;
bool mWorks = false;
bool rWorks = false;

void setup() {
Serial.begin (9600);
pinMode(LED_BUILTIN, OUTPUT);
pinMode (switchL, INPUT);
pinMode (switchM, INPUT);
pinMode (switchR, INPUT);
}

void loop() {

if (digitalRead(switchL) == HIGH) {
  Serial.println("Button L Pressed");
  lWorks = true;
}
if (digitalRead(switchM) == HIGH) {
  Serial.println("Button M Pressed");
  mWorks = true;
}
if (digitalRead(switchR) == HIGH) {
  Serial.println("Button R Pressed");
  rWorks = true;
}

if (lWorks && mWorks && rWorks) {
  digitalWrite(LED_BUILTIN, HIGH);
}

}
void setup() {
  for (int i = 0; i <= 8; i++) {
    pinMode(i, OUTPUT); 
  }
}

int lights[] = {7, 6, 3, 2, 5, 4, 1, 0};
int active = 0;

void loop() {
  for (int i = 0; i <= 8; i++) {
    analogWrite(i, 0);
  }
  analogWrite(lights[active], 255);
  
  active = ( active + 1 ) % 8;
  
  delay(1000);
}

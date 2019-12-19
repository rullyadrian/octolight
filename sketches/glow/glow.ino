void setup() {
  for (int i = 0; i <= 8; i++) {
    pinMode(i, OUTPUT); 
  }
}

int maxBrightness = 63;
int brightness = 0;
int step = 1;

void loop() {
  for (int i = 0; i <= 8; i++) {
    analogWrite(i, brightness);
  }

  brightness = brightness + step;
  if (brightness >= maxBrightness) {
    brightness = maxBrightness;
    step *= -1;
  } else if (brightness <= 0) {
    brightness = 0;
    step *= -1;
  }

  delay(80);
}

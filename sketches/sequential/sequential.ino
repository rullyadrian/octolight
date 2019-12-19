#define NUM_LIGHTS 8
#define PERIOD 100
#define HALF_PERIOD (PERIOD / 2)
#define OVERLAP 20
#define REST 100
#define MAX_VALUE 255
#define DELAY 10

int lights[] = {7, 6, 3, 2, 5, 4, 1, 0};
int values[] = {0, 0, 0, 0, 0, 0, 0, 0};
int t = 0;

void setup()
{
  for (int i = 0; i <= 8; i++)
  {
    pinMode(i, OUTPUT);
  }
}

void loop()
{
  calculateValues();
  writeValues();

  t = (t + 1) % (NUM_LIGHTS * (PERIOD - OVERLAP) + OVERLAP + REST);
  delay(DELAY);
}

void calculateValues()
{
  for (int i = 0; i < NUM_LIGHTS; i++)
  {
    values[i] = calculateValue(i, t - i * (PERIOD - OVERLAP));
  }
}

int calculateValue(int idx, int t)
{
  float value = 0.0;

  if (t >= 0)
  {
    if (t < HALF_PERIOD)
    {
      value = float(t) / HALF_PERIOD * MAX_VALUE;
    }
    else if (t < PERIOD)
    {
      value = (1 - (float(t) - HALF_PERIOD) / HALF_PERIOD) * MAX_VALUE;
    }
  }

  return value;
}

void writeValues()
{
  for (int i = 0; i < NUM_LIGHTS; i++)
  {
    analogWrite(lights[i], values[i]);
  }
}
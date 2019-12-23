const int MAX_BRIGHTNESS = 255;
const int NUM_OF_LIGHTS = 8;
const long FIRE_INTERVAL = 500;

class Light
{
    int pin;
    int updateInterval;
    int numOfSteps;
    int scaleMultiply;
    int scaleDivide;
    int step;
    unsigned long lastUpdateTime;

public:
    Light(int pin, int updateInterval, int numOfSteps, int scaleMultiply, int scaleDivide)
    {
        this->pin = pin;
        this->updateInterval = updateInterval;
        this->numOfSteps = numOfSteps;
        this->scaleMultiply = scaleMultiply;
        this->scaleDivide = scaleDivide;
        this->step = -1;
        this->lastUpdateTime = 0;

        pinMode(pin, OUTPUT);
    }

    void fire()
    {
        step = 0;
    }

    void update()
    {
        if (step < 0)
        {
            return;
        }

        long currentTime = millis();
        if (currentTime - lastUpdateTime < updateInterval)
        {
            return;
        }

        int brightness = calculateBrightness(step);
        analogWrite(pin, brightness);

        step++;
        if (step == numOfSteps)
        {
            step = -1;
        }

        lastUpdateTime = currentTime;
    }

private:
    int calculateBrightness(int step)
    {
        int brightness = 0;

        if (step < numOfSteps / 2)
        {
            brightness = step * MAX_BRIGHTNESS / (numOfSteps / 2);
        }
        else if (step < numOfSteps)
        {
            brightness = MAX_BRIGHTNESS - (step - numOfSteps / 2) * MAX_BRIGHTNESS / ((numOfSteps - 1) / 2);
        }

        return brightness * scaleMultiply / scaleDivide;
    }
};

Light lights[] = {
    Light(7, 10, 100, 1, 1),
    Light(6, 10, 100, 1, 1),
    Light(3, 10, 100, 1, 4),
    Light(2, 10, 100, 1, 1),
    Light(5, 10, 100, 1, 1),
    Light(4, 10, 100, 1, 1),
    Light(1, 10, 100, 1, 4),
    Light(0, 10, 100, 1, 1),
};

int currentLight = 0;
long lastFireTime = 0;

void setup()
{
}

void loop()
{
    long currentTime = millis();
    if (currentTime - lastFireTime >= FIRE_INTERVAL)
    {
        lights[currentLight].fire();
        currentLight = (currentLight + 1) % NUM_OF_LIGHTS;
        lastFireTime = currentTime;
    }

    for (int i = 0; i < NUM_OF_LIGHTS; i++)
    {
        lights[i].update();
    }
}
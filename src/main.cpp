#include <Arduino.h>
#include <color.h>
#include <effects.h>
#include <Adafruit_NeoPixel.h>
#include <vector>

NEOFX::cycle func{NEOFX::rainbow, 1.0};

constexpr int num_neopixels = 181;

// std::vector<double> x{0.0, -1, 0.5, 0.866, 1, 0.866, -0.5};
// std::vector<double> y{0.0, 0, 0.866, 0.5, 0, -0.5, -0.866};

Adafruit_NeoPixel pixels(num_neopixels, 13);

double t = 0.0;
constexpr int wait_time = 30;
constexpr double delta_t = 0.005;

void setup() {
  pixels.begin();
  pixels.setBrightness(255/4);
}

void loop() {
  t += delta_t;
  pixels.fill(0);
  pixels.show();
  delay(1000);
  for (int i = 0; i < num_neopixels; i++){
    // NEOFX::RGB col = func(0, 0, t);
    pixels.setPixelColor(i, 255, 255, 255);
    delay(10);
    pixels.show();
  }

  delay(wait_time);
  // put your main code here, to run repeatedly:
}
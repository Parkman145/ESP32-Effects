#include <Arduino.h>
#include <color.h>
#include <effects.h>
#include <Adafruit_NeoPixel.h>
#include <vector>
#include <effect_presets.h>


// Constants
constexpr int num_neopixels = 241;
constexpr int wait_time = 30;
constexpr double delta_t = 0.005;
constexpr int brightness = 255/32;
constexpr int pin = 13;
constexpr double scale = 1.0/9.0;
std::vector<int> row_counts{1, 8, 12, 16, 24, 32, 40, 48, 60};


auto func = NEOFX::effect_presets::rainbow_chaser;

// Locations for mini disk
// std::vector<double> x{0.0, -1, 0.5, 0.866, 1, 0.866, -0.5};
// std::vector<double> y{0.0, 0, 0.866, 0.5, 0, -0.5, -0.866};

Adafruit_NeoPixel pixels(num_neopixels, pin);

double t = 0.0;

std::vector<double> x;
std::vector<double> y;


float lx = 0;
float ly = 0.5;
float lop = 1.0;
float rx = 0;
float ry = 0;
float rop = 0;

String recieve_message(){
  Serial.find('<');
  return Serial.readStringUntil('>');
}

void decode_message(String str){
  char* token = strtok(str.begin(), ",>");
  if (token == nullptr) return;
  lx = atof(token);
  token = strtok(nullptr, ",>");
  if (token == nullptr) return;
  ly = atof(token);
  token = strtok(nullptr, ",>");
  if (token == nullptr) return;
  lop = atof(token);
  token = strtok(nullptr, ",>");
  if (token == nullptr) return;
  rx = atof(token);
  token = strtok(nullptr, ",>");
  if (token == nullptr) return;
  ry = atof(token);
  token = strtok(nullptr, ",>");
  if (token == nullptr) return;
  rop = atof(token);  
}


void setup() {
  // Calculating positions of pixels, with wires to the right
  // This can def be made more efficient, perhaps by using a std::array
  // But I don't care
  for (int i = 0; i < row_counts.size(); i++) {
    double distance = i;
    for (int j = 0; j < row_counts[i]; j++) {
      double angle = 2*PI*(-static_cast<double>(j)/static_cast<double>(row_counts[i]))+2*PI;
      x.push_back(std::cos(angle)*distance*scale);
      y.push_back(std::sin(angle)*distance*scale);
    }
  }
  pixels.begin();
  pixels.setBrightness(brightness);
  Serial.begin(115200);
  pinMode(14, INPUT);
  Serial.println("beginning");
}

void loop() {
  t += delta_t*lx*lx*lx*10;
  String message = recieve_message();
  decode_message(message); 

  for (int i = 0; i < num_neopixels; i++){
    NEOFX::RGB col = func(x[i], y[i], t);
    pixels.setPixelColor(i, col.R*255, col.G*255, col.B*255);
  }
  pixels.show();

  delay(wait_time);
  // put your main code here, to run repeatedly:
}
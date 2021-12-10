#include <Adafruit_AHTX0.h>
//Temp Sensor int
Adafruit_AHTX0 aht;
const int heat_pin = 5;
const int cool_pin = 6;
const int temp_up_btn = 9;
const int temp_down_btn = 10;
int btn1_state = 0;
int btn2_state = 0;
int temp_set = 0;
int temp_get = 0;
int heat = LOW;
int cool = LOW;

//display int
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);
  Serial.println("Adafruit AHT10/AHT20 demo!");
  if (! aht.begin()) {
    Serial.println("Could not find AHT? Check wiring");
    while (1) delay(10);
  }
  Serial.println("AHT10 or AHT20 found");
  pinMode(heat_pin, OUTPUT);
  pinMode(cool_pin, OUTPUT);
  pinMode(temp_up_btn, INPUT);
  pinMode(temp_down_btn, INPUT);

  //display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 20);
  // Display static text
  display.println("No temp set");
  display.display(); 
}

void loop() {
  //button
  btn1_state = digitalRead(temp_up_btn);
  btn2_state = digitalRead(temp_down_btn);
  if (btn1_state == HIGH) {
    temp_set += 1;
  } else if (btn2_state == HIGH) {
    temp_set -= 1;
  }
  
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data
  if (temp_get == 0) {
    temp_get = temp.temperature;
    temp_set = temp.temperature;
  } else {
    temp_get = temp.temperature;
  }
  
  //Serial.print("Temperature: "); Serial.print(temp.temperature); Serial.println(" degrees C");
  //Serial.print("Humidity: "); Serial.print(humidity.relative_humidity); Serial.println("% rH");
  if (temp_set < temp_get - 2 ) {
    heat = LOW;
    cool = HIGH;
    Serial.println("Turn on fan");
    setDisplay("fan", temp_get, temp_set);
  } else if (temp_set > temp_get + 2) {
    heat = HIGH;
    cool = LOW;
    setDisplay("peltier", temp_get, temp_set);
    Serial.println("Turn on peltier");
  } else {
    heat = LOW;
    cool = LOW;
    setDisplay("none", temp_get, temp_set);
    Serial.println("Turn on none");
  }
  
  digitalWrite(heat_pin, heat);
  digitalWrite(cool_pin, cool);
  delay(500);
}

void setDisplay(String device, int temp_sens, int set_temp){
  String print_disp = "Turn on " + device;
  display.clearDisplay();
  display.setCursor(0, 20);
  display.print("Set temp: ");
  display.print(set_temp);
  display.println(" C");
  display.print("Current temp: ");
  display.print(temp_sens);
  display.println(" C");
  display.print(print_disp);
  display.display(); 
}

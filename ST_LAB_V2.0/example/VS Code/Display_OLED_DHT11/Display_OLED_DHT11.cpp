#include <Arduino.h>
#include <Wire.h>
#include <DHT.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// -------------------------------------------------------------
// OLED config
// -------------------------------------------------------------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// -------------------------------------------------------------
// DHT11 config
// -------------------------------------------------------------
#define DHTPIN 19
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
    Serial.begin(115200);

    // เริ่มต้น DHT
    dht.begin();

    // เริ่มต้น OLED
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.println("OLED FAIL");
        while (1);
    }

    display.clearDisplay();
    display.setTextColor(WHITE);
}

void loop()
{
    float t = dht.readTemperature(); // อุณหภูมิ °C
    float h = dht.readHumidity();    // ความชื้น %

    if (isnan(t) || isnan(h))
    {
        Serial.println("Failed to read DHT11");
        return;
    }

    // แสดงผลทาง Serial
    Serial.print("Temp: ");
    Serial.print(t);
    Serial.print(" C  Humi: ");
    Serial.print(h);
    Serial.println(" %");

    // ---------------- OLED ----------------
    display.clearDisplay();

    // หัวข้อ
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print("DHT11 SENSOR");

    // อุณหภูมิ
    display.setTextSize(2);
    display.setCursor(0, 20);
    display.print("T:");
    display.print(t, 1);
    display.print(" C");

    // ความชื้น
    display.setCursor(0, 45);
    display.print("H:");
    display.print(h, 1);
    display.print(" %");

    display.display();

    delay(2000); // DHT11 ต้องหน่วงเวลา
}

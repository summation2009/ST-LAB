#include <Arduino.h>
#include <Wire.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

// -------------------------------------------------------------
// DHT11 config
// -------------------------------------------------------------
#define DHTPIN 19
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// -------------------------------------------------------------
// LCD I2C config
// -------------------------------------------------------------
LiquidCrystal_I2C lcd(0x27, 20, 4); // 20x4 LCD

void setup()
{
    Serial.begin(115200);

    // เริ่มต้น DHT
    dht.begin();

    // เริ่มต้น LCD
    lcd.init();
    lcd.backlight();

    // ข้อความเริ่มต้น
    lcd.setCursor(3, 1);
    lcd.print("DHT11 SENSOR");
    delay(2000);
    lcd.clear();
}

void loop()
{
    float t = dht.readTemperature(); // °C
    float h = dht.readHumidity();    // %

    if (isnan(t) || isnan(h))
    {
        lcd.setCursor(0, 0);
        lcd.print("DHT11 ERROR     ");
        return;
    }

    // แสดงผล Serial
    Serial.print("Temp: ");
    Serial.print(t);
    Serial.print(" C  Humi: ");
    Serial.print(h);
    Serial.println(" %");

    // ---------------- LCD ----------------
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(t, 1);
    lcd.print(" C   ");   // ลบค่าค้าง

    lcd.setCursor(0, 1);
    lcd.print("Humi: ");
    lcd.print(h, 1);
    lcd.print(" %   ");

    delay(2000); // DHT11 ต้องหน่วงเวลา
}

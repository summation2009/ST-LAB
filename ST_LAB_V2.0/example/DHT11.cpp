#include <Arduino.h>
#include <DHT.h>

// -------------------------------------------------------------
// กำหนดขาที่เชื่อมต่อ DHT11 และชนิดเซ็นเซอร์
// -------------------------------------------------------------
#define DHTPIN 19        // ขาที่ต่อ DHT11
#define DHTTYPE DHT11    // ชนิดเซ็นเซอร์ DHT11 DHTTYPE ถ้าเป็น DHT22 ก็เปลี่ยนเป็น DHT22

DHT dht(DHTPIN, DHTTYPE); // สร้าง object สำหรับอ่านค่า DHT11


void setup()
{
    Serial.begin(115200); // เปิด Serial Monitor
    dht.begin();          // เริ่มต้น DHT sensor
}


// -------------------------------------------------------------
// อ่านค่า Temperature และ Humidity
// -------------------------------------------------------------
void loop()
{
    // อ่านค่าอุณหภูมิ (°C)
    float t = dht.readTemperature();

    // อ่านค่าความชื้นสัมพัทธ์ (%RH)
    float h = dht.readHumidity();

    // ตรวจสอบว่าการอ่านค่าสำเร็จหรือไม่
    if (isnan(t) || isnan(h))
    {
        Serial.println("Failed to read DHT11!"); // ถ้าอ่านค่าไม่ได้
        return;                                  // ออกจาก loop ครั้งนี้
    }

    // แสดงผลค่าที่อ่านได้
    Serial.println("====================DHT11====================");
    Serial.print("Temp: "); 
    Serial.print(t); 
    Serial.print(" C  Humi: "); 
    Serial.print(h); 
    Serial.println(" %RH");
    
    delay(2000); // รอ 2 วินาทีก่อนอ่านค่าครั้งถัดไป (DHT11 ไม่ควรอ่านเร็วเกิน)
}

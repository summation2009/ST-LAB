#include <Arduino.h>

// -------------------------------------------------------------
// กำหนดขา LDR
// -------------------------------------------------------------
int LDR = 34;          // ขา ADC สำหรับอ่านค่า LDR
int LDR_Value = 0;     // ตัวแปรเก็บค่า LDR


void setup()
{
    Serial.begin(115200);  // เปิด Serial Monitor
    pinMode(LDR, INPUT);   // ตั้งขา LDR เป็น INPUT (สำหรับ ADC)
}

void loop()
{
    // อ่านค่าแรงดันจาก LDR (0–4095 สำหรับ ESP32 ADC 12-bit)
    LDR_Value = analogRead(LDR);

    // แสดงผลบน Serial Monitor
    Serial.println("====================LDR====================");
    Serial.print("LDR : ");
    Serial.println(LDR_Value);

    delay(50); // อ่านค่าใหม่ทุก 50 ms
}

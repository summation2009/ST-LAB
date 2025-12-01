#include <Arduino.h>

// -------------------------------------------------------------
// กำหนดขา IR sensor
// -------------------------------------------------------------
#define INFRARED 16

int count = 0; // ตัวแปรเก็บจำนวนครั้งที่ IR ถูกตรวจจับ


void setup()
{
    Serial.begin(115200);   // เปิด Serial Monitor
    pinMode(INFRARED, INPUT); // ตั้งขา IR เป็น INPUT
}


// -------------------------------------------------------------
// ตรวจจับการเปลี่ยนสถานะของ IR
// -------------------------------------------------------------
void loop()
{
    int irVal = digitalRead(INFRARED); // อ่านค่าสัญญาณจาก IR sensor
    static int lastIR = HIGH;          // เก็บสถานะ IR ก่อนหน้า (เริ่ม HIGH)

    // --- ตรวจสอบการเปลี่ยนจาก LOW → HIGH ---
    // เพิ่ม count เฉพาะตอนที่มีวัตถุผ่าน (IR สลับจาก LOW เป็น HIGH)
    if (irVal == HIGH && lastIR == LOW)
    {
        count++;                       // เพิ่มจำนวน
        Serial.print("Count = ");      
        Serial.println(count);         // แสดงผลบน Serial Monitor
    }

    // อัปเดตสถานะ IR ก่อนหน้า
    lastIR = irVal;

    delay(50); // หน่วงเวลา 50 ms ลดการเด้งสัญญาณ (debounce)
}

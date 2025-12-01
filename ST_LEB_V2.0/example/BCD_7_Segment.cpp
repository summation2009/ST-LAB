#include <Arduino.h>

// -------------------------------------------------------------
// GPIO Pins for 7-segment digit : หลักสิบ (tens digit)
// 4-bit BCD สำหรับแสดงตัวเลข 0–9
// -------------------------------------------------------------
#define TENS_A 16
#define TENS_B 17
#define TENS_C 18
#define TENS_D 19

// -------------------------------------------------------------
// GPIO Pins for 7-segment digit : หลักหน่วย (units digit)
// -------------------------------------------------------------
#define UNITS_A 12
#define UNITS_B 32
#define UNITS_C 25
#define UNITS_D 27


// -------------------------------------------------------------
// ฟังก์ชันแสดงผลตัวเลขแบบ BCD บน 7-segment ทั้งสองหลัก
// tens  = เลขหลักสิบ  (0–9)
// units = เลขหลักหน่วย (0–9)
// -------------------------------------------------------------
void displayValue(int tens, int units)
{
    // ----- 7-segment หลักสิบ -----
    digitalWrite(TENS_A, tens & 0x1);           // bit 0
    digitalWrite(TENS_B, (tens >> 1) & 0x1);    // bit 1
    digitalWrite(TENS_C, (tens >> 2) & 0x1);    // bit 2
    digitalWrite(TENS_D, (tens >> 3) & 0x1);    // bit 3

    // ----- 7-segment หลักหน่วย -----
    digitalWrite(UNITS_A, units & 0x1);        // bit 0
    digitalWrite(UNITS_B, (units >> 1) & 0x1); // bit 1
    digitalWrite(UNITS_C, (units >> 2) & 0x1); // bit 2
    digitalWrite(UNITS_D, (units >> 3) & 0x1); // bit 3
}


// -------------------------------------------------------------
// ตั้งค่าเริ่มต้น
// -------------------------------------------------------------
void setup()
{
    Serial.begin(115200);

    // ตั้งขา OUTPUT สำหรับหลักสิบ
    pinMode(TENS_A, OUTPUT);
    pinMode(TENS_B, OUTPUT);
    pinMode(TENS_C, OUTPUT);
    pinMode(TENS_D, OUTPUT);

    // ตั้งขา OUTPUT สำหรับหลักหน่วย
    pinMode(UNITS_A, OUTPUT);
    pinMode(UNITS_B, OUTPUT);
    pinMode(UNITS_C, OUTPUT);
    pinMode(UNITS_D, OUTPUT);
}


// -------------------------------------------------------------
// Loop หลัก: นับเลข 00 → 99 แล้ววนกลับ
// -------------------------------------------------------------
void loop()
{
    for (int number = 0; number < 100; number++)
    {
        int tens = number / 10;   // คำนวณหลักสิบ เช่น 57 → 5
        int units = number % 10;  // คำนวณหลักหน่วย เช่น 57 → 7

        displayValue(tens, units); // แสดงค่าบน 7-segment ทั้งสองตัว

        delay(1000);               // แสดงเลขใหม่ทุก 1 วินาที
    }
}

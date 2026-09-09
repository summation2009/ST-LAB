#include <Arduino.h>

// -------------------------------------------------------------
// กำหนดขาสำหรับสวิตช์ 4 ปุ่ม
// -------------------------------------------------------------
#define SW1 16
#define SW2 17
#define SW3 18
#define SW4 19

void setup() {
    Serial.begin(115200); // เปิด Serial Monitor

    // ตั้งสวิตช์เป็น INPUT_PULLUP
    // หมายความว่าเมื่อไม่ได้กดจะอ่าน HIGH, กดแล้วอ่าน LOW
    pinMode(SW1, INPUT_PULLUP);
    pinMode(SW2, INPUT_PULLUP);
    pinMode(SW3, INPUT_PULLUP);
    pinMode(SW4, INPUT_PULLUP);
}

void loop() {
    // อ่านค่าจากสวิตช์
    int s1 = digitalRead(SW1);
    int s2 = digitalRead(SW2);
    int s3 = digitalRead(SW3);
    int s4 = digitalRead(SW4);

    // ตรวจสอบสวิตช์แต่ละตัว
    if (s1 == LOW) {
        Serial.println("SW1 PRESSED"); // กดแล้วแสดงข้อความ
    }

    if (s2 == LOW) {
        Serial.println("SW2 PRESSED");
    }

    if (s3 == LOW) {
        Serial.println("SW3 PRESSED");
    }

    if (s4 == LOW) {
        Serial.println("SW4 PRESSED");
    }

    delay(100); // หน่วงเวลา 100 ms เพื่อป้องกันการอ่านซ้ำ/สัญญาณกระพริบ
}

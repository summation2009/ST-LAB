#include <Arduino.h>

// -------------------------------------------------------------
// Pin และ Channel สำหรับ Buzzer
// -------------------------------------------------------------
#define BUZZER 18      // ขาเชื่อมต่อ Buzzer
#define BUZZER_CH 0    // channel ของ LEDC (0–15)

void setup()
{
    Serial.begin(115200); // เปิด serial monitor

    // ตั้งค่า PWM สำหรับ BUZZER
    // ledcSetup(CH, ความถี่เริ่มต้น, ความละเอียด)
    // ความละเอียด 8 บิต → ค่า duty 0–255
    ledcSetup(BUZZER_CH, 2000, 8);

    // ผูก channel เข้ากับขา BUZZER
    ledcAttachPin(BUZZER, BUZZER_CH);
}

void loop()
{
    Serial.println("BUZZER 800");
    
    // ส่งสัญญาณเสียงความถี่ 800 Hz
    ledcWriteTone(BUZZER_CH, 800);
    delay(1000); // เปิดเสียง 1 วินาที

    Serial.println("BUZZER 0");

    // ปิดเสียง (ส่ง tone = 0)
    ledcWriteTone(BUZZER_CH, 0);
    delay(1000); // ปิดเสียง 1 วินาที
}

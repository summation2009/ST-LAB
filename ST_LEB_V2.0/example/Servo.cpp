#include <Arduino.h>
#include <ESP32Servo.h>

// -------------------------------------------------------------
// กำหนดขาสำหรับ Servo
// -------------------------------------------------------------
int SERVO_PIN = 23;
Servo myservo;  // สร้างอ๊อปเจ็กต์ Servo

void setup()
{
    Serial.begin(115200); // เปิด Serial Monitor

    // จอง Timer สำหรับ PWM Servo (ESP32 ต้องจอง 4 timers)
    ESP32PWM::allocateTimer(0);
    ESP32PWM::allocateTimer(1);
    ESP32PWM::allocateTimer(2);
    ESP32PWM::allocateTimer(3);

    // ตั้งค่า Servo ให้ทำงานที่ 50 Hz
    myservo.setPeriodHertz(50);

    // attach Servo กับพิน 23, min=500us, max=2400us
    myservo.attach(SERVO_PIN, 500, 2400);
}

void loop()
{
    // หมุน Servo จาก 0° → 180°
    for (int pos = 0; pos <= 180; pos += 1)
    {
        myservo.write(pos); // ส่งมุมให้ Servo
        delay(10);          // หน่วงเวลา 10 ms
    }

    // หมุน Servo จาก 180° → 0°
    for (int pos = 180; pos >= 0; pos -= 1)
    {
        myservo.write(pos); // ส่งมุมให้ Servo
        delay(10);          // หน่วงเวลา 10 ms
    }
}

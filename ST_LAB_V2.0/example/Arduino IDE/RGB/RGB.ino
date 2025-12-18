#include <Arduino.h>

// -------------------------------------------------------------
// กำหนดขาสำหรับ RGB LED
// -------------------------------------------------------------
const int RED_Pin = 32;    // พินสำหรับไฟสีแดง
const int GREEN_Pin = 12;  // พินสำหรับไฟสีเขียว
const int BLUE_Pin = 27;   // พินสำหรับไฟสีน้ำเงิน


// -------------------------------------------------------------
// ฟังก์ชันสำหรับตั้งค่าสี RGB
// red, green, blue = 0–255 (0=ปิด, 255=เต็ม)
// -------------------------------------------------------------
void setRGBColor(int red, int green, int blue) {
    // ตั้งค่า PWM เพื่อควบคุมความสว่างของแต่ละสี
    analogWrite(RED_Pin, red);
    analogWrite(GREEN_Pin, green);
    analogWrite(BLUE_Pin, blue);
}

void setup()
{
    Serial.begin(115200); // เปิด Serial Monitor

    // ตั้งขา RGB LED เป็น OUTPUT
    pinMode(RED_Pin, OUTPUT);
    pinMode(GREEN_Pin, OUTPUT);
    pinMode(BLUE_Pin, OUTPUT);
}

void loop()
{
    setRGBColor(0, 255, 255);   // สีแดง
    delay(500);

    setRGBColor(255, 0, 255);   // สีเขียว
    delay(500);

    setRGBColor(255, 255, 0);   // สีน้ำเงิน
    delay(500);

    setRGBColor(0, 0, 255); // สีเหลือง
    delay(500);

    setRGBColor(255, 0, 0); // สีฟ้าอ่อน
    delay(500);

    setRGBColor(0, 255, 0); // สีม่วง
    delay(500);

    setRGBColor(0, 0, 0); // สีขาว
    delay(500);
}

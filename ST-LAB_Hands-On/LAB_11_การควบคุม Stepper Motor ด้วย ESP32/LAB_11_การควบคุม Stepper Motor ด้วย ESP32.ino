/* ST-LAB (ESP32) - Example Code
 LAB11.1 : Stepper Motor
*/
#include <Arduino.h> // ไลบรารีหลักของ Arduino (จำเป็นสำหรับ ESP32/PlatformIO บางกรณี)

const int IN1 = 16; // ขา GPIO16 ต่อกับขดลวดชุดที่ 1 ของสเต็ปเปอร์
const int IN2 = 17; // ขา GPIO17 ต่อกับขดลวดชุดที่ 2
const int IN3 = 18; // ขา GPIO18 ต่อกับขดลวดชุดที่ 3
const int IN4 = 19; // ขา GPIO19 ต่อกับขดลวดชุดที่ 4

// ตารางลำดับการกระตุ้นขดลวดแบบ Half-step (8 จังหวะต่อรอบลำดับ)
const uint8_t seq[8][4] = {
{1, 0, 0, 0}, // Step 0: เปิดเฉพาะขดลวด IN1
{1, 1, 0, 0}, // Step 1: เปิด IN1 และ IN2 พร้อมกัน
{0, 1, 0, 0}, // Step 2: เปิดเฉพาะขดลวด IN2
{0, 1, 1, 0}, // Step 3: เปิด IN2 และ IN3 พร้อมกัน
{0, 0, 1, 0}, // Step 4: เปิดเฉพาะขดลวด IN3
{0, 0, 1, 1}, // Step 5: เปิด IN3 และ IN4 พร้อมกัน
{0, 0, 0, 1}, // Step 6: เปิดเฉพาะขดลวด IN4
{1, 0, 0, 1} // Step 7: เปิด IN4 และ IN1 พร้อมกัน
};

// ฟังก์ชันสั่งเปิด/ปิดขดลวดทั้ง 4 เส้น
void setCoils(uint8_t a, uint8_t b, uint8_t c, uint8_t d)
{
digitalWrite(IN1, a); // ส่งสถานะ HIGH/LOW ไปยัง IN1
digitalWrite(IN2, b); // ส่งสถานะ HIGH/LOW ไปยัง IN2
digitalWrite(IN3, c); // ส่งสถานะ HIGH/LOW ไปยัง IN3
digitalWrite(IN4, d); // ส่งสถานะ HIGH/LOW ไปยัง IN4
}

// สั่งหมุนมอเตอร์ 1 สเต็ป ตามลำดับที่กำหนด
void stepOnce(int idx)
{
idx = (idx + 8) % 8;
// ทำให้ค่า index อยู่ในช่วง 0–7 เสมอ (รองรับค่าติดลบ)
setCoils(
seq[idx][0], // สถานะขดลวด IN1
seq[idx][1], // สถานะขดลวด IN2
seq[idx][2], // สถานะขดลวด IN3
seq[idx][3] // สถานะขดลวด IN4
);
}
void setup()
{
pinMode(IN1, OUTPUT); // ตั้งค่า IN1 เป็นขาเอาต์พุต
pinMode(IN2, OUTPUT); // ตั้งค่า IN2 เป็นขาเอาต์พุต
pinMode(IN3, OUTPUT); // ตั้งค่า IN3 เป็นขาเอาต์พุต
pinMode(IN4, OUTPUT); // ตั้งค่า IN4 เป็นขาเอาต์พุต
}

void loop()
{
static int i = 0; // เก็บตำแหน่งสเต็ปปัจจุบัน (จำค่าไว้ระหว่างรอบ loop)
// ===== หมุนตามเข็มนาฬิกา =====
for (int k = 0; k < 400; k++)
{
stepOnce(i++); // เพิ่มลำดับ index เพื่อหมุนไปข้างหน้า
delay(3); // หน่วงเวลา 3 ms ควบคุมความเร็วการหมุน
}
delay(500); // หยุดพัก 0.5 วินาที ก่อนเปลี่ยนทิศทาง
// ===== หมุนทวนเข็มนาฬิกา =====
for (int k = 0; k < 400; k++)
{
stepOnce(i--); // ลดลำดับ index เพื่อหมุนย้อนกลับ
delay(3); // หน่วงเวลา 3 ms ควบคุมความเร็วการหมุน
}
delay(500); // หยุดพักก่อนเริ่มรอบใหม่
}
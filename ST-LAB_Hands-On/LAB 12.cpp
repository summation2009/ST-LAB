/* ST-LAB (ESP32) - Example Code
 LAB12 : Servo Motor Control
*/
#include <ESP32Servo.h> // เรียกใช้งานไลบรารี Servo สำหรับ ESP32

const int SERVO_PIN = 23; // กำหนด GPIO23 เป็นขาควบคุม Servo
Servo myServo; // สร้างอ็อบเจกต์ Servo

void setup() {
myServo.setPeriodHertz(50); // ตั้งความถี่ PWM ที่ 50Hz (มาตรฐาน Servo)
myServo.attach(SERVO_PIN, // ผูก Servo กับ GPIO23
500, // พัลส์ต่ำสุด 500us (0 องศา)
2400); // พัลส์สูงสุด 2400us (180 องศา)
}

void loop() {
for (int angle = 0; angle <= 180; angle++) { // หมุน Servo จาก 0 ถึง 180 องศา
myServo.write(angle); // สั่ง Servo หมุนไปยังมุมที่กำหนด
delay(10); // หน่วงเวลาให้ Servo เคลื่อนที่
}
for (int angle = 180; angle >= 0; angle--) { // หมุน Servo กลับจาก 180 ถึง 0
myServo.write(angle); // สั่ง Servo หมุนกลับ
delay(10); // หน่วงเวลา
}
}
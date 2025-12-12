#include <Arduino.h>
#include <Stepper.h>

// -------------------------------------------------------------
// การหมุน 1 รอบของมอเตอร์ 28BYJ-48
// ใช้โหมด full step = 2048 ขั้นตอน สำหรับหมุน 360 องศา
// -------------------------------------------------------------
const int stepsPerRevolution = 2048;

// -------------------------------------------------------------
// สร้างอ๊อปเจ็กต์ Stepper
// note: ลำดับพินตาม wiring ของมอเตอร์ 28BYJ-48
// -------------------------------------------------------------
Stepper myStepper = Stepper(stepsPerRevolution, 16, 17, 18, 19);

void setup() {

    Serial.begin(115200); // เปิด Serial Monitor

    // ตั้งค่าความเร็วสเต็ปเปอร์ (rpm)
    // สเต็ปเปอร์ 28BYJ-48 5V ควรใช้ประมาณ 10–15 rpm
    myStepper.setSpeed(15);
}

void loop() {

    // หมุนไปข้างหน้า 1 รอบ
    myStepper.step(stepsPerRevolution);
    delay(500); // หน่วงเวลา 0.5 วินาที

    // หมุนย้อนกลับ 1 รอบ
    myStepper.step(-stepsPerRevolution);
    delay(500); // หน่วงเวลา 0.5 วินาที
}

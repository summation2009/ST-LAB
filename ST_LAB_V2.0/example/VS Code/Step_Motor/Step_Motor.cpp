#include <Arduino.h>

// -------------------------------------------------------------
// กำหนดขาที่ใช้ควบคุม Stepper Motor (4 สาย)
// ต่อเข้ากับ ULN2003 / L298 / Driver แบบ 4 Phase
// -------------------------------------------------------------
int motorPin1 = 16;   // Coil A
int motorPin2 = 17;   // Coil B
int motorPin3 = 18;   // Coil C
int motorPin4 = 19;   // Coil D

// -------------------------------------------------------------
// ความเร็วในการหมุน (delay ต่อ 1 step)
// ค่ายิ่งน้อย → หมุนเร็ว
// -------------------------------------------------------------
int motorSpeed = 4;   // หน่วย: ms


// -------------------------------------------------------------
// ฟังก์ชันหมุนทวนเข็มนาฬิกา (Counterclockwise)
// ลำดับการจ่ายไฟแบบ Full-step
// -------------------------------------------------------------
void counterclockwise() {

  // Step 1
  digitalWrite(motorPin1, HIGH); 
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);  
  digitalWrite(motorPin4, LOW);
  delay(motorSpeed);

  // Step 2
  digitalWrite(motorPin1, LOW);  
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);  
  digitalWrite(motorPin4, LOW);
  delay(motorSpeed);

  // Step 3
  digitalWrite(motorPin1, LOW);  
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH); 
  digitalWrite(motorPin4, LOW);
  delay(motorSpeed);

  // Step 4
  digitalWrite(motorPin1, LOW);  
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);  
  digitalWrite(motorPin4, HIGH);
  delay(motorSpeed);
}


// -------------------------------------------------------------
// ฟังก์ชันหมุนตามเข็มนาฬิกา (Clockwise)
// ลำดับการจ่ายไฟย้อนกลับจาก CCW
// -------------------------------------------------------------
void clockwise() {

  // Step 1
  digitalWrite(motorPin1, LOW);  
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);  
  digitalWrite(motorPin4, HIGH);
  delay(motorSpeed);

  // Step 2
  digitalWrite(motorPin1, LOW);  
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH); 
  digitalWrite(motorPin4, LOW);
  delay(motorSpeed);

  // Step 3
  digitalWrite(motorPin1, LOW);  
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);  
  digitalWrite(motorPin4, LOW);
  delay(motorSpeed);

  // Step 4
  digitalWrite(motorPin1, HIGH); 
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);  
  digitalWrite(motorPin4, LOW);
  delay(motorSpeed);
}


// -------------------------------------------------------------
// ฟังก์ชันหยุดมอเตอร์
// ตัดไฟทุกขดลวด
// -------------------------------------------------------------
void stopMotor() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
}


// -------------------------------------------------------------
// setup() – ตั้งค่าเริ่มต้น
// -------------------------------------------------------------
void setup() {

  // ตั้งขาควบคุม Stepper เป็น OUTPUT
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
}


// -------------------------------------------------------------
// loop() – การทำงานหลัก
// -------------------------------------------------------------
void loop() {

  // ---------------------------------------------------------
  // หมุนทวนเข็มนาฬิกาประมาณ 10 วินาที
  // 1 รอบ = 4 steps
  // 2500 × 4 ms ≈ 10 วินาที
  // ---------------------------------------------------------
  for (int i = 0; i < 2500; i++) {
    counterclockwise();
  }

  // ---------------------------------------------------------
  // หมุนตามเข็มนาฬิกาประมาณ 10 วินาที
  // ---------------------------------------------------------
  for (int i = 0; i < 2500; i++) {
    clockwise();
  }

  // ---------------------------------------------------------
  // หยุดมอเตอร์ 2 วินาที
  // ---------------------------------------------------------
  stopMotor();
  delay(2000);
}

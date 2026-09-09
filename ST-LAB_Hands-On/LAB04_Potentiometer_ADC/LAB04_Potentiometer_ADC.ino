/*
  ST-LAB v2.0 (ESP32) - Example Code (Thai Commented)  // คำสั่ง/การตั้งค่าในโปรแกรม
  หมายเหตุ:  // คำสั่ง/การตั้งค่าในโปรแกรม
  - กรุณาแก้ค่า WiFi / Broker / Server ให้ตรงกับหน้างานก่อนใช้งานจริง  // คำสั่ง/การตั้งค่าในโปรแกรม
  - ผังขา (GPIO) ยึดตามสเปกที่ล็อกไว้ในเอกสารประกอบการสอน  // คำสั่ง/การตั้งค่าในโปรแกรม
*/


#define POT_PIN 35   // ADC (Potentiometer)
#define LED_PIN 2  // กำหนดค่าคงที่/ชื่อพินเพื่อใช้งานสะดวก

void setup() {  // ฟังก์ชันเริ่มต้น ทำงานครั้งเดียวเมื่อบอร์ดเริ่มทำงาน
  Serial.begin(115200);  // เริ่มต้นพอร์ต Serial สำหรับดีบัก
  pinMode(LED_PIN, OUTPUT);  // กำหนดโหมดการทำงานของขา GPIO

  // ตั้งความละเอียด ADC (ESP32 default 12-bit = 0..4095)
  analogReadResolution(12);  // ตั้งความละเอียด ADC ของ ESP32
  Serial.println("LAB04: Potentiometer ADC Started");  // คำสั่ง/การตั้งค่าในโปรแกรม
}  // ขอบเขตบล็อกคำสั่ง

void loop() {  // ฟังก์ชันหลัก ทำงานวนซ้ำตลอดเวลา
  int v = analogRead(POT_PIN);          // 0..4095
  float percent = (v / 4095.0f) * 100.0f;  // คำสั่ง/การตั้งค่าในโปรแกรม

  // ตัวอย่าง: เปิด LED เมื่อหมุนเกิน 50%
  digitalWrite(LED_PIN, (percent > 50.0f) ? HIGH : LOW);  // สั่งให้ขา GPIO ออกค่า HIGH/LOW

  Serial.print("POT="); Serial.print(v);  // คำสั่ง/การตั้งค่าในโปรแกรม
  Serial.print(" ("); Serial.print(percent, 1); Serial.println("%)");  // คำสั่ง/การตั้งค่าในโปรแกรม

  delay(200);  // หน่วงเวลา (มิลลิวินาที)
}  // ขอบเขตบล็อกคำสั่ง

/*
  ST-LAB v2.0 (ESP32) - Example Code (Thai Commented)  // คำสั่ง/การตั้งค่าในโปรแกรม
  หมายเหตุ:  // คำสั่ง/การตั้งค่าในโปรแกรม
  - กรุณาแก้ค่า WiFi / Broker / Server ให้ตรงกับหน้างานก่อนใช้งานจริง  // คำสั่ง/การตั้งค่าในโปรแกรม
  - ผังขา (GPIO) ยึดตามสเปกที่ล็อกไว้ในเอกสารประกอบการสอน  // คำสั่ง/การตั้งค่าในโปรแกรม
*/


#define LED_PIN 2  // กำหนดค่าคงที่/ชื่อพินเพื่อใช้งานสะดวก
#define SW1_PIN 16  // กำหนดค่าคงที่/ชื่อพินเพื่อใช้งานสะดวก
#define SW2_PIN 17  // กำหนดค่าคงที่/ชื่อพินเพื่อใช้งานสะดวก
#define SW3_PIN 18  // กำหนดค่าคงที่/ชื่อพินเพื่อใช้งานสะดวก
#define SW4_PIN 19  // กำหนดค่าคงที่/ชื่อพินเพื่อใช้งานสะดวก

// สวิตช์บนบอร์ดมักต่อแบบกดแล้วลง GND (Active LOW)
// ใช้ INPUT_PULLUP เพื่อเปิด Pull-up ภายใน
void setup() {  // ฟังก์ชันเริ่มต้น ทำงานครั้งเดียวเมื่อบอร์ดเริ่มทำงาน
  Serial.begin(115200);  // เริ่มต้นพอร์ต Serial สำหรับดีบัก

  pinMode(LED_PIN, OUTPUT);  // กำหนดโหมดการทำงานของขา GPIO
  pinMode(SW1_PIN, INPUT_PULLUP);  // กำหนดโหมดการทำงานของขา GPIO
  pinMode(SW2_PIN, INPUT_PULLUP);  // กำหนดโหมดการทำงานของขา GPIO
  pinMode(SW3_PIN, INPUT_PULLUP);  // กำหนดโหมดการทำงานของขา GPIO
  pinMode(SW4_PIN, INPUT_PULLUP);  // กำหนดโหมดการทำงานของขา GPIO

  Serial.println("LAB02: Digital Input (Switch) Started");  // คำสั่ง/การตั้งค่าในโปรแกรม
}  // ขอบเขตบล็อกคำสั่ง

void loop() {  // ฟังก์ชันหลัก ทำงานวนซ้ำตลอดเวลา
  int sw1 = digitalRead(SW1_PIN);  // อ่านค่าสถานะจากขา GPIO
  int sw2 = digitalRead(SW2_PIN);  // อ่านค่าสถานะจากขา GPIO
  int sw3 = digitalRead(SW3_PIN);  // อ่านค่าสถานะจากขา GPIO
  int sw4 = digitalRead(SW4_PIN);  // อ่านค่าสถานะจากขา GPIO

  // ตัวอย่าง: กด SW1 ให้ LED ติด (Active LOW)
  digitalWrite(LED_PIN, (sw1 == LOW) ? HIGH : LOW);  // สั่งให้ขา GPIO ออกค่า HIGH/LOW

  Serial.print("SW1="); Serial.print(sw1 == LOW ? "PRESSED" : "RELEASED");  // คำสั่ง/การตั้งค่าในโปรแกรม
  Serial.print(" | SW2="); Serial.print(sw2 == LOW ? "PRESSED" : "RELEASED");  // คำสั่ง/การตั้งค่าในโปรแกรม
  Serial.print(" | SW3="); Serial.print(sw3 == LOW ? "PRESSED" : "RELEASED");  // คำสั่ง/การตั้งค่าในโปรแกรม
  Serial.print(" | SW4="); Serial.println(sw4 == LOW ? "PRESSED" : "RELEASED");  // คำสั่ง/การตั้งค่าในโปรแกรม

  delay(150);  // หน่วงเวลา (มิลลิวินาที)
}  // ขอบเขตบล็อกคำสั่ง

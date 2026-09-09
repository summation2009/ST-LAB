/* ST-LAB (ESP32) - Example Code
 LAB14 : IR Clamp Counter
*/
const int IR_PIN = 33; // กำหนด GPIO33 เป็นขารับสัญญาณ IR Sensor
const int DEBOUNCE_MS = 30; // เวลาหน่วงสำหรับลดสัญญาณรบกวน (ms)

long count = 0; // ตัวแปรเก็บจำนวนการนับ
int lastStable = HIGH; // สถานะที่เสถียรก่อนหน้า
int lastRead = HIGH; // ค่าที่อ่านล่าสุด
unsigned long lastChange = 0; // เวลาที่สถานะเปลี่ยนล่าสุด

void setup() {
Serial.begin(115200); // เริ่มต้นการสื่อสาร Serial
pinMode(IR_PIN, INPUT_PULLUP); // ตั้งค่า IR_PIN เป็น Input พร้อม Pull-up
Serial.println("IR Counter Started"); // แสดงข้อความเริ่มต้น
}

void loop() {
int r = digitalRead(IR_PIN); // อ่านค่าจาก IR Sensor
if (r != lastRead) { // ตรวจสอบว่าค่าที่อ่านเปลี่ยนหรือไม่
lastChange = millis(); // บันทึกเวลาที่เปลี่ยน
lastRead = r; // เก็บค่าที่อ่านล่าสุด
}
if (millis() - lastChange > DEBOUNCE_MS) { // ตรวจสอบว่าคงที่เกินเวลาที่กำหนด
if (lastStable != r) { // หากสถานะเสถียรเปลี่ยน
lastStable = r; // อัปเดตสถานะเสถียร
if (lastStable == HIGH) { // ตรวจจับขอบสัญญาณ HIGH -> LOW
count++; // เพิ่มค่าการนับ
Serial.print("Count = "); // แสดงข้อความ
Serial.println(count); // แสดงค่าการนับ
}
}
}
}
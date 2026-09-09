/* ST-LAB (ESP32) - Example Code
 LAB02 : Digital Input (Switch)
-------------------------------------------------
ตัวอย่างโปรแกรมอ่านค่าสวิตช์ดิจิทัล (Active LOW)
และควบคุม LED พร้อมแสดงผลผ่าน Serial Monitor
*/
// -------------- กำหนดหมายเลขขา GPIO -------------------
#define LED_PIN 2 // กำหนดขา GPIO2 สำหรับควบคุม LED บนบอร์ด
#define SW1_PIN 16 // กำหนดขา GPIO16 สำหรับสวิตช์ SW1
#define SW2_PIN 17 // กำหนดขา GPIO17 สำหรับสวิตช์ SW2
#define SW3_PIN 18 // กำหนดขา GPIO18 สำหรับสวิตช์ SW3
#define SW4_PIN 19 // กำหนดขา GPIO19 สำหรับสวิตช์ SW4
/*
หมายเหตุ:
- สวิตช์ต่อแบบ Active LOW (กด = LOW, ปล่อย = HIGH)
- ใช้ INPUT_PULLUP เพื่อเปิดตัวต้านทาน Pull-up ภายใน ESP32
*/
// -------------------- ฟังก์ชัน setup --------------------
void setup()
{
Serial.begin(115200); // เริ่มต้นการสื่อสาร Serial ที่ความเร็ว 115200 bps
pinMode(LED_PIN, OUTPUT); // กำหนดขา LED เป็นขาเอาต์พุต
pinMode(SW1_PIN, INPUT_PULLUP); // กำหนดขา SW1 เป็นอินพุต พร้อม Pull-up ภายใน
pinMode(SW2_PIN, INPUT_PULLUP); // กำหนดขา SW2 เป็นอินพุต พร้อม Pull-up ภายใน
pinMode(SW3_PIN, INPUT_PULLUP); // กำหนดขา SW3 เป็นอินพุต พร้อม Pull-up ภายใน
pinMode(SW4_PIN, INPUT_PULLUP); // กำหนดขา SW4 เป็นอินพุต พร้อม Pull-up ภายใน
Serial.println("LAB02: Digital Input (Switch) Started");
// แสดงข้อความแจ้งว่าโปรแกรมเริ่มทำงานแล้ว
}

// -------------------- ฟังก์ชัน loop --------------------
void loop()
{
int sw1 = digitalRead(SW1_PIN); // อ่านสถานะสวิตช์ SW1 (HIGH / LOW)
int sw2 = digitalRead(SW2_PIN); // อ่านสถานะสวิตช์ SW2 (HIGH / LOW)
int sw3 = digitalRead(SW3_PIN); // อ่านสถานะสวิตช์ SW3 (HIGH / LOW)
int sw4 = digitalRead(SW4_PIN); // อ่านสถานะสวิตช์ SW4 (HIGH / LOW)
// ถ้า SW1 ถูกกด (LOW) ให้ LED ติด ถ้าไม่กดให้ LED ดับ
digitalWrite(LED_PIN, (sw1 == LOW) ? HIGH : LOW);
// แสดงสถานะของ SW1 ผ่าน Serial Monitor
Serial.print("SW1=");
Serial.print(sw1 == LOW ? "PRESSED" : "RELEASED");
// แสดงสถานะของ SW2 ผ่าน Serial Monitor
Serial.print(" | SW2=");
Serial.print(sw2 == LOW ? "PRESSED" : "RELEASED");
// แสดงสถานะของ SW3 ผ่าน Serial Monitor
Serial.print(" | SW3=");
Serial.print(sw3 == LOW ? "PRESSED" : "RELEASED");
// แสดงสถานะของ SW4 ผ่าน Serial Monitor และขึ้นบรรทัดใหม่
Serial.print(" | SW4=");
Serial.println(sw4 == LOW ? "PRESSED" : "RELEASED");
delay(150); // หน่วงเวลา 150 ms เพื่อลดการอ่านถี่เกินไป
}
/* ST-LAB (ESP32) Example Code
 LAB05 : LDR Analog Input
*/
#define LDR_PIN 34 // กำหนดขา GPIO34 สำหรับอ่านค่า ADC จาก LDR
#define LED_PIN 2 // กำหนดขา GPIO2 สำหรับควบคุม LED

void setup()
{ // ทำงานครั้งเดียวเมื่อเปิดเครื่องหรือรีเซตบอร์ด
Serial.begin(115200); // เริ่มต้นการสื่อสาร Serial ที่ความเร็ว 115200 bps
pinMode(LED_PIN, OUTPUT); // ตั้งค่า LED_PIN เป็นขาเอาต์พุต (ส่งสัญญาณออก)
analogReadResolution(12); // ตั้งค่า ADC ให้มีความละเอียด 12 บิต (ช่วงค่า 0–4095)
Serial.println("LAB05: LDR Analog Input Started"); // แสดงข้อความเริ่มต้นบน Serial Monitor
} // จบฟังก์ชัน setup()

void loop()
{ // ทำงานวนซ้ำตลอดเวลาที่บอร์ดยังเปิดอยู่
int ldr = analogRead(LDR_PIN); // อ่านค่าความเข้มแสงจาก LDR (ช่วงประมาณ 0–4095)
Serial.print("LDR=");
Serial.println(ldr); // แสดงค่าดิบที่อ่านได้จาก ADC
// ตัวอย่างเงื่อนไข: ถ้าค่า ADC ต่ำ (แสงน้อย/มืด) ให้เปิด LED
// หมายเหตุ: ค่าสูงหรือต่ำอาจสลับกัน ขึ้นกับการต่อวงจรแบ่งแรงดัน
digitalWrite(LED_PIN, (ldr < 2000) ? HIGH : LOW); // ควบคุม LED ตามระดับแสงที่ตรวจจับได้
delay(200); // หน่วงเวลา 200 ms เพื่อลดความถี่ในการอ่านค่าและแสดงผล
} // จบฟังก์ชัน loop()
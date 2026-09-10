/* ST-LAB (ESP32) - Example Code
LAB09 : 7-Segment 2 Digit (BCD -> CD4543BE x2)
BCD (8-4-2-1): A=1, B=2, C=4, D=8
*/
#define TENS_A 16 // กำหนดขา GPIO 16 เป็นบิต A (LSB) ของหลักสิบ
#define TENS_B 17 // กำหนดขา GPIO 17 เป็นบิต B ของหลักสิบ
#define TENS_C 18 // กำหนดขา GPIO 18 เป็นบิต C ของหลักสิบ
#define TENS_D 19 // กำหนดขา GPIO 19 เป็นบิต D (MSB) ของหลักสิบ
#define UNITS_A 12 // กำหนดขา GPIO 12 เป็นบิต A (LSB) ของหลักหน่วย
#define UNITS_B 32 // กำหนดขา GPIO 32 เป็นบิต B ของหลักหน่วย
#define UNITS_C 25 // กำหนดขา GPIO 25 เป็นบิต C ของหลักหน่วย
#define UNITS_D 27 // กำหนดขา GPIO 27 เป็นบิต D (MSB) ของหลักหน่วย

// ฟังก์ชันสำหรับส่งค่าตัวเลข 0–9 ออกเป็นรหัส BCD 4 บิต
void writeBCD(int pinA, int pinB, int pinC, int pinD, int n)
{
n = constrain(n, 0, 9); // จำกัดค่า n ให้อยู่ในช่วง 0–9 เท่านั้น
// ส่งค่าบิตแต่ละตำแหน่งของ n ออกไปยังขา GPIO
digitalWrite(pinA, (n >> 0) & 0x01); // บิตที่ 0 (LSB)
digitalWrite(pinB, (n >> 1) & 0x01); // บิตที่ 1
digitalWrite(pinC, (n >> 2) & 0x01); // บิตที่ 2
digitalWrite(pinD, (n >> 3) & 0x01); // บิตที่ 3 (MSB)
}
// ฟังก์ชันแสดงตัวเลข 2 หลัก (00–99)
void show2DigitNumber(int value)
{
value = constrain(value, 0, 99); // จำกัดค่าให้อยู่ในช่วง 0–99
int tens = value / 10; // คำนวณค่าหลักสิบ
int units = value % 10; // คำนวณค่าหลักหน่วย
writeBCD(TENS_A, TENS_B, TENS_C, TENS_D, tens); // ส่งค่าหลักสิบออกเป็น BCD
writeBCD(UNITS_A, UNITS_B, UNITS_C, UNITS_D, units); // ส่งค่าหลักหน่วยออกเป็น BCD
}

void setup()
{
// กำหนดขาหลักสิบเป็นเอาต์พุต
pinMode(TENS_A, OUTPUT);
pinMode(TENS_B, OUTPUT);
pinMode(TENS_C, OUTPUT);
pinMode(TENS_D, OUTPUT);
// กำหนดขาหลักหน่วยเป็นเอาต์พุต
pinMode(UNITS_A, OUTPUT);
pinMode(UNITS_B, OUTPUT);
pinMode(UNITS_C, OUTPUT);
pinMode(UNITS_D, OUTPUT);
show2DigitNumber(0); // แสดงค่าเริ่มต้นเป็น 00
}
void loop()
{
static int n = 0; // ตัวแปรเก็บค่าปัจจุบัน (จำค่าระหว่างรอบ loop)
show2DigitNumber(n); // แสดงค่าปัจจุบันบนจอ 2 หลัก
n = (n + 1) % 100; // เพิ่มค่าทีละ 1 และวนกลับ 0 เมื่อถึง 100
delay(200); // หน่วงเวลา 200 มิลลิวินาที
}
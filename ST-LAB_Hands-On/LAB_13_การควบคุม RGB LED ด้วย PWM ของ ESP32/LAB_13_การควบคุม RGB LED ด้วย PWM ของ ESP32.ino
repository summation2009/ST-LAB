/* ST-LAB (ESP32) - Example Code
LAB13 : RGB LED Control
*/
const int RED_Pin = 32; // กำหนด GPIO32 สำหรับ LED สีแดง
const int GREEN_Pin = 12; // กำหนด GPIO12 สำหรับ LED สีเขียว
const int BLUE_Pin = 27; // กำหนด GPIO27 สำหรับ LED สีน้ำเงิน
const int CH_R = 0; // ช่อง PWM สำหรับสีแดง
const int CH_G = 1; // ช่อง PWM สำหรับสีเขียว
const int CH_B = 2; // ช่อง PWM สำหรับสีน้ำเงิน
const int PWM_FREQ = 5000; // ความถี่ PWM 5kHz
const int PWM_RES = 8; // ความละเอียด PWM 8 บิต (0–255)

void setColor(uint8_t r, uint8_t g, uint8_t b) {
ledcWrite(CH_R, r); // กำหนดความสว่างสีแดง
ledcWrite(CH_G, g); // กำหนดความสว่างสีเขียว
ledcWrite(CH_B, b); // กำหนดความสว่างสีน้ำเงิน
}

void setup() {
ledcSetup(CH_R, PWM_FREQ, PWM_RES); // ตั้งค่า PWM ช่องสีแดง
ledcSetup(CH_G, PWM_FREQ, PWM_RES); // ตั้งค่า PWM ช่องสีเขียว
ledcSetup(CH_B, PWM_FREQ, PWM_RES); // ตั้งค่า PWM ช่องสีน้ำเงิน
ledcAttachPin(RED_Pin, CH_R); // ผูก PWM สีแดงกับ GPIO32
ledcAttachPin(GREEN_Pin, CH_G); // ผูก PWM สีเขียวกับ GPIO12
ledcAttachPin(BLUE_Pin, CH_B); // ผูก PWM สีน้ำเงินกับ GPIO27
}

void loop() {
setColor(255, 0, 0); // แสดงสีแดง
delay(500); // หน่วงเวลา
setColor(0, 255, 0); // แสดงสีเขียว
delay(500); // หน่วงเวลา
setColor(0, 0, 255); // แสดงสีน้ำเงิน
delay(500); // หน่วงเวลา
setColor(180, 0, 180); // แสดงสีม่วง (ผสม)
delay(500); // หน่วงเวลา
setColor(0, 0, 0); // ปิดไฟ LED
delay(500); // หน่วงเวลา
}
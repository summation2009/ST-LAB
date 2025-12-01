#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include "LedControl.h"

// --- MAX7219 ---
#define DIN_PIN 23      // ขา Data In
#define CLK_PIN 18      // ขา Clock
#define LOAD_PIN 5      // ขา Load/CS
LedControl lc = LedControl(DIN_PIN, CLK_PIN, LOAD_PIN, 1);  // กำหนด MAX7219 จำนวน 1 โมดูล

// --- WiFi config ---
const char* ssid = "xxxxxx";       // ชื่อ WiFi ที่จะเชื่อมต่อ
const char* password = "xxxxxx";     // รหัสผ่าน WiFi

// --- NTP ---
WiFiUDP ntpUDP;    // ใช้ UDP สำหรับดึงเวลา NTP
NTPClient timeClient(ntpUDP, "pool.ntp.org", 7*3600, 60000);  
// pool.ntp.org = server เวลา
// 7*3600 = GMT+7
// 60000 = อัปเดตทุก 60 วินาที

// --- เวลา fallback ---
unsigned long lastUpdate = 0; // เวลาที่ NTP ถูกอัปเดตล่าสุด (ms)
int lastHour = 16;            // ค่าเริ่มต้นชั่วโมง (ใช้ถ้า NTP ไม่มา)
int lastMinute = 55;          // ค่าเริ่มต้นนาที (ใช้ถ้า NTP ไม่มา)


// ฟังก์ชันแสดงเวลา HHMM บน MAX7219
void showTime(int hour, int minute) {

  // แยกแต่ละหลัก เช่น 16:55 → [1][6][5][5]
  int h1 = hour / 10;      // หลักสิบชั่วโมง
  int h2 = hour % 10;      // หลักหน่วยชั่วโมง
  int m1 = minute / 10;    // หลักสิบนาที
  int m2 = minute % 10;    // หลักหน่วยนาที

  // แสดงตัวเลขลง MAX7219 (decimal=false = ไม่เปิดจุด)
  lc.setDigit(0, 0, h1, false);
  lc.setDigit(0, 1, h2, false);
  lc.setDigit(0, 2, m1, false);
  lc.setDigit(0, 3, m2, false);
}


void setup() {
  Serial.begin(115200);

  // --- ตั้งค่า MAX7219 ---
  lc.shutdown(0, false);   // เปิดการทำงาน
  lc.setIntensity(0, 8);   // ความสว่าง 0–15
  lc.clearDisplay(0);      // ล้างหน้าจอ

  // --- เชื่อมต่อ WiFi ---
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");

  // --- เริ่มระบบ NTP ---
  timeClient.begin();

  // ดึงเวลาครั้งแรก หากสำเร็จ
  if (timeClient.update()) {
    lastHour = timeClient.getHours();       // เก็บชั่วโมง
    lastMinute = timeClient.getMinutes();   // เก็บนาที
    lastUpdate = millis();                  // บันทึกเวลาปัจจุบัน (ms)
    Serial.println("Time obtained from NTP");
  } else {
    Serial.println("Failed to obtain time, fallback to default");
  }
}


void loop() {

  // --- อัปเดตเวลาจาก NTP ทุก 60 วินาที ---
  if (millis() - lastUpdate >= 60000) {
    if (timeClient.update()) {
      lastHour = timeClient.getHours();      // ได้เวลาชั่วโมงจริง
      lastMinute = timeClient.getMinutes();  // ได้นาทีจริง
      Serial.println("NTP time updated");
    }
    lastUpdate = millis();   // รีเซ็ตการจับเวลา
  }


  // --- Fallback: ถ้า NTP ไม่มาเพิ่มเวลาเองทุก 1 นาที ---
  static unsigned long lastTick = 0;
  if (millis() - lastTick >= 60000) {
    lastMinute++;            // เพิ่มนาที
    if (lastMinute >= 60) {  // เช็คครบ 60 นาที
      lastMinute = 0;
      lastHour++;            // เพิ่มชั่วโมง
      if (lastHour >= 24) lastHour = 0;  // ชั่วโมงวน
    }
    lastTick = millis();     // รีเซ็ตตัวจับเวลา
  }

  // --- แสดงเวลาแบบนิ่ง ๆ HHMM ---
  showTime(lastHour, lastMinute);

  delay(1000);  // อัปเดตหน้าจอทุก 1 วินาที (ไม่กระพริบ)
}

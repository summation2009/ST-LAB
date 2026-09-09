/*
  ST-LAB v2.0 (ESP32) - Example Code (Thai Commented)  // คำสั่ง/การตั้งค่าในโปรแกรม
  หมายเหตุ:  // คำสั่ง/การตั้งค่าในโปรแกรม
  - กรุณาแก้ค่า WiFi / Broker / Server ให้ตรงกับหน้างานก่อนใช้งานจริง  // คำสั่ง/การตั้งค่าในโปรแกรม
  - ผังขา (GPIO) ยึดตามสเปกที่ล็อกไว้ในเอกสารประกอบการสอน  // คำสั่ง/การตั้งค่าในโปรแกรม
*/


#include <WiFi.h>  // เรียกใช้งานไลบรารีที่จำเป็น
#include <HTTPClient.h>  // เรียกใช้งานไลบรารีที่จำเป็น

const char* ssid = "YOUR_WIFI";  // ประกาศค่าคงที่สำหรับการตั้งค่า
const char* password = "YOUR_PASS";  // ประกาศค่าคงที่สำหรับการตั้งค่า

const char* apiUrl = "http://example.com/api/telemetry";

void setup() {  // ฟังก์ชันเริ่มต้น ทำงานครั้งเดียวเมื่อบอร์ดเริ่มทำงาน
  Serial.begin(115200);  // เริ่มต้นพอร์ต Serial สำหรับดีบัก
  WiFi.begin(ssid, password);  // เริ่มเชื่อมต่อเครือข่าย Wi‑Fi
  while (WiFi.status() != WL_CONNECTED) {  // ตรวจสอบสถานะการเชื่อมต่อ Wi‑Fi
    delay(300);  // หน่วงเวลา (มิลลิวินาที)
  }  // ขอบเขตบล็อกคำสั่ง
}  // ขอบเขตบล็อกคำสั่ง

void loop() {  // ฟังก์ชันหลัก ทำงานวนซ้ำตลอดเวลา
  if (WiFi.status() == WL_CONNECTED) {  // ตรวจสอบสถานะการเชื่อมต่อ Wi‑Fi
    HTTPClient http;  // สร้างอ็อบเจ็กต์ HTTP client
    http.begin(apiUrl);  // กำหนด URL/เริ่มต้นการเรียก API
    http.addHeader("Content-Type", "application/json");  // กำหนด Header ของ HTTP

    String payload = "{";  // ประกาศตัวแปรชนิด String
    payload += "\"device_id\":\"stlab01\",";  // คำสั่ง/การตั้งค่าในโปรแกรม
    payload += "\"ts\":" + String((uint32_t)(millis()/1000)) + ",";  // คำสั่ง/การตั้งค่าในโปรแกรม
    payload += "\"temp_c\":28.5,";  // คำสั่ง/การตั้งค่าในโปรแกรม
    payload += "\"hum_pct\":60.0";  // คำสั่ง/การตั้งค่าในโปรแกรม
    payload += "}";  // คำสั่ง/การตั้งค่าในโปรแกรม

    int code = http.POST(payload);  // ส่งข้อมูลด้วย HTTP POST
    Serial.print("HTTP Code: ");  // คำสั่ง/การตั้งค่าในโปรแกรม
    Serial.println(code);  // คำสั่ง/การตั้งค่าในโปรแกรม

    http.end();  // ปิดการใช้งาน HTTP client เพื่อคืนทรัพยากร
  }  // ขอบเขตบล็อกคำสั่ง
  delay(5000);  // หน่วงเวลา (มิลลิวินาที)
}  // ขอบเขตบล็อกคำสั่ง

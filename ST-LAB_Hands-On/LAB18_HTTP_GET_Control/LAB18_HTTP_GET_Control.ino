/*
  ST-LAB v2.0 (ESP32) - Example Code (Thai Commented)  // คำสั่ง/การตั้งค่าในโปรแกรม
  หมายเหตุ:  // คำสั่ง/การตั้งค่าในโปรแกรม
  - กรุณาแก้ค่า WiFi / Broker / Server ให้ตรงกับหน้างานก่อนใช้งานจริง  // คำสั่ง/การตั้งค่าในโปรแกรม
  - ผังขา (GPIO) ยึดตามสเปกที่ล็อกไว้ในเอกสารประกอบการสอน  // คำสั่ง/การตั้งค่าในโปรแกรม
*/


#include <WiFi.h>  // เรียกใช้งานไลบรารีที่จำเป็น
#include <HTTPClient.h>  // เรียกใช้งานไลบรารีที่จำเป็น

#define LED_PIN 2  // กำหนดค่าคงที่/ชื่อพินเพื่อใช้งานสะดวก

const char* ssid = "YOUR_WIFI";  // ประกาศค่าคงที่สำหรับการตั้งค่า
const char* password = "YOUR_PASS";  // ประกาศค่าคงที่สำหรับการตั้งค่า

const char* apiUrl = "http://example.com/api/control";

void setup() {  // ฟังก์ชันเริ่มต้น ทำงานครั้งเดียวเมื่อบอร์ดเริ่มทำงาน
  Serial.begin(115200);  // เริ่มต้นพอร์ต Serial สำหรับดีบัก
  pinMode(LED_PIN, OUTPUT);  // กำหนดโหมดการทำงานของขา GPIO

  WiFi.begin(ssid, password);  // เริ่มเชื่อมต่อเครือข่าย Wi‑Fi
  while (WiFi.status() != WL_CONNECTED) {  // ตรวจสอบสถานะการเชื่อมต่อ Wi‑Fi
    delay(300);  // หน่วงเวลา (มิลลิวินาที)
  }  // ขอบเขตบล็อกคำสั่ง
}  // ขอบเขตบล็อกคำสั่ง

void loop() {  // ฟังก์ชันหลัก ทำงานวนซ้ำตลอดเวลา
  if (WiFi.status() == WL_CONNECTED) {  // ตรวจสอบสถานะการเชื่อมต่อ Wi‑Fi
    HTTPClient http;  // สร้างอ็อบเจ็กต์ HTTP client
    http.begin(apiUrl);  // กำหนด URL/เริ่มต้นการเรียก API

    int code = http.GET();  // ร้องขอข้อมูลด้วย HTTP GET
    if (code == 200) {  // ตรวจสอบเงื่อนไขการทำงาน
      String payload = http.getString();  // ประกาศตัวแปรชนิด String
      if (payload.indexOf("\"led\":1") >= 0) digitalWrite(LED_PIN, HIGH);  // สั่งให้ขา GPIO ออกค่า HIGH/LOW
      else                                   digitalWrite(LED_PIN, LOW);  // สั่งให้ขา GPIO ออกค่า HIGH/LOW

      Serial.println(payload);  // คำสั่ง/การตั้งค่าในโปรแกรม
    } else {  // คำสั่ง/การตั้งค่าในโปรแกรม
      Serial.print("HTTP Error: ");  // คำสั่ง/การตั้งค่าในโปรแกรม
      Serial.println(code);  // คำสั่ง/การตั้งค่าในโปรแกรม
    }  // ขอบเขตบล็อกคำสั่ง

    http.end();  // ปิดการใช้งาน HTTP client เพื่อคืนทรัพยากร
  }  // ขอบเขตบล็อกคำสั่ง
  delay(3000);  // หน่วงเวลา (มิลลิวินาที)
}  // ขอบเขตบล็อกคำสั่ง

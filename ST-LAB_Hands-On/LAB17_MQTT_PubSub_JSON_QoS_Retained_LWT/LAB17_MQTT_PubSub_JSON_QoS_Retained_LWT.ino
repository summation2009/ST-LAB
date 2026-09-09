/*
  ST-LAB v2.0 (ESP32) - Example Code (Thai Commented)  // คำสั่ง/การตั้งค่าในโปรแกรม
  หมายเหตุ:  // คำสั่ง/การตั้งค่าในโปรแกรม
  - กรุณาแก้ค่า WiFi / Broker / Server ให้ตรงกับหน้างานก่อนใช้งานจริง  // คำสั่ง/การตั้งค่าในโปรแกรม
  - ผังขา (GPIO) ยึดตามสเปกที่ล็อกไว้ในเอกสารประกอบการสอน  // คำสั่ง/การตั้งค่าในโปรแกรม
*/


#include <WiFi.h>  // เรียกใช้งานไลบรารีที่จำเป็น
#include <PubSubClient.h>  // เรียกใช้งานไลบรารีที่จำเป็น
#include <ArduinoJson.h>  // เรียกใช้งานไลบรารีที่จำเป็น

#define LED_PIN 2  // กำหนดค่าคงที่/ชื่อพินเพื่อใช้งานสะดวก

const char* ssid = "YOUR_WIFI";  // ประกาศค่าคงที่สำหรับการตั้งค่า
const char* password = "YOUR_PASS";  // ประกาศค่าคงที่สำหรับการตั้งค่า

const char* mqtt_host = "broker.hivemq.com";  // ประกาศค่าคงที่สำหรับการตั้งค่า
const int   mqtt_port = 1883;  // ประกาศค่าคงที่สำหรับการตั้งค่า

const char* topic_cmd = "stlab/control/led";  // ประกาศค่าคงที่สำหรับการตั้งค่า
const char* topic_tlm = "stlab/telemetry/json";  // ประกาศค่าคงที่สำหรับการตั้งค่า

WiFiClient net;  // คำสั่ง/การตั้งค่าในโปรแกรม
PubSubClient mqtt(net);  // คำสั่ง/การตั้งค่าในโปรแกรม

String clientId = "stlab-esp32-001";  // ประกาศตัวแปรชนิด String

void mqttCallback(char* topic, byte* payload, unsigned int length) {  // คำสั่ง/การตั้งค่าในโปรแกรม
  String msg;  // ประกาศตัวแปรชนิด String
  for (unsigned int i = 0; i < length; i++) msg += (char)payload[i];  // วนซ้ำตามจำนวนรอบที่กำหนด

  if (String(topic) == topic_cmd) {  // ตรวจสอบเงื่อนไขการทำงาน
    if (msg == "1") digitalWrite(LED_PIN, HIGH);  // สั่งให้ขา GPIO ออกค่า HIGH/LOW
    else            digitalWrite(LED_PIN, LOW);  // สั่งให้ขา GPIO ออกค่า HIGH/LOW
  }  // ขอบเขตบล็อกคำสั่ง
}  // ขอบเขตบล็อกคำสั่ง

void connectWiFi() {  // คำสั่ง/การตั้งค่าในโปรแกรม
  WiFi.begin(ssid, password);  // เริ่มเชื่อมต่อเครือข่าย Wi‑Fi
  while (WiFi.status() != WL_CONNECTED) {  // ตรวจสอบสถานะการเชื่อมต่อ Wi‑Fi
    delay(300);  // หน่วงเวลา (มิลลิวินาที)
  }  // ขอบเขตบล็อกคำสั่ง
}  // ขอบเขตบล็อกคำสั่ง

void connectMQTT() {  // คำสั่ง/การตั้งค่าในโปรแกรม
  mqtt.setServer(mqtt_host, mqtt_port);  // กำหนดค่า MQTT Broker (Host/Port)
  mqtt.setCallback(mqttCallback);  // กำหนดฟังก์ชัน callback เมื่อมีข้อความเข้า

  while (!mqtt.connected()) {  // วนซ้ำจนกว่าจะเป็นไปตามเงื่อนไข
    const char* willTopic = "stlab/status/lwt";  // ประกาศค่าคงที่สำหรับการตั้งค่า
    const char* willMsg   = "offline";  // ประกาศค่าคงที่สำหรับการตั้งค่า

    if (mqtt.connect(clientId.c_str(), willTopic, 1, true, willMsg)) {  // ตรวจสอบเงื่อนไขการทำงาน
      mqtt.publish("stlab/status/lwt", "online", true);  // ส่งข้อความ (Publish) ไปยัง Topic
      mqtt.subscribe(topic_cmd, 1);  // สมัครรับข้อความ (Subscribe) จาก Topic
    } else {  // คำสั่ง/การตั้งค่าในโปรแกรม
      delay(1000);  // หน่วงเวลา (มิลลิวินาที)
    }  // ขอบเขตบล็อกคำสั่ง
  }  // ขอบเขตบล็อกคำสั่ง
}  // ขอบเขตบล็อกคำสั่ง

void publishTelemetry() {  // คำสั่ง/การตั้งค่าในโปรแกรม
  StaticJsonDocument<128> doc;  // คำสั่ง/การตั้งค่าในโปรแกรม
  doc["device_id"] = "stlab01";  // คำสั่ง/การตั้งค่าในโปรแกรม
  doc["ts"] = (uint32_t)(millis() / 1000);  // คำสั่ง/การตั้งค่าในโปรแกรม
  doc["led"] = digitalRead(LED_PIN);  // อ่านค่าสถานะจากขา GPIO

  char out[128];  // คำสั่ง/การตั้งค่าในโปรแกรม
  size_t n = serializeJson(doc, out);  // คำสั่ง/การตั้งค่าในโปรแกรม

  mqtt.beginPublish(topic_tlm, n, false);  // ส่งข้อความ (Publish) ไปยัง Topic
  mqtt.write((const uint8_t*)out, n);  // คำสั่ง/การตั้งค่าในโปรแกรม
  mqtt.endPublish();  // ส่งข้อความ (Publish) ไปยัง Topic
}  // ขอบเขตบล็อกคำสั่ง

void setup() {  // ฟังก์ชันเริ่มต้น ทำงานครั้งเดียวเมื่อบอร์ดเริ่มทำงาน
  pinMode(LED_PIN, OUTPUT);  // กำหนดโหมดการทำงานของขา GPIO
  Serial.begin(115200);  // เริ่มต้นพอร์ต Serial สำหรับดีบัก

  connectWiFi();  // คำสั่ง/การตั้งค่าในโปรแกรม
  connectMQTT();  // คำสั่ง/การตั้งค่าในโปรแกรม
}  // ขอบเขตบล็อกคำสั่ง

void loop() {  // ฟังก์ชันหลัก ทำงานวนซ้ำตลอดเวลา
  if (WiFi.status() != WL_CONNECTED) connectWiFi();  // ตรวจสอบสถานะการเชื่อมต่อ Wi‑Fi
  if (!mqtt.connected()) connectMQTT();  // ตรวจสอบเงื่อนไขการทำงาน

  mqtt.loop();  // ฟังก์ชันหลัก ทำงานวนซ้ำตลอดเวลา

  static unsigned long last = 0;  // คำสั่ง/การตั้งค่าในโปรแกรม
  if (millis() - last > 2000) {  // ตรวจสอบเงื่อนไขการทำงาน
    last = millis();  // คำสั่ง/การตั้งค่าในโปรแกรม
    publishTelemetry();  // คำสั่ง/การตั้งค่าในโปรแกรม
  }  // ขอบเขตบล็อกคำสั่ง
}  // ขอบเขตบล็อกคำสั่ง

#include <Arduino.h>
#include "ModbusMaster.h"

// -------------------------------------------------------------
// สร้างอ๊อปเจ็กต์ ModbusMaster สำหรับสื่อสารกับอุปกรณ์ Modbus
// -------------------------------------------------------------
ModbusMaster myModbus;

#define SLAVE_ID 1            // ID ของอุปกรณ์ Modbus ที่ต้องการอ่านค่า
#define SLAVE_BAUDRATE 9600   // ความเร็วสื่อสาร (baudrate) ต้องตรงกับเซนเซอร์

void setup()
{
    // Serial0 สำหรับดูค่า debug ผ่าน Serial Monitor
    Serial.begin(115200);

    // Serial2 สำหรับสื่อสาร Modbus
    // RX = GPIO16, TX = GPIO17
    Serial2.begin(SLAVE_BAUDRATE, SERIAL_8N1, 16, 17);

    // เริ่มต้น Modbus ด้วย Slave ID และพอร์ต Serial2
    myModbus.begin(SLAVE_ID, Serial2);
}

void loop()
{
    uint8_t result;      // ตัวแปรเก็บผลลัพธ์การอ่าน
    float Temperature, Humidity;

    // อ่านค่าจาก Holding Register เริ่มที่ 0 จำนวน 15 รีจิสเตอร์
    result = myModbus.readHoldingRegisters(0, 15);

    // ตรวจสอบผลลัพธ์
    if (result == myModbus.ku8MBSuccess) {
        // อ่านค่า Humidity จาก buffer 0 (บางเซนเซอร์ต้องหาร 10 หรือ 100)
        Humidity = myModbus.getResponseBuffer(0);
        // อ่านค่า Temperature จาก buffer 1
        Temperature = myModbus.getResponseBuffer(1);

        // แสดงผลบน Serial Monitor
        Serial.print(Humidity);
        Serial.print(" %RH\t");
        Serial.print(Temperature);
        Serial.println(" *C");
    } else {
        // แสดงข้อความ error หากอ่านค่าไม่สำเร็จ
        Serial.println("error");
    }

    delay(1000); // อ่านค่าใหม่ทุก 1 วินาที
}

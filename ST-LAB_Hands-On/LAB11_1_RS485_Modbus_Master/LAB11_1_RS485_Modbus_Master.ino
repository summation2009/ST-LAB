/*
  ST-LAB v2.0 (ESP32) - Example Code (Thai Commented)  // คำสั่ง/การตั้งค่าในโปรแกรม
  หมายเหตุ:  // คำสั่ง/การตั้งค่าในโปรแกรม
  - กรุณาแก้ค่า WiFi / Broker / Server ให้ตรงกับหน้างานก่อนใช้งานจริง  // คำสั่ง/การตั้งค่าในโปรแกรม
  - ผังขา (GPIO) ยึดตามสเปกที่ล็อกไว้ในเอกสารประกอบการสอน  // คำสั่ง/การตั้งค่าในโปรแกรม
*/


#include <ModbusMaster.h>  // เรียกใช้งานไลบรารีที่จำเป็น

#define RS485_RX 16  // กำหนดค่าคงที่/ชื่อพินเพื่อใช้งานสะดวก
#define RS485_TX 17  // กำหนดค่าคงที่/ชื่อพินเพื่อใช้งานสะดวก

ModbusMaster node;  // สั่งงาน/ตั้งค่าโปรโตคอล Modbus RTU

void setup() {  // ฟังก์ชันเริ่มต้น ทำงานครั้งเดียวเมื่อบอร์ดเริ่มทำงาน
  Serial.begin(115200);  // เริ่มต้นพอร์ต Serial สำหรับดีบัก
  Serial2.begin(9600, SERIAL_8N1, RS485_RX, RS485_TX);  // เริ่มต้น UART2 สำหรับสื่อสารอุปกรณ์ภายนอก

  node.begin(1, Serial2);  // สั่งงาน/ตั้งค่าโปรโตคอล Modbus RTU
  Serial.println("LAB11.1: Modbus RTU Master Started");  // สั่งงาน/ตั้งค่าโปรโตคอล Modbus RTU
}  // ขอบเขตบล็อกคำสั่ง

void loop() {  // ฟังก์ชันหลัก ทำงานวนซ้ำตลอดเวลา
  uint8_t result = node.readHoldingRegisters(0x0000, 2);  // สั่งงาน/ตั้งค่าโปรโตคอล Modbus RTU

  if (result == node.ku8MBSuccess) {  // สั่งงาน/ตั้งค่าโปรโตคอล Modbus RTU
    uint16_t r0 = node.getResponseBuffer(0);  // สั่งงาน/ตั้งค่าโปรโตคอล Modbus RTU
    uint16_t r1 = node.getResponseBuffer(1);  // สั่งงาน/ตั้งค่าโปรโตคอล Modbus RTU

    Serial.print("HR[0x0000]="); Serial.print(r0);  // คำสั่ง/การตั้งค่าในโปรแกรม
    Serial.print(" | HR[0x0001]="); Serial.println(r1);  // คำสั่ง/การตั้งค่าในโปรแกรม
  } else {  // คำสั่ง/การตั้งค่าในโปรแกรม
    Serial.print("Modbus Error: ");  // สั่งงาน/ตั้งค่าโปรโตคอล Modbus RTU
    Serial.println(result);  // คำสั่ง/การตั้งค่าในโปรแกรม
  }  // ขอบเขตบล็อกคำสั่ง

  delay(1000);  // หน่วงเวลา (มิลลิวินาที)
}  // ขอบเขตบล็อกคำสั่ง

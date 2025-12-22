#include <Adafruit_GFX.h>       // Library หลักสำหรับวาดกราฟิก
#include <Adafruit_SSD1306.h>   // Library สำหรับจอ OLED SSD1306

// -------------------------------------------------------------
// กำหนดขนาดหน้าจอ
// -------------------------------------------------------------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// สร้าง object สำหรับจอ OLED
// &Wire = ใช้ I2C
// -1 = ไม่มี pin reset
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


void setup()
{
    Serial.begin(115200);

    // เริ่มต้นจอ OLED
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) // 0x3C = I2C address
    {
        Serial.println("OLED FAIL"); // ถ้าเริ่มจอไม่สำเร็จ
        while (1)
            ; // หยุดโปรแกรม
    }

    // ล้างหน้าจอ
    display.clearDisplay();

    // ตั้งค่าสีตัวอักษรเป็นขาว (OLED ขาว-ดำ)
    display.setTextColor(WHITE);

    // แสดงผลการตั้งค่า initial
    display.display();
}


void loop()
{
    // ล้างหน้าจอก่อนเขียนใหม่ทุกรอบ
    display.clearDisplay();

    // --- แสดงข้อความบรรทัดแรก ---
    display.setTextSize(3);   // ขนาดตัวอักษร
    display.setCursor(0, 0);  // กำหนดตำแหน่งเริ่มพิมพ์
    display.print("Hello!!"); // ข้อความ

    // --- แสดงข้อความบรรทัดที่สอง ---
    display.setTextSize(2);   // ขนาดเล็กลง
    display.setCursor(0, 35); // กำหนดตำแหน่ง
    display.print("SUMTECH");

    // ส่งข้อมูลทั้งหมดไปแสดงบนจอ
    display.display();
}

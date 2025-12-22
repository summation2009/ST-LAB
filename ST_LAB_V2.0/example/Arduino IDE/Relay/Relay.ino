// -------------------------------------------------------------
// กำหนดขาสำหรับ Relay
// -------------------------------------------------------------
#define RELAY1_PIN 25
#define RELAY2_PIN 26

// -------------------------------------------------------------
void setup()
{
    Serial.begin(115200); // เปิด Serial Monitor

    // ตั้งขา Relay เป็น OUTPUT
    pinMode(RELAY1_PIN, OUTPUT);
    pinMode(RELAY2_PIN, OUTPUT);
}

void loop()
{
    // --- เปิด Relay 1 ---
    Serial.println("Relay ON");
    digitalWrite(RELAY1_PIN, LOW); // บางโมดูล Relay ใช้ LOW = ON
    delay(1000);                   // รอ 1 วินาที

    // --- ปิด Relay 2 ---
    Serial.println("Relay OFF");
    digitalWrite(RELAY2_PIN, HIGH); // บางโมดูล Relay ใช้ HIGH = OFF
    delay(1000);                    // รอ 1 วินาที
}

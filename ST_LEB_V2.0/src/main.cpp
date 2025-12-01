#include <Arduino.h>

// -------------------------------------------------------------
// กำหนดขาสำหรับ LED
// LED_GREENx  = LED สีเขียว
// LED_YELLOWx = LED สีเหลือง
// LED_REDx    = LED สีแดง
// -------------------------------------------------------------
int LED_GREEN1 = 16;
int LED_GREEN2 = 17;
int LED_GREEN3 = 18;
int LED_YELLOW1 = 19;
int LED_YELLOW2 = 12;
int LED_YELLOW3 = 32;
int LED_RED1 = 25;
int LED_RED2 = 27;


void setup() {
    Serial.begin(115200);

    // ตั้งขาทุกตัวเป็น OUTPUT
    pinMode(LED_GREEN1, OUTPUT);
    pinMode(LED_GREEN2, OUTPUT);
    pinMode(LED_GREEN3, OUTPUT);
    pinMode(LED_YELLOW1, OUTPUT);
    pinMode(LED_YELLOW2, OUTPUT);
    pinMode(LED_YELLOW3, OUTPUT);
    pinMode(LED_RED1, OUTPUT);
    pinMode(LED_RED2, OUTPUT);
}

void loop()
{
    // ---------------------------------------------------------
    // ปิด LED ทุกตัว
    // ---------------------------------------------------------
    digitalWrite(LED_GREEN1, LOW);
    digitalWrite(LED_GREEN2, LOW);
    digitalWrite(LED_GREEN3, LOW);
    digitalWrite(LED_YELLOW1, LOW);
    digitalWrite(LED_YELLOW2, LOW);
    digitalWrite(LED_YELLOW3, LOW);
    digitalWrite(LED_RED1, LOW);
    digitalWrite(LED_RED2, LOW);
    delay(1000); // รอ 1 วินาที

    // ---------------------------------------------------------
    // เปิด LED ทุกตัว
    // ---------------------------------------------------------
    digitalWrite(LED_GREEN1, HIGH);
    digitalWrite(LED_GREEN2, HIGH);
    digitalWrite(LED_GREEN3, HIGH);
    digitalWrite(LED_YELLOW1, HIGH);
    digitalWrite(LED_YELLOW2, HIGH);
    digitalWrite(LED_YELLOW3, HIGH);
    digitalWrite(LED_RED1, HIGH);
    digitalWrite(LED_RED2, HIGH);
    delay(1000); // รอ 1 วินาที
}

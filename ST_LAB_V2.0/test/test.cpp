#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>
#include <ESP32Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include "LedControl.h"
#include "ModbusMaster.h"
#include <Stepper.h>

// #define ENABLE_DEBUG
// #define showOlED

//************************************************************************//
// setup sensot
// #define USE_DHT11
// #define USE_LCD
// #define USE_OLED
// #define USE_BUZZER
// #define USE_VR
// #define USE_SERVO
// #define USE_BCD_7_Segment
// #define USE_INFRARED
// #define USE_MAX7219
// #define USE_Step_DCMotor
// #define USE_Step_Motor
// #define USE_Modbus_RS485
// #define USE_Relay
// #define USE_LDR

//************************************************************************//
// RELAY
#ifdef USE_Relay
#define RELAY1_PIN 25
#define RELAY2_PIN 26
#endif

//************************************************************************//
// Step_Motor
#ifdef USE_Step_Motor
//การหมุน 1 รอบ เราจะใช้มอเตอร์ในโหมดเต็มขั้นตอน ซึ่งหมายความว่าต้องใช้ 2048 ขั้นตอนในการหมุน 360 องศา
const int stepsPerRevolution = 2048;

// Create stepper object called ‘myStepper’, note the pin order:
Stepper myStepper = Stepper(stepsPerRevolution, 16, 17, 18, 19);            
#endif

//************************************************************************//
// Modbus_RS485
#ifdef USE_Modbus_RS485
// instantiate ModbusMaster object
ModbusMaster myModbus;                   

#define SLAVE_ID 1                        
#define SLAVE_BAUDRATE 9600               
#endif

//************************************************************************//
// Step_DCMotor
#ifdef USE_Step_DCMotor
int enA = 13;
int in1 = 12;
int in2 = 14;

// This function lets you control spinning direction of motors
void directionControl()
{
  // Set motors to maximum speed
  digitalWrite(enA, HIGH);

  // Turn on motor A & B
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  ;
  delay(2000);

  // Now change motor directions
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  delay(2000);

  // Turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}

// This function lets you control speed of the motors
void speedControl()
{
  // Turn on motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  // Accelerate from zero to maximum speed
  for (int i = 0; i < 256; i++)
  {
    analogWrite(enA, i);
    delay(20);
  }

  // Decelerate from maximum speed to zero
  for (int i = 255; i >= 0; --i)
  {
    analogWrite(enA, i);
    delay(20);
  }

  // Now turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}
#endif

//************************************************************************//
// 7segmant 4 digi MAX7219
#ifdef USE_MAX7219
#define DIN_PIN 23
#define CLK_PIN 18
#define LOAD_PIN 5
LedControl lc = LedControl(DIN_PIN, CLK_PIN, LOAD_PIN, 1);

// --- WiFi config ---
const char *ssid = "sumtech 2.4G";
const char *password = "123456aaff";

// --- NTP ---
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 7 * 3600, 60000); // UTC+7

// --- เวลา fallback ---
unsigned long lastUpdate = 0;
int lastHour = 16;
int lastMinute = 55;

void showTime(int hour, int minute)
{
  int h1 = hour / 10;
  int h2 = hour % 10;
  int m1 = minute / 10;
  int m2 = minute % 10;

  // decimal = false เพื่อไม่ให้จุดขึ้น
  lc.setDigit(0, 0, h1, false); // หลักสิบชั่วโมง
  lc.setDigit(0, 1, h2, false); // หลักหน่วยชั่วโมง
  lc.setDigit(0, 2, m1, false); // หลักสิบ นาที
  lc.setDigit(0, 3, m2, false); // หลักหน่วย นาที
}
#endif

//************************************************************************//
// INFRARED SENSOR
#ifdef USE_INFRARED
#define INFRARED 16
int count = 0;
#endif

//************************************************************************//
// 7-segment ขา GPIO ซ้ำกับ LED 8 EA และ Switch 4 EA
#ifdef USE_BCD_7_Segment
// GPIO Pins for 7-segment of tens (หลักสิบ)
#define TENS_A 16 // ขาที่ซ้ำ LED_GREEN1
#define TENS_B 17 // ขาที่ซ้ำ LED_GREEN2
#define TENS_C 18 // ขาที่ซ้ำ LED_GREEN3
#define TENS_D 19 // ขาที่ซ้ำ LED_YELLOW1

// GPIO Pins for 7-segment of units (หลักหน่วย)
#define UNITS_A 12 // ขาที่ซ้ำ LED_YELLOW2, Switch1
#define UNITS_B 32 // ขาที่ซ้ำ LED_YELLOW3, Switch2
#define UNITS_C 25 // ขาที่ซ้ำ LED_RED1, Switch3
#define UNITS_D 27 // ขาที่ซ้ำ LED_RED2, Switch4

// ** ปุ่มเพิ่มเลข (ใช้ GPIO 33) **
#define BUTTON_INC_PIN 33
#endif

//************************************************************************//
// LCD
#ifdef USE_LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);
#endif

//************************************************************************//
// OLED
#ifdef USE_OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
#endif

//************************************************************************//
// DHT11
#ifdef USE_DHT11
#define DHTPIN 19
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
#endif

//************************************************************************//
// LDR
#ifdef USE_LDR
int LDR = 34;
int LDR_Value = 0;
#endif

//************************************************************************//
// VR
#ifdef USE_VR
int VR_PIN = 35;
#endif

//************************************************************************//
// VR
#ifdef USE_SERVO
int SERVO_PIN = 23;
Servo myservo;
#endif

//************************************************************************//
// BUZZER using LEDC (ESP32)
#ifdef USE_BUZZER
#define BUZZER 18
#define BUZZER_CH 0
#endif

//************************************************************************//
unsigned long previousMillisMatrix = 0;
int secMatrix = 0;

#define INTERVAL_MESSAGE1 5
#define INTERVAL_MESSAGE2 10

//************************************************************************//
// showDHT
#ifdef USE_DHT11
void showDHT()
{

  float t = dht.readTemperature();
  float h = dht.readHumidity();

  if (isnan(t) || isnan(h))
  {
    Serial.println("Failed to read DHT11!");
    return;
  }

#ifdef USE_showOLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Temperature:");

  display.setTextSize(2);
  display.setCursor(0, 10);
  display.print(t);
  display.print(" C");

  display.setTextSize(1);
  display.setCursor(0, 35);
  display.print("Humidity:");

  display.setTextSize(2);
  display.setCursor(0, 45);
  display.print(h);
  display.print(" %");

  display.display();
#endif

  Serial.println("====================DHT11====================");
  Serial.print("Temp: ");
  Serial.print(t);
  Serial.print(" C  Humi: ");
  Serial.print(h);
  Serial.println(" %RH");

}
#endif

//************************************************************************//
// showLDR
#ifdef USE_LDR
void showLDR()
{
  LDR_Value = analogRead(LDR);

#ifdef USE_showOLED
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 25);
  display.print("LDR:");
  display.print(LDR_Value);
  display.display();
#endif

  Serial.println("====================LDR====================");
  Serial.print("LDR : ");
  Serial.println(LDR_Value);

  if (LDR_Value > 4000)
  {
    ledcWriteTone(BUZZER_CH, 800);
  }
  else
  {
    ledcWriteTone(BUZZER_CH, 0);
  }
}
#endif

//************************************************************************//
// แปลงค่าของหลักสิบเป็น BCD และส่งไปยัง 7-segment ของหลักสิบและหลักหน่วย
#ifdef USE_BCD_7_Segment
void displayValue(int tens, int units)
{
  // 7-segment ของหลักสิบ
  digitalWrite(TENS_A, tens & 0x1);
  digitalWrite(TENS_B, (tens >> 1) & 0x1);
  digitalWrite(TENS_C, (tens >> 2) & 0x1);
  digitalWrite(TENS_D, (tens >> 3) & 0x1);

  // 7-segment ของหลักหน่วย
  digitalWrite(UNITS_A, units & 0x1);
  digitalWrite(UNITS_B, (units >> 1) & 0x1);
  digitalWrite(UNITS_C, (units >> 2) & 0x1);
  digitalWrite(UNITS_D, (units >> 3) & 0x1);
}
#endif

//************************************************************************//

void setup()
{
  Serial.begin(115200);

//************************************************************************//
// sep up Step_Motor
#ifdef USE_Step_Motor
// สามารถตั้งค่าความเร็วเป็น rpm ด้วยฟังก์ชัน ความเร็วสูงสุด สำหรับสเต็ปเปอร์มอเตอร์ 28byj-48 คือประมาณ10-15 รอบต่อนาทีที่ 5 V
myStepper.setSpeed(15);           
#endif

//************************************************************************//
// Setup Modbus_RS485
#ifdef USE_Modbus_RS485
  Serial2.begin(SLAVE_BAUDRATE, SERIAL_8N1, 16, 17);    
  myModbus.begin(SLAVE_ID, Serial2);               
#endif

//************************************************************************//
// setup Step_DCMotor
#ifdef USE_Step_DCMotor
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
#endif

//************************************************************************//
// MAX7219 setup
#ifdef USE_MAX7219
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);

  // WiFi connect
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");

  // NTP setup
  timeClient.begin();
  if (timeClient.update())
  {
    lastHour = timeClient.getHours();
    lastMinute = timeClient.getMinutes();
    lastUpdate = millis();
    Serial.println("Time obtained from NTP");
  }
  else
  {
    Serial.println("Failed to obtain time, fallback to default");
  }
#endif

//************************************************************************//
// setup dht11
#ifdef USE_DHT11
  dht.begin();
#endif

//************************************************************************//
// setup OLED
#ifdef USE_OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println("OLED FAIL");
    while (1)
      ;
  }

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.display();
#endif

//************************************************************************//
// setup SERVO
#ifdef USE_SERVO
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);
  myservo.attach(SERVO_PIN, 500, 2400);
#endif

//************************************************************************//
// setup LCD
#ifdef USE_LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("VR Servo Control");
#endif

//************************************************************************//
// pinmode
#ifdef USE_LDR
  pinMode(LDR, INPUT);
#endif

#ifdef USE_BCD_7_Segment
  pinMode(TENS_A, OUTPUT);
  pinMode(TENS_B, OUTPUT);
  pinMode(TENS_C, OUTPUT);
  pinMode(TENS_D, OUTPUT);

  pinMode(UNITS_A, OUTPUT);
  pinMode(UNITS_B, OUTPUT);
  pinMode(UNITS_C, OUTPUT);
  pinMode(UNITS_D, OUTPUT);

    // ปุ่มเพิ่มเลข
  pinMode(BUTTON_INC_PIN, INPUT_PULLUP);
#endif

#ifdef USE_INFRARED
  pinMode(INFRARED, INPUT);
#endif

  //************************************************************************//
  // RELAY
#ifdef USE_Relay
pinMode(RELAY1_PIN, OUTPUT);
pinMode(RELAY2_PIN, OUTPUT);
#endif

//************************************************************************//
// setup BUZZER LEDC
#ifdef USE_BUZZER
  ledcSetup(BUZZER_CH, 2000, 8);
  ledcAttachPin(BUZZER, BUZZER_CH);
#endif
}

void loop()
{

    //************************************************************************//
  //loop Reley 
#ifdef USE_Relay
  Serial.println("Relay ON");
  digitalWrite(RELAY1_PIN, HIGH); // เปิด Relay
  delay(1000);                   // รอ 5 วินาที

  Serial.println("Relay OFF");
  digitalWrite(RELAY2_PIN, LOW);  // ปิด Relay
  delay(1000);
#endif

//************************************************************************//
// loop Step_Motor
#ifdef USE_Step_Motor
myStepper.step(stepsPerRevolution);
delay(500);


myStepper.step(-stepsPerRevolution);
delay(500);           
#endif


//************************************************************************//
// loop Modbus_RS485
#ifdef USE_Modbus_RS485
  uint8_t result;
  float Temperature, Humidity;

  result = myModbus.readHoldingRegisters(0, 15);   // เริ่มอ่านค่าที่ตำแหน่งรีจิสเตอร์ 0, เป็นจำนวน 2 รีจิสเตอร์

  if (result == myModbus.ku8MBSuccess) {          // หากสำเร็จ เซนเซอร์ตอบกลับ และไม่มีผิดพลาด
    Humidity = myModbus.getResponseBuffer(0);     // เอาค่า Buffer 0 ที่อ่านจาก Modbus มาไว้ในตัวแปร Humidity และหารด้วย 10
    Temperature = myModbus.getResponseBuffer(1);  // เอาค่า Buffer 1 ที่อ่านจาก Modbus มาไว้ในตัวแปร Temperature และหารด้วย 10

    Serial.print (Humidity);                 // นำค่าที่อ่านได้ พิมพ์ออกทาง Serial0
    Serial.print (" %RH");
    Serial.print ("\t");
    Serial.print (Temperature);              // นำค่าที่อ่านได้ พิมพ์ออกทาง Serial0
    Serial.println (" *C");
  } else {
    Serial.println ("error");
  }
  
  delay(1000);             
#endif

//************************************************************************//
// Step_DCMotor
#ifdef USE_Step_DCMotor
  directionControl();
  delay(1000);
  speedControl();
  delay(1000);
#endif


//************************************************************************//
// MAX7219
#ifdef USE_MAX7219
  // อัปเดต NTP ทุก 60 วินาที
  if (millis() - lastUpdate >= 60000)
  {
    if (timeClient.update())
    {
      lastHour = timeClient.getHours();
      lastMinute = timeClient.getMinutes();
      Serial.println("NTP time updated");
    }
    lastUpdate = millis();
  }

  // เพิ่ม fallback minute ทุก 1 นาที
  static unsigned long lastTick = 0;
  if (millis() - lastTick >= 60000)
  {
    lastMinute++;
    if (lastMinute >= 60)
    {
      lastMinute = 0;
      lastHour++;
      if (lastHour >= 24)
        lastHour = 0;
    }
    lastTick = millis();
  }

  // แสดงเวลาแบบ HHMM นิ่ง ๆ
  showTime(lastHour, lastMinute);
  delay(1000);
#endif

//************************************************************************//
// INFRARED SENSOR
#ifdef USE_INFRARED
  int irVal = digitalRead(INFRARED); // อ่านค่า IR sensor
  static int lastIR = HIGH;          // เก็บสถานะ IR ก่อนหน้า

  // เพิ่ม count เฉพาะเมื่อ IR เปลี่ยนจาก LOW → HIGH
  if (irVal == HIGH && lastIR == LOW)
  {
    count++;
    Serial.print("Count = ");
    Serial.println(count);
  }

  lastIR = irVal; // อัปเดตสถานะก่อนหน้า
  delay(50);
#endif

  //************************************************************************//
  // Count Numbers 7-segment
#ifdef USE_BCD_7_Segment
    static int currentNumber = 0;            // 0 - 99
    static int lastButtonState = HIGH;       // ปุ่มใช้ INPUT_PULLUP -> idle HIGH
    static unsigned long lastDebounceTime = 0;
    const unsigned long debounceDelay = 50;  // ms

    int reading = digitalRead(BUTTON_INC_PIN);

    // ถ้าสถานะเปลี่ยน รีเซ็ต debounce timer
    if (reading != lastButtonState) {
      lastDebounceTime = millis();
    }

    // ถ้าเกินเวลา debounce แล้ว ให้ยอมรับสถานะ
    if ((millis() - lastDebounceTime) > debounceDelay) {
      // edge detect: เมื่อปุ่มเปลี่ยนจาก HIGH -> LOW (กดปุ่มครั้งเดียว)
      static int stableLastState = HIGH; // เก็บสถานะที่ผ่าน debounce แล้ว
      if (reading != stableLastState) {
        stableLastState = reading;
        if (stableLastState == LOW) {
          // ปุ่มถูกกด
          currentNumber++;
          if (currentNumber > 99) currentNumber = 0;
          Serial.print("Number = ");
          Serial.println(currentNumber);
        }
      }
    }

    lastButtonState = reading;

    int tens = currentNumber / 10;
    int units = currentNumber % 10;
    displayValue(tens, units);

    delay(50); // short delay เพื่อไม่ให้ loop วิ่งเร็วเกินไป
#endif

#ifdef USE_VR
  int vr = analogRead(VR_PIN); // 0 - 4095

#ifdef USE_SERVO
  int angle = map(vr, 0, 4095, 90, 0);
  myservo.write(angle);
#endif

#ifdef USE_LCD
  lcd.setCursor(0, 1);
  lcd.print("VR:");
  lcd.print(vr);
  lcd.print("   ");
#endif

  Serial.print("VR=");
  Serial.print(vr);

  delay(50);
#endif

#ifdef USE_OLED
  unsigned long now = millis();

  if (now - previousMillisMatrix >= 1000)
  {
    secMatrix++;
    Serial.println(secMatrix);

    if (secMatrix <= INTERVAL_MESSAGE1)
    {
      showDHT();
    }
    else if (secMatrix <= INTERVAL_MESSAGE2)
    {
      showLDR();
    }
    else
    {
      secMatrix = 0;
    }

    previousMillisMatrix = now;
  }
#endif
}

// https://www.hackster.io/yettiz/easy-voltmeter-with-esp8266-mini-d1-pro-with-oled-display-1a91dc
// Вывод на OLED экран измеренного напряжения на аккумуляторе

#include <ESP8266WiFi.h>
#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>        // https://github.com/olikraus/u8g2
#include <SoftwareSerial.h>

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

int analogInput = A0;

float vout = 0.0;
float vin = 0.0;
float R4 = 62000;   // Resistor 62k 
float R3 = 220000;  // Resistor 220k
int value = 0;
String $vin = "0";

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_OFF);
  WiFi.forceSleepBegin();
  delay(1);
  pinMode(analogInput, INPUT);
  u8g2.begin();                   // init Display 
}

void loop(void) {
 value = analogRead(analogInput);
 vout = (value * 3.40) / 1024.0;  // mybe u must change the 3.3 to 5 and 3.485
                                   // *** work not correct with ESP32 ***
                                   //for the ESP32 u have to change the 1023 to 4095
                                   // ***********************************
 vin = vout / (R3/(R4+R3));
 $vin = String(vin);
 Serial.print("Voltage = ");
 Serial.print(vin,3);
 Serial.println("V");

 showonoled();

}

//=========== Funktion init Display ========
void u8g2_prepare(void) {
  //u8g2.setFont(u8g2_font_6x10_tf);
  //u8g2.setFont(u8g2_font_fur20_tr);
  u8g2.setFont(u8g2_font_bubble_tr);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
}

//=========== Funktion show on Display =====
void showonoled() {
  u8g2.clearBuffer();
  u8g2_prepare();
  
  u8g2.drawStr(0, 0, "Voltage");
  u8g2.drawStr(13, 45, $vin.c_str());
  u8g2.drawStr(93, 45, "V");

  u8g2.sendBuffer();  
  delay(200);
}

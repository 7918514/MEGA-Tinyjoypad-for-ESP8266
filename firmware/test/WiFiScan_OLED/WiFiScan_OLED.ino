#include <U8g2lib.h>  // Библиотека для OLED https://github.com/olikraus/u8g2
#include <ESP8266WiFi.h>

// Инициализация OLED (SH1106, I2C, 128x64)
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// Переменные
unsigned long lastScanTime = 0;
const unsigned long scanInterval = 10000; // 10 секунд
int currentNetworkIndex = 0;
int totalNetworks = 0;

void setup() {
  Serial.begin(115200);

  // Инициализация OLED
  u8g2.begin();
  u8g2.setFont(u8g2_font_6x10_mr); // Компактный шрифт

  // Режим сканирования Wi‑Fi (не подключаемся ни к чему)
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.println("");
  Serial.println("Wi‑Fi scanner started. Scanning every 10 seconds...");
  displayStartupScreen();
}

void loop() {
  // Сканируем сети каждые 10 секунд
  if (millis() - lastScanTime > scanInterval) {
    lastScanTime = millis();
    scanNetworks();
  }

  // Переключаем сети каждые 3 секунды стабильно
  static unsigned long lastNetworkSwitch = 0;
  if (totalNetworks > 0 && millis() - lastNetworkSwitch >= 2000) {
    lastNetworkSwitch = millis();
    currentNetworkIndex = (currentNetworkIndex + 1) % totalNetworks;
  }

  // Всегда отображаем текущую сеть
  if (totalNetworks > 0) {
    displayNetwork(currentNetworkIndex);
  } else {
    displayNoNetworks();
  }
}

// Функция сканирования Wi‑Fi сетей
void scanNetworks() {
  Serial.println("Starting Wi‑Fi scan...");

  // Запускаем сканирование
  int n = WiFi.scanNetworks();
  totalNetworks = n;
  currentNetworkIndex = 0;

  if (n == 0) {
    Serial.println("No networks found");
  } else {
    Serial.print("Networks found: ");
    Serial.println(n);

    for (int i = 0; i < n; ++i) {
      String ssid = WiFi.SSID(i);
      int32_t rssi = WiFi.RSSI(i);
      uint8_t encryptionType = WiFi.encryptionType(i);
      uint8_t bssid[6];
      memcpy(bssid, WiFi.BSSID(i), 6);
      int32_t channel = WiFi.channel(i);
      bool hidden = WiFi.isHidden(i);

      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(ssid);
      Serial.print(" (");
      Serial.print(rssi);
      Serial.print("dBm)");
      Serial.print(" Ch: ");
      Serial.print(channel);
      Serial.print(" MAC: ");

      // Выводим MAC‑адрес
      for (int j = 0; j < 6; ++j) {
        if (j != 0) Serial.print(":");
        Serial.printf("%02X", bssid[j]);
      }

      Serial.print(" ");
      // Определяем тип шифрования
  switch (encryptionType) {
  case 7: // ENC_TYPE_NONE — открытая сеть
    Serial.print("Open");
    break;
  case 5: // ENC_TYPE_WEP
    Serial.print("WEP");
    break;
  case 2: // ENC_TYPE_TKIP — WPA/PSK
    Serial.print("WPA");
    break;
  case 4: // ENC_TYPE_CCMP — WPA2/PSK
    Serial.print("WPA2");
    break;
  case 8: // ENC_TYPE_AUTO — WPA/WPA2/PSK
    Serial.print("WPA/WPA2");
    break;
  default:
    Serial.print("Encrypted");
    break;
}

      if (hidden) {
        Serial.print(" (hidden)");
      }
      Serial.println();
    }
  }
  Serial.println("--- Scan complete ---");
}

// Преобразование MAC‑адреса в строку
String macToString(const uint8_t* mac) {
  String result;
  for (int i = 0; i < 6; ++i) {
    if (i != 0) result += ":";
    char buffer[3];
    sprintf(buffer, "%02X", mac[i]);
    result += buffer;
  }
  return result;
}

// Отображение конкретной сети на OLED
void displayNetwork(int index) {
  u8g2.clearBuffer();


  // Информация о сети
  if (totalNetworks > 0 && index < totalNetworks) {
    String ssid = WiFi.SSID(index);
    int32_t rssi = WiFi.RSSI(index);
    uint8_t encryptionType = WiFi.encryptionType(index);
    uint8_t bssid[6];
    memcpy(bssid, WiFi.BSSID(index), 6);
    int32_t channel = WiFi.channel(index);
    bool hidden = WiFi.isHidden(index);

    u8g2.setCursor(0, 10);
    u8g2.print("#");
    u8g2.print(index + 1);
    u8g2.print("/");
    u8g2.print(totalNetworks);

    u8g2.setCursor(0, 20);
    u8g2.print("SSID: ");
    // Обрезаем слишком длинные названия (16 символов для этого шрифта)
    if (ssid.length() > 16) {
      ssid = ssid.substring(0, 16) + "*";
    }
    u8g2.print(ssid);

    u8g2.setCursor(0, 30);
    u8g2.print("RSSI: ");
    u8g2.print(rssi);
    u8g2.print("dBm");

    // Вывод номера канала
    u8g2.setCursor(0, 40);
    u8g2.print("Channel: ");
    u8g2.print(channel);

    // Вывод типа шифрования
    u8g2.setCursor(0, 50);
    u8g2.print("Encrypt: ");

    switch (encryptionType) {
      case 7:
        u8g2.print("Open");
        break;
      case 5:
        u8g2.print("WEP");
        break;
      case 2:
        u8g2.print("WPA");
        break;
      case 4:
        u8g2.print("WPA2");
        break;
      case 8:
        u8g2.print("WPA/WPA2");
        break;
      default:
        u8g2.print("Encryption");
        break;
}

    // Вывод статуса скрытой сети
    if (hidden) {
      u8g2.setCursor(90, 50); // Позиция справа
      u8g2.print("HID");
    }
    
    // Отображение MAC‑адреса
    String macStr = macToString(bssid);
    u8g2.setCursor(0, 60);
    u8g2.print("MAC:");
    // Обрезаем MAC‑адрес, если не помещается (17 символов: XX:XX:XX:XX:XX:XX)
    if (macStr.length() > 17) {
      macStr = macStr.substring(0, 17);
    }
    u8g2.print(macStr);
    
  }

  u8g2.sendBuffer();
}

// Экран при отсутствии сетей
void displayNoNetworks() {
  u8g2.clearBuffer();
  u8g2.setCursor(0, 32);
  u8g2.print("No networks found");
  u8g2.sendBuffer();
}

// Начальный экран
void displayStartupScreen() {
  u8g2.clearBuffer();
  u8g2.setCursor(0, 28);
  u8g2.print("WiFi Scanner");
  u8g2.setCursor(0, 40);
  u8g2.print("ESP8266 + OLED");
  u8g2.sendBuffer();
}

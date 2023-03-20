#include <WiFi.h>
#include <time.h>
#include <M5StickCPlus.h>

//Set initial brightness (Values 7-15)
int brightness = 7;

const unsigned char thunder_bits[] PROGMEM = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xff, 0x7f, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0xfc, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc,
   0xff, 0xff, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xff, 0xff, 0x03,
   0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00,
   0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xff,
   0xff, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xff, 0xff, 0x7f, 0x00,
   0x00, 0x00, 0x00, 0x00, 0xe0, 0xff, 0xff, 0x3f, 0x00, 0x00, 0x00, 0x00,
   0x00, 0xe0, 0xff, 0xff, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xff,
   0xff, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xff, 0xff, 0x0f, 0x00,
   0x00, 0x00, 0x00, 0x00, 0xf8, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00, 0x00,
   0x00, 0xfc, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xff,
   0xff, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x01, 0x00,
   0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00,
   0x80, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xff, 0xff,
   0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xff, 0xff, 0x7f, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xe0, 0xff, 0xff, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00,
   0xf0, 0xff, 0xff, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xff, 0xff,
   0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xff, 0xff, 0x0f, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xfc, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00,
   0xfe, 0xff, 0xff, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xff, 0xff,
   0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00,
   0x00, 0x00, 0x80, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
   0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xff, 0xff, 0x7f,
   0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xff, 0xff, 0x3f, 0x00, 0x00, 0x00,
   0x00, 0x00, 0xe0, 0xff, 0xff, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0,
   0xff, 0xff, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xff, 0xff, 0xff,
   0xff, 0xff, 0x7f, 0x00, 0x00, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f,
   0x00, 0x00, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x00, 0x00, 0xfe,
   0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0x03, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01,
   0x00, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xc0, 0xff,
   0xff, 0xff, 0xff, 0xff, 0x7f, 0x00, 0x00, 0xc0, 0xff, 0xff, 0xff, 0xff,
   0xff, 0x3f, 0x00, 0x00, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x00,
   0x00, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x00, 0x00, 0xf8, 0xff,
   0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0x00, 0xf8, 0xff, 0xff, 0xff, 0xff,
   0xff, 0x01, 0x00, 0x00, 0x00, 0x0c, 0x30, 0xff, 0xff, 0xff, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0xff, 0xff, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0xff,
   0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xff, 0xff, 0x0f, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xc0, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00,
   0xe0, 0xff, 0xff, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xff, 0xff,
   0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xff, 0xff, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xf8, 0xff, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0xf8, 0xff, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0xff, 0x0f,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0xff, 0x07, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xfe, 0xff, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0x7f, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x80, 0xff, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0,
   0xff, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xff, 0x0f, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xff, 0x07, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0xf0, 0xff, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8,
   0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xff, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0xfc, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe,
   0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x07, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x80, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xff,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x7f, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0xe0, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0xe0, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x07,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x03, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0xf8, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x07, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x03, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xc0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

//Edit with your WiFi information
const char* ssid = "M5";
const char* password = "1234567890";

void Battery() {
  // Display the battery charge when the M5 button is pressed
  Serial.println("M5 Button pressed");
  M5.Beep.tone(4000);
  delay(100);
  M5.Beep.mute();
  float batteryVoltage = M5.Axp.GetBatVoltage();
  //int batteryPercentage = map(batteryVoltage, 3.0, 4.2, 0, 100);  //Display as a percentage.
  Serial.print("Battery voltage: ");
  Serial.println(batteryVoltage);
  M5.Lcd.fillScreen(TFT_BLACK);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(10, 0);
  M5.Lcd.print("Voltage: ");
  M5.Lcd.print(batteryVoltage);
  M5.Lcd.print("V");
  M5.Lcd.drawXBitmap(50, 30, thunder_bits, 72, 100, TFT_WHITE);
  M5.update(); // Update the screen
  delay(2000);
  M5.Lcd.fillScreen(TFT_BLACK);
}

void Dimmer() {
  // Dims the display
  Serial.println("B Button pressed");
  M5.Beep.tone(4000);
  delay(100);
  M5.Beep.mute();
  brightness += 2;
  if (brightness > 14) brightness = 7;
  M5.Axp.ScreenBreath(brightness);
}

void setup() {
  Serial.begin(115200);
  M5.begin();
  pinMode(10, OUTPUT);
  delay(500);
  digitalWrite (10, HIGH); // turn off the LED
  M5.Lcd.setRotation(3); // Flip the screen 180 degrees
  M5.Lcd.fillScreen(TFT_BLACK);
  M5.Axp.ScreenBreath(brightness);


  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    M5.Lcd.fillScreen(TFT_BLACK);
    M5.Lcd.setTextSize(1);
    M5.Lcd.setCursor(10, 20);
    M5.Lcd.println("Connecting to WiFi...");
    Serial.println("Connecting to WiFi...");
  }

  M5.Lcd.print("WiFi connected");
  Serial.println("WiFi connected");
  
  // Sync time with NTP server
  configTime(-6 * 3600, 0, "pool.ntp.org"); // Set the GMT offset to -6
  M5.Lcd.print("Time synced with NTP server");
  Serial.println("Time synced with NTP server");
  
  // Wait for time to be set
  while (time(nullptr) < 1631952000) {
    delay(1000);
    M5.Lcd.print("Waiting for time to be set...");
    Serial.println("Waiting for time to be set...");
  }
  
  // Clear the screen
  M5.Lcd.fillScreen(TFT_BLACK);
}

void loop() {
  M5.Lcd.setCursor(10, 0);
  M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
  M5.Lcd.setTextSize(2);
  M5.Lcd.print("*** CARPE DIEM ***");

  M5.Lcd.setCursor(10, 53);
  M5.Lcd.setTextSize(4);
  
  // Get the current time and date
  time_t now = time(nullptr);
  struct tm timeinfo;
  localtime_r(&now, &timeinfo);
  
  // Format and display the time
  char timeStr[10];
  sprintf(timeStr, "%02d:%02d:%02d", timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
  M5.Lcd.print(timeStr);
  
  // Format and display the date and day of the week
  char dateStr[11];
  strftime(dateStr, sizeof(dateStr), "%d/%m/%Y", &timeinfo);
  M5.Lcd.setCursor(10, 120);
  M5.Lcd.setTextSize(2);
  M5.Lcd.print(dateStr);
  
  char dayStr[4];
  strftime(dayStr, sizeof(dayStr), "%a", &timeinfo);
  M5.Lcd.setCursor(190, 120);
  M5.Lcd.setTextSize(2);
  M5.Lcd.print(dayStr);

  // Beep twice every hour
  if (timeinfo.tm_min == 0 && timeinfo.tm_sec == 0) {
    if (timeinfo.tm_hour == 0 || timeinfo.tm_hour == 12) {
      // For midnight and noon, beep 3 times
      for (int i = 0; i < 3; i++) {
        M5.Beep.tone(4000, 100);
        delay(100);
        M5.Beep.mute();
        digitalWrite(10, LOW);
        delay(500);
        digitalWrite(10, HIGH);//Turn off the LED. ESP pins work backwards?
        delay(500);
      }
    } else {
      // For other hours, beep twice
      for (int i = 0; i < 2; i++) {
        M5.Beep.tone(4000, 100);
        delay(100);
        M5.Beep.mute();
        digitalWrite(10, LOW);
        delay(500);
        digitalWrite(10, HIGH);
        delay(500);
      }
    }
  }

  // Beep every quarter hour and turn on the LED
  else if (timeinfo.tm_min % 15 == 0 && timeinfo.tm_sec == 0) {
    M5.Beep.tone(4000, 100);
    delay(100);
    M5.Beep.mute();
    digitalWrite(10, LOW);
    delay(500);
    digitalWrite(10, HIGH);
    delay(500);
  }
  else {
    digitalWrite(10, HIGH);
    delay(500);
  }

    // Alarm at 9:40 am
    if (timeinfo.tm_hour == 9 && timeinfo.tm_min == 40 && timeinfo.tm_sec == 0) {
    for (int i = 0; i < 9; i++)
    M5.Beep.tone(4000, 100);
    delay(100);
    M5.Beep.mute();
    digitalWrite(10, LOW);
    delay(333);
    digitalWrite(10, HIGH);
    delay(333);
  }

  if (M5.BtnA.wasPressed()) Battery();
  if (M5.BtnB.wasPressed()) Dimmer();
  M5.update();

  delay(333); // Update the display and check the time every third of a second
}
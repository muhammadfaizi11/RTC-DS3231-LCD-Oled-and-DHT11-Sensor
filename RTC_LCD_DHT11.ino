#include "RTClib.h"
#include "Wire.h"
#include "LiquidCrystal_I2C.h"
#include "DHT.h"
#define DHTPIN 13
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Set the LCD address to 0x23 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x23, 20, 4);

RTC_DS3231 rtc;

char hari[7][20] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};

int tanggal;
int bulan;
int tahun;
int jam;
int menit;
int detik;

String dow; //day of week
String MyDate;
String MyTime;

void setup() {
  Serial.begin(57600);

#ifndef ESP32
  while (!Serial);
#endif

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }
if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //Set time from computer
  }

  //Initialize LCD
  lcd.begin();

  // Turn on the blacklight and print a message.
  lcd.backlight(); 
}

void loop() {
  DateTime now = rtc.now();

  lcd.clear();
  tanggal = now.day();
  bulan = now.month();
  tahun = now.year();
  jam = now.hour();
  menit = now.minute();
  detik = now.second();

  dow = hari[now.dayOfTheWeek()];

  //Get the now day value
  Serial.print("Since midnight 1/1/1970 = ");
  Serial.print(now.unixtime());
  Serial.print("s = ");
  Serial.print(now.unixtime()/86400L);
  Serial.println("d");

  MyDate = MyDate + dow + ", " + tanggal + "/" + bulan + "/" + tahun;
  MyTime = MyTime + jam + ":" + menit + ":" + detik;

  //Send to serial monitor
  Serial.println(dow);
  Serial.println(MyDate);
  Serial.println(MyTime);

  //Print on LCD
  lcd.setCursor(2,0);
  lcd.print(MyDate);
  lcd.setCursor(5,1);
  lcd.print(MyTime);
  MyDate= " ";
  MyTime = " ";
  lcd.setCursor(4,2);
  lcd.print("Suhu : ");
  lcd.print(rtc.getTemperature());
  delay(1000);

//  //Sensor DHT11 membaca suhu dan kelembaban
//  float suhu = dht.readTemperature();
//  float lembab = dht.readHumidity();
//
//  //Memeriksa apakah sensor berhasil membaca suhu dan kelembaban
//  if (isnan(suhu) || isnan(lembab)) {
//    Serial.println("Gagal membaca Sensor DHT11");
//    return;
//  }
//
//  //Show DHT11 Sensor to Serial Monitor
//  Serial.print("Suhu : ");
//  Serial.print(suhu);
//  Serial.print("Kelembaban : ");
//  Serial.print(lembab);
//  Serial.println();
//  delay(1000);
//
//  //Send DHT11 to LCD
//  lcd.setCursor(6,3);
//  lcd.print("Suhu : ");
//  lcd.println(suhu);
//  lcd.setCursor(3,4);
//  lcd.print("Kelembaban : ");
//  lcd.println(lembab);
//  delay(1000);
   
}

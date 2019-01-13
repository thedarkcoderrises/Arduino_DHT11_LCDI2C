

#include <DHT.h>
#include <Wire.h>  
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // SET I2C Address

#define DHTPIN 8 // Defines pin number to which the sensor is connected

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);

int incomingByte = 0; 

void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);  // Initialinze LCD.
  lcd.backlight(); // makes Backligh ON. 
}
void loop() {
  // Wait a few seconds between measurements.
  delay(2000); // Delays 2 secods, as the DHT22 sampling rate is 0.5Hz
// Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
 lcd.setCursor(0,0); // Sets the location at which subsequent text written to the LCD will be displayed
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  //float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  //float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);

  lcd.clear();     // Clears LCD
  lcd.home();      // Sets cursor at Column 0 and Line 0
  lcd.print("Current Temp:");
  lcd.setCursor(0,1);
  lcd.print("H:");
  lcd.print(round(h));
  lcd.print("%");
  lcd.print(" T:");
  lcd.print(t);
  lcd.print((char)223);
  lcd.print("C");


 for (int positionCounter = 0; positionCounter < 40; positionCounter++) {
    // scroll one position left:
    lcd.scrollDisplayLeft();
    // wait a bit:
    delay(500);
  }
  
//  Serial.print(F("°F  Heat index: "));
//  Serial.print(hic);
//  Serial.print(F("°C "));
//  Serial.print(hif);
//  Serial.println(F("°F"));

}

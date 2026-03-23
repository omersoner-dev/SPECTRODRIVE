
  // put your setup code here, to run once:
#include <LiquidCrystal.h>

// LCD pinleri: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(29, 28, 27, 26, 25, 24);

// LDR modülleri (dijital çıkış)
const int ldrSol = 22;
const int ldrSag = 23;
const int tiltPin = 30;
const int buzzerPin = 32;

// Motor pinleri (L298N)
const int in1 = 2;
const int in2 = 3;
const int in3 = 4;
const int in4 = 5;
const int enA = 6;
const int enB = 7;

// LED
int LEDdizisi[]={8,9,10,11};

const int trigPin = 12;
const int echoPin = 13;

// Ayarlar
const int hiz = 100;
bool cakarModu = false;
bool takipModu = false;
unsigned long zaman = 0;
bool alarmAktif = false;  // TILT alarmı aktif mi?
String gelenVeri = "";
bool ledDurum = LOW;

void stopMotors() {
  digitalWrite(in1, LOW); digitalWrite(in2, LOW);
  digitalWrite(in3, LOW); digitalWrite(in4, LOW);
  analogWrite(enA, 0); analogWrite(enB, 0);
}

bool engelVarMi() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  

  long sure = pulseIn(echoPin, HIGH);
  int mesafe = sure / 58.2;
  Serial.println(mesafe); 
  return (mesafe > 0 && mesafe < 3.3); // 15 cm'den yakınsa engel var
}

void isikTakip() {
  int sol = digitalRead(ldrSol);
  int sag = digitalRead(ldrSag);

  if (sol == LOW && sag == LOW) {
    ileri();
  } else if (sol == LOW && sag == HIGH) {
    solaDon();
  } else if (sol == HIGH && sag == LOW) {
    sagaDon();
  } else {
    stopMotors();
  }
}

// Fonksiyonlar

void ileri() {
  digitalWrite(in1, HIGH); digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH); digitalWrite(in4, LOW);
  analogWrite(enA, hiz); analogWrite(enB, hiz);
}

void solaDon() {
  digitalWrite(in1, LOW); digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH); digitalWrite(in4, LOW);
  analogWrite(enA, hiz); analogWrite(enB, hiz);
}

void sagaDon() {
  digitalWrite(in1, HIGH); digitalWrite(in2, LOW);
  digitalWrite(in3, LOW); digitalWrite(in4, HIGH);
  analogWrite(enA, hiz); analogWrite(enB, hiz);
}
void geri() {
  digitalWrite(in1, LOW); digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW); digitalWrite(in4, HIGH);
  analogWrite(enA, hiz); analogWrite(enB, hiz);
}


void setup() {
  Serial1.begin(9600); // HC-05 için
 Serial.begin(9600);

  pinMode(ldrSol, INPUT);
  pinMode(ldrSag, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(tiltPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

   for(int i=0;i<4;i++)
  {
  pinMode(LEDdizisi[i],OUTPUT);
  }

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  
  lcd.begin(16, 2);
  lcd.print("  SPECTRODRIVE");
  lcd.setCursor(0,1);
  lcd.print("   WELCOME :)    ");
  delay(3000);
    
  lcd.clear();
  lcd.begin(16, 2);
  lcd.print("     Ready...");
  lcd.setCursor(0,1);
  lcd.print("  SPECTRODRIVE");


  stopMotors();
}

void loop() {
  static unsigned long sonTiltZamani = 0;
  const unsigned long tiltMinInterval = 1000; // 1 saniye
  
  // Tilt kontrolü (debounce'lu)
  if (digitalRead(tiltPin) == LOW && (millis() - sonTiltZamani > tiltMinInterval)) {
    sonTiltZamani = millis();
    alarmAktif = true;
    
    // 3 kez veri gönderim garantisi
    for (int i = 0; i < 3; i++) {
      Serial1.println("TILT"); // Uygulamaya gönder
      Serial.println("DEBUG: TILT_ALARM gönderildi"); // Seri monitör kontrol
      delay(50);
    }
  }

  // Bluetooth veri okuma
  while (Serial1.available()) {
    char ch = Serial1.read();
    if (ch == '\n' || ch == '\r') {
      gelenVeri.trim();
      Serial.print("Gelen veri: ");
      Serial.println(gelenVeri);

      if (gelenVeri == "6161" && alarmAktif) {
        alarmAktif = false;
        lcd.clear();
        lcd.print("System Normal");
        Serial1.println("UNLOCK");
      } 
      else if (!alarmAktif) {
        if (gelenVeri == "A" || gelenVeri == "a") {
          cakarModu = !cakarModu;
          lcd.clear();
          lcd.print("Party Mode");
          lcd.setCursor(0, 1);
          lcd.print(cakarModu ? "ON" : "OFF");
        } 
        else if (gelenVeri == "B" || gelenVeri == "b") {
          takipModu = !takipModu;
          lcd.clear();
          lcd.print("Follow Mode");
          lcd.setCursor(0, 1);
          lcd.print(takipModu ? "ON" : "OFF");
          if(!takipModu)
          {
            stopMotors();    
          }
        }
        
      }
      gelenVeri = "";
    } 
    else {
      gelenVeri += ch;
    }
  }



  // Alarm aktifse her şeyi kilitle
  if (alarmAktif) {
    stopMotors();
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(LEDdizisi[0], HIGH);
    lcd.setCursor(0, 0);
    lcd.print("   WARNING!!!   ");
    lcd.setCursor(0, 1);
    lcd.print("Enter code...");
    return;
  } else {
    digitalWrite(buzzerPin, LOW);
  }

  // Çakar LED
  if (cakarModu) {
    for(int i=0;i<4;i++)
{
  digitalWrite(LEDdizisi[i],HIGH);
  delay(100);
  digitalWrite(LEDdizisi[i],LOW);
 }
  for(int a=3;a>-1;a--)
  {
  digitalWrite(LEDdizisi[a],HIGH);
  delay(100);
  digitalWrite(LEDdizisi[a],LOW);
  }
  }
   else 
  {
    digitalWrite(LEDdizisi[0], LOW);
    digitalWrite(LEDdizisi[1], LOW);
    digitalWrite(LEDdizisi[2], LOW);
    digitalWrite(LEDdizisi[3], LOW);
  }

  // Takip modu
  if (takipModu) {
    int sol = digitalRead(ldrSol);
    int sag = digitalRead(ldrSag);

    // LOW = ışık var
  if (takipModu) {
    if (engelVarMi()) {
      stopMotors();
      lcd.setCursor(0, 1);
      lcd.print("Object Detected");
      geri();      // Kısa süre geri
      digitalWrite(LEDdizisi[0],HIGH);    
      delay(650);  // 400 ms geri gitmesi yeterli
      unsigned long baslangic = millis();
      while (millis() - baslangic < 650) {
        digitalWrite(buzzerPin, HIGH);
        delay(100);
        digitalWrite(buzzerPin, LOW);
         delay(100); // toplam 200 ms aralıkla ötüyor
}
      stopMotors();    // Sonra dur
      
     //sagaDon(); // engel varsa saga kaç
      //delay(600);
    } else {
      isikTakip();
      lcd.setCursor(0, 1);
      lcd.print("FORWARD          ");
    }
  } else {
    stopMotors();
  }

  delay(50);
}
}


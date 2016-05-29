#include <TimerOne.h>

#include <LiquidCrystal.h>
#include <EEPROM.h>
#include "FaEEPROM.h"
#include "FaButton.h"
#include "FaDegerSakla.h"
#include "FaZamanlayici.h";
#include <Bounce2.h>


const int analogInPinSW = A3;  //
const int analogInPinY = A4;  // Analog input pin that the potentiometer is attached to
const int analogInPinX = A5;  // Analog input pin that the potentiometer is attached to
int sensorValueYDef = 0;        // value read from the pot
int sensorValueXDef = 0;

bool AyarModu = false;
int  AyarHanesi = 0;

float Satir1,Satir2,Satir3 =0;


int AktifSatir = 0;


byte FormButton = 0;
byte IsikSiddeti = 200;

volatile unsigned int StepHizi = 0;
int StepHizi_Sakla = 0;


volatile unsigned int stepPortu = 7;
volatile long DakikadakiStepSayisi = 0;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
FaDegerSakla sakla_1;

FaZamanlayici ZamanlayiciStepMotor;
FaZamanlayici ZamanlayiciForm;
FaZamanlayici ZamanlayiciButton;

FaButton FaButton1;

Bounce debouncer = Bounce();


void setup() {

  sensorValueYDef = analogRead(analogInPinY);
  sensorValueXDef = analogRead(analogInPinX);

  pinMode(stepPortu, OUTPUT);
  pinMode(13, OUTPUT);

  pinMode(analogInPinSW, INPUT_PULLUP);
  debouncer.attach(analogInPinSW);
  debouncer.interval(100); // interval in ms


  Serial.begin(9600);

  lcd.clear();
  lcd.begin(20, 4);
  lcd.print("www.artekya.com");

  delay(1000);

  FaEEPROM.RestartSay();

  StepHizi =  FaEEPROM.GetStepHizi();

  if (StepHizi < 0) {
    StepHizi = 10;
  }

  if (StepHizi > 500) {
    StepHizi = 10;
  }


  DakikadakiStepSayisi = DakikadakiStepSayisiBul(StepHizi);

  Timer1.initialize(80);
  Timer1.attachInterrupt( timerIsr );
  //Timer1.pwm(led, 1023,100000);

}

void loop() {


  debouncer.update();

  if ( debouncer.fell() ) {
    AyarModu = !AyarModu;
  }

  FormGoruntule();

  while (Serial.available() > 0) {
    static String s = "";

    int thisChar = Serial.read();
    if ((thisChar == ';') || (thisChar == '\n')) {
      Komut(s);
      s = "";
    }
    else {
      s += char(thisChar);
    }
  }
}



void SetStepHizi(unsigned long value) {
  StepHizi = value;
  DakikadakiStepSayisi = DakikadakiStepSayisiBul(value);
  FaEEPROM.SetStepHizi(value);

}

void Komut(String Value) {

  String Anahtar = "";
  String Deger = "";

  int i = Value.indexOf('=');

  Anahtar = Value.substring(0, i);
  Deger = Value.substring(i + 1);

  if (Anahtar == "Speed") {
    SetStepHizi(Deger.toInt());
  }
  else if (Anahtar == "SariLed") {
    digitalWrite(8, Deger.toInt() );
  }
  else {
    Serial.println("Hatali Komut");
    Serial.println("Speed=10; Komutu ile Motor hizini 10 yapabilirsiniz. ");
    Serial.println("SariLed=1; Komutu ile Sari Ledi yakabilirsiniz.");

    Serial.println("Anahtar ." + Anahtar);
    Serial.println("Deger ." + Deger);

  }

}

void timerIsr() {
  //DigitalKareDalga(400*81);//400

  DakikadaXDefaStepGonder(DakikadakiStepSayisi);
  //DakikadaXDefaStepGonder(60L);


}


void DakikadaXDefaStepGonder(unsigned long DakikadakiTekrarSayisi) {

  volatile unsigned long Dakika = 60000000;//Microsaniye
  volatile unsigned long MicroSaniyeBeklemeSuresi = (Dakika / DakikadakiTekrarSayisi);

  volatile unsigned long fark = micros() - MicroSaniyeBeklemeSuresi;

  if (ZamanlayiciStepMotor. MicrosaniyedeBir(MicroSaniyeBeklemeSuresi)) {
    digitalWrite(stepPortu, HIGH );
    delayMicroseconds(3);
    digitalWrite(stepPortu, LOW );
  }

}


int JoistikOku(int Port, int DefValue, int MaxValue) {

  int outputValue = 0;
  int sensorValue;

  sensorValue = analogRead(Port);
  if (sensorValue < (DefValue - 2))
    outputValue = map(sensorValue, 0, DefValue, MaxValue, 0);
  else if (sensorValue > (DefValue + 2))
    outputValue = map(sensorValue, DefValue, 1021, 0, (MaxValue * (-1)));
  else
    outputValue = 0;

  return outputValue;

}



void FormGoruntule() {

  String Satir1, Satir2, Satir3, Satir4;

  int button;
  int button2;

  button = JoistikOku(analogInPinX, sensorValueXDef, 3);
  button2 = JoistikOku(analogInPinY, sensorValueYDef, 20);


  if (AyarModu) {

    if (button2 > 1) {
      AyarHanesi++;
    }
    if (button2 < -1) {
      AyarHanesi--;
    }

    if (AyarHanesi < 0)
      AyarHanesi = 0;
    if (AyarHanesi > 3)
      AyarHanesi = 3;

    if AktifSatir==0 

  }
  else if (AyarModu == false) {
    if (button > 1) {
      AktifSatir--;
    }
    if (button < -1) {
      AktifSatir++;
    }

    if (AktifSatir < 0)
      AktifSatir = 0;
    if (AktifSatir > 3)
      AktifSatir = 3;
  }



  //lcd.setCursor(11, imlec);
  //lcd.blink();
  //lcd.noBlink();


  Satir1 = SatirSec(AktifSatir, 0) + "DIAMETER:";
  Satir2 = SatirSec(AktifSatir, 1) + "FLOWRATE :12,34ml/h";
  Satir3 = SatirSec(AktifSatir, 2) + "TIME:";
  Satir4 = SatirSec(AktifSatir, 3) + "ON/OFF :ON";

  LCDYaz2(Satir1, Satir2 , Satir3, Satir4, 300);


}

String SatirSec(int imlec, int Satir) {

  String SecimHarfi = "*";

  if (AyarModu)
    SecimHarfi = ">" + String(AyarHanesi) + "-";

  if (imlec == Satir)
    return SecimHarfi;
  else
    return " ";
}



void LCDYaz2(String Satir1, String Satir2, String Satir3, String Satir4, long Sure) {

  int x = FaButton1.JoyY;

  if (sakla_1.Sakla(Satir1, Satir2, Satir3, Satir4))  {

    digitalWrite( 13, digitalRead( 13 ) ^ 1 );
    lcd.noBlink();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(sakla_1.Satir1);
    lcd.setCursor(0, 1);

    lcd.print(sakla_1.Satir2);
    lcd.setCursor(0, 2);

    lcd.print(sakla_1.Satir3);
    lcd.setCursor(0, 3);
    lcd.print(sakla_1.Satir4);

    Serial.println("");
    Serial.println("--------------------");
    Serial.println(sakla_1.Satir1);
    Serial.println(sakla_1.Satir2);
    Serial.println(sakla_1.Satir3);
    Serial.println(sakla_1.Satir4);
    Serial.println("--------------------");
    Serial.println("");

    delay(Sure);


  }
}




long DakikadakiStepSayisiBul(unsigned long pStepHizi) {
  return map(pStepHizi, 10, 20, 400, 200);
}








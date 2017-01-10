#include <TimerOne.h>

#include <LiquidCrystal.h>
#include <EEPROM.h>
#include "FaEEPROM.h"
#include "FaButton.h"
#include "FaDegerSakla.h"
#include "FaZamanlayici.h";
#include "FaDecimalView.h";
#include "FaGeriSayim.h";

#include <Bounce2.h>

const int analogInPinSW = A3;  //
const int analogInPinY = A4;  // Analog input pin that the potentiometer is attached to
const int analogInPinX = A5;  // Analog input pin that the potentiometer is attached to
int sensorValueYDef = 0;        // value read from the pot
int sensorValueXDef = 0;

bool StepAcik = false;
bool AyarModu = false;
int  AyarHanesi = 1;

int AktifSatir = 0;


byte FormButton = 0;
byte IsikSiddeti = 200;



volatile double DakikadakiTurSayisi = 0;
volatile long DakikadakiStepSayisi = 0;

volatile unsigned int stepPortu = 7;
volatile unsigned int stepDIR = 8;


volatile unsigned long MicroSaniyeBeklemeSuresi = 0;
volatile unsigned long _DakikadakiTekrarSayisi;




volatile long HizliSarma = 0;


LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
FaDegerSakla sakla_1;

FaZamanlayici ZamanlayiciStepMotor;
FaZamanlayici ZamanlayiciForm;
FaZamanlayici ZamanlayiciButton;

FaZamanlayici ZamanlayiciSure;
FaGeriSayim GeriSayim;




FaButton FaButton1;
FaDecimalView DiameterValue;
FaDecimalView FlowrateValue;
FaDecimalView TimeValue;



Bounce debouncer = Bounce();


// diameter sign (ø)
byte newChar0[8] = {
  B00000,
  B00000,
  B01101,
  B10010,
  B10101,
  B01001,
  B10110,
  B00000
};

// dakika
byte newChar1[8] = {
  B10000,
  B10000,
  B10000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

// saniye
byte newChar2[8] = {
  B10100,
  B10100,
  B10100,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};



void setup() {

  lcd.createChar(0, newChar0);
  lcd.createChar(1, newChar1);
  lcd.createChar(2, newChar2);

  TimeValue.Sparator = char(1);
  TimeValue.SaatModu = true;

  DiameterValue.SetValue(2000);
  FlowrateValue.SetValue(2000);
  TimeValue.SetValue(500);

  sensorValueYDef = analogRead(analogInPinY);
  sensorValueXDef = analogRead(analogInPinX);

  pinMode(stepPortu, OUTPUT);
  pinMode(stepDIR, OUTPUT);

  pinMode(13, OUTPUT);

  pinMode(analogInPinSW, INPUT_PULLUP);
  debouncer.attach(analogInPinSW);
  debouncer.interval(10); // interval in ms

  Serial.begin(9600);

  lcd.clear();
  lcd.begin(20, 4);
  lcd.print("www.inovenso.com");

  delay(1000);


  FaEEPROM.RestartSay();





  Timer1.initialize(80);
  Timer1.attachInterrupt( timerIsr );
  //Timer1.pwm(led, 1023,100000);

}

void loop() {

  if (StepAcik)
  {
    if (ZamanlayiciSure.MicrosaniyedeBir(1000000L)) {
      TimeValue.SetMicros(GeriSayim.GetKalanZaman());
      //TimeValue.UpDownDigit(4, -1);
    }
  }

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




void Komut(String Value) {

  String Anahtar = "";
  String Deger = "";

  int i = Value.indexOf('=');

  Anahtar = Value.substring(0, i);
  Deger = Value.substring(i + 1);

  if (Anahtar == "Speed") {

    //SetStepHizi(Deger.toInt());

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

  //DakikadaXDefaStepGonder(DakikadakiStepSayisi);


  //if(StepAcik)
  //  DakikadaXDefaStepGonder(1600L * 700L);


  if ((TimeValue.GetValue() > 0) && (StepAcik))
    //DakikadaXDefaStepGonder(1000000L);
    //DakikadaXDefaStepGonder(DakikadakiStepSayisi);
    MikroSaniyedeBirDefaStepGonder(MicroSaniyeBeklemeSuresi);

  else if (HizliSarma > 0)
    DakikadaXDefaStepGonder(HizliSarma);



}



//volatile unsigned long Dakika = 60000000L - 100000 ;//geri kaldı
//volatile unsigned long Dakika = 60000000L - 1000000 ;//ileri gitti
//volatile unsigned long Dakika = 60000000L - 500000 ;//ileri gitti
//volatile unsigned long Dakika = 60000000L - 300000 ;//ileri gitti
volatile unsigned long Dakika = 60000000L; //-   1000000 ;





void DakikadaXDefaStepGonder(unsigned long DakikadakiTekrarSayisi) {
  //volatile unsigned long Dakika = 60000000;//Microsaniye

  // Bölme işlemi zaman alabileceği için burada if kontrollü yapıldı
  if (_DakikadakiTekrarSayisi != DakikadakiTekrarSayisi)
  {
    volatile unsigned long HataPayi = 3100 * (DakikadakiTekrarSayisi) / 64;

    _DakikadakiTekrarSayisi != DakikadakiTekrarSayisi;
    MicroSaniyeBeklemeSuresi = ((Dakika - HataPayi) / DakikadakiTekrarSayisi);
  }

  if (ZamanlayiciStepMotor. MicrosaniyedeBir(MicroSaniyeBeklemeSuresi)) {

    digitalWrite(stepPortu, HIGH );
    delayMicroseconds(4);
    digitalWrite(stepPortu, LOW );

  }
}


void MikroSaniyedeBirDefaStepGonder(unsigned long mikrosaniye) {

  if (ZamanlayiciStepMotor.MicrosaniyedeBir(mikrosaniye)) {

    digitalWrite(stepPortu, HIGH );
    delayMicroseconds(4);
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

  button = JoistikOku(analogInPinX, sensorValueXDef, 20);
  button2 = JoistikOku(analogInPinY, sensorValueYDef, 30);



  if (AyarModu) {

    if (AktifSatir != 3)
    {
      if (button2 > 20) {
        AyarHanesi++;
        delay(300);
      }

      else if (button2 < -20) {
        AyarHanesi--;
        delay(300);
      }

      if (AyarHanesi < 1)
        AyarHanesi = 1;
      else if (AyarHanesi > 4)
        AyarHanesi = 4;
    }

    if (AktifSatir == 0)
    {
      if (button > 15) {
        DiameterValue.UpDownDigit(AyarHanesi, 1);
        delay(300);
      }
      else if (button < -15) {
        DiameterValue.UpDownDigit(AyarHanesi, -1);
        delay(300);
      }
    }
    else if (AktifSatir == 1)
    {
      if (button > 15) {
        FlowrateValue.UpDownDigit(AyarHanesi, 1);
        delay(300);
      }
      else if (button < -15) {
        FlowrateValue.UpDownDigit(AyarHanesi, -1);
        delay(300);
      }
    }
    else if (AktifSatir == 2)
    {
      if (button > 15) {
        TimeValue.UpDownDigit(AyarHanesi, 1);

        GeriSayim.SetToplamZaman(1000000L * TimeValue.GetToplamSaniye());



        delay(300);
      }
      else if (button < -15) {
        TimeValue.UpDownDigit(AyarHanesi, -1);
        GeriSayim.SetToplamZaman(1000000L * TimeValue.GetToplamSaniye());



        delay(300);
      }
    }

    else if (AktifSatir == 3)
    {
      if (button > 14) {

        //DakikadakiTurSayisi = 1 / (3.1415 * FlowrateValue.GetValue()/100 * DiameterValue.GetValue()/100 * DiameterValue.GetValue()/100 / 4000 ) / 180;
        
        DakikadakiTurSayisi = (3.1415 * (double)FlowrateValue.GetValue()/100.00 * (double)DiameterValue.GetValue()/100.00 * (double)DiameterValue.GetValue()/100.00 / 4000.00 ) / 180.00;
        
        DakikadakiStepSayisi  = 6400 * DakikadakiTurSayisi;

        double C2=(double)DiameterValue.GetValue()/100.00  *  (double)DiameterValue.GetValue()/100.00;
        

        MicroSaniyeBeklemeSuresi= (long)(220.98 * C2  / ((double)FlowrateValue.GetValue()/100.00)) ;


          Serial.println(((double)DiameterValue.GetValue()/100.00  * (double)DiameterValue.GetValue()/100.00));
          Serial.println(FlowrateValue.GetValue()/100);


          Serial.println("MicroSaniyeBeklemeSuresi");
          Serial.println(MicroSaniyeBeklemeSuresi);


          

          

        StepAcik = true;
        ZamanlayiciSure.Reset();
        GeriSayim.Basla();
        //delay(50);
      }
      else if (button < -14) {
        StepAcik = false;
        GeriSayim.Durdur();
        //delay(50);
      }

      else if (button2 > 5) {
        digitalWrite(stepDIR, LOW);
        HizliSarma = map(button2, 3, 28, 1L, 1600L * 500L);
      }
      else if (button2 < -5) {
        HizliSarma = map(button2, -3, -28, 1L, 1600L * 500L);
        digitalWrite(stepDIR, HIGH);
      }
      else
      {
        HizliSarma = 0;
      }


    }




  }
  else if (AyarModu == false) {
    if (button > 1) {
      AktifSatir--;
      delay(300);
    }
    if (button < -1) {
      AktifSatir++;
      delay(300);
    }

    if (AktifSatir < 0)
      AktifSatir = 0;
    if (AktifSatir > 3)
      AktifSatir = 3;
  }

  Satir1 = SatirSec(AktifSatir, 0) + "DIAMETER:" + DiameterValue.ToString() + " " + char(0); // "ø";
  Satir2 = SatirSec(AktifSatir, 1) + "FLOWRATE:" + FlowrateValue.ToString() + " ml/h";
  Satir3 = SatirSec(AktifSatir, 2) + "TIME    :" + TimeValue.ToString() + char(2);

  if (StepAcik)
    Satir4 = SatirSec(AktifSatir, 3) + "ON/OFF  :ON ";
  else
    Satir4 = SatirSec(AktifSatir, 3) + "ON/OFF  :OFF";


  LCDYaz2(Satir1, Satir2 , Satir3, Satir4);


  if (AktifSatir == 3)
  {
    lcd.noBlink();
  }
  else if (AyarModu)
  {

    if (AyarHanesi > 2)
      lcd.setCursor(10 + AyarHanesi , AktifSatir);
    else
      lcd.setCursor(9 + AyarHanesi , AktifSatir);

    lcd.blink();
  }


}

String SatirSec(int imlec, int Satir) {

  String SecimHarfi = "*";

  if (AyarModu)
  {
    SecimHarfi = ">" ;//+ String(AyarHanesi) + "-";
  }
  if (imlec == Satir)
  {
    return SecimHarfi;
  }
  else
    return " ";
}



void LCDYaz2(String Satir1, String Satir2, String Satir3, String Satir4) {

  //int x = FaButton1.JoyY;



  if (sakla_1.Sakla(Satir1, Satir2, Satir3, Satir4))  {



    digitalWrite( 13, digitalRead( 13 ) ^ 1 );
    lcd.noBlink();
    //lcd.clear();

    if (sakla_1.Degisti1())
    {
      lcd.setCursor(0, 0);
      lcd.print(sakla_1.Satir1);
    }
    if (sakla_1.Degisti2())
    {

      lcd.setCursor(0, 1);
      lcd.print(sakla_1.Satir2);
    }
    if (sakla_1.Degisti3())
    {

      lcd.setCursor(0, 2);
      lcd.print(sakla_1.Satir3);
    }
    if (sakla_1.Degisti4())
    {

      lcd.setCursor(0, 3);
      lcd.print(sakla_1.Satir4);
    }
    /*
        Serial.println("");
        Serial.println("--------------------");
        Serial.println(sakla_1.Satir1);
        Serial.println(sakla_1.Satir2);
        Serial.println(sakla_1.Satir3);
        Serial.println(sakla_1.Satir4);
        Serial.println("--------------------");
        Serial.println("");
    */
    //delay(Sure);

  }
}











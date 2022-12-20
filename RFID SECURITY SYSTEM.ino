
#include <SPI.h>       // tag
#include <MFRC522.h>  //tag
#include <LiquidCrystal.h> // for lcd screen
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

const int rs = 8, en = 7, d4 = 6, d5 = 5, d6 = 4, d7 = 3; //defining pins of lcd screen
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
long duration;
int distance;
int trigPin=A0;
int echoPin=A1;
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println(" PUNCH YOUR CARD TO THE READER...");
  Serial.println();
  lcd.begin(16, 2);//dimensions of lcd
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(2,OUTPUT);
}

void loop() 
{ 
  analogRead(A5);
 
  digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;

if(analogRead(A5)<=10)
{
Serial.print("analog value :  "); Serial.println(analogRead(A5));
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
delay(2000);
lcd.setCursor(4,0);  
lcd.print("SEE");
lcd.setCursor(2,1);
lcd.print("monitor");
}
if(distance<=35)
{
lcd.setCursor(2,0);  
lcd.print("PUNCH CARD....");
}
if(distance>35)
{
lcd.clear();  
}
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "DD F9 90 79") //change here the UID of the card/cards that you want to give access
  {
    lcd.setCursor(3,0);  
    lcd.clear();
    Serial.println("Authorized access");
    Serial.println();
    delay(3000);
    digitalWrite(2,HIGH);
    lcd.setCursor(3,0 );
    lcd.print("AUTHORIZED");
    lcd.setCursor(4,1);
    lcd.print("ACCESS...");
    delay(5000);
    lcd.clear();
      }
 
 else   {
   lcd.setCursor(3,0);  
    lcd.clear();
    Serial.println(" Access denied");
    delay(3000);
    digitalWrite(2,LOW);
    lcd.setCursor(4,0 );
    lcd.print("ACCESS");
lcd.setCursor(4,1);
lcd.print("DENIED!!!");
    delay(5000);
    lcd.clear();
  }
} 

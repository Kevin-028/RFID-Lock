//Programa: Sistema de trava eletrica com RFID
#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
#define F 4

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

void setup() 
{
  Serial.begin(9600);   // Inicia a serial
  SPI.begin();      // Inicia  SPI bus
  mfrc522.PCD_Init();   // Inicia MFRC522
  Serial.println("Aproxime o seu cartao do leitor...");
  Serial.println();
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);

  digitalWrite(4, HIGH);
}

void loop() 
{

  // Procura por cartao RFID
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Seleciona o cartao RFID
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Mostra UID na serial
  Serial.print("UID da tag :");
  String conteudo= "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Mensagem : ");
  conteudo.toUpperCase();
  Serial.println(conteudo);
  if (conteudo.substring(1) == "13 F9 9B 0E") //UID 1 - Cartao
  {
    Serial.println("Liberado ");
    Serial.println();
    digitalWrite(2, HIGH); 
    digitalWrite(4, 0); 


    delay(3000);           // espera 3 segundos
    digitalWrite(2, LOW); 
    digitalWrite(4, 1); 

  }  
}
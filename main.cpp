// SimpleRx - the slave or the receiver

#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN 9
#define CSN_PIN 10

const byte address[][6] = {"1node", "2node", "3node", "4node", "5node", "6node"};

RF24 radio(CE_PIN, CSN_PIN);


int dataReceived;

bool newData = false; 

bool ledStatus = false; 
int LED = 7;

void getData();
void showData();

void setup()
{ 

  pinMode(LED, OUTPUT);

  Serial.begin(9600);

  Serial.println(F("SimpleRx Starting"));
  radio.begin();
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(111);
  radio.setPALevel(RF24_PA_MAX);
  radio.openReadingPipe(1, address[0]);
  radio.startListening();
}

void loop()
{
  getData();
  showData();
}

void getData()
{
  uint8_t pipeNum;
  if (radio.available(&pipeNum))
  {
    Serial.print(F("Got data on pipe: "));
    Serial.println(pipeNum);
    radio.read(&dataReceived, sizeof(dataReceived));
    newData = true;
  }
}

void showData()
{
  if (newData == true)
  {
    Serial.println("Received data");
    Serial.println(dataReceived);
    if(!ledStatus) {
      digitalWrite(LED, HIGH);
      ledStatus = true;
    } 
    else {
      digitalWrite(LED, LOW);
      ledStatus = false;
    }
    
    newData = false;
  }
}
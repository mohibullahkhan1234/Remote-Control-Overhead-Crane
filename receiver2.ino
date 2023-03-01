
// SimpleRx - the slave or the receiver
#include <RF24Network.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN   7
#define CSN_PIN 8
const uint16_t this_node = 01;
const uint16_t other_node = 00;

RF24 radio(CE_PIN, CSN_PIN);
RF24Network network(radio);
bool newData = false;
bool aux;
int counter = 0;
bool test;
int aux1;
int aux2;
int counter1 = 0;
int counter2 = 0;
struct payload_t{
char dataReceived[10]; // this must match dataToSend in the TX
char commandreceived[10];

};
payload_t payload; 

int led_1 = A0;
int led_2 = A1;
int led_3 = A2;
int led_4 = A3;
int led_5 = A4;
int led_6 = A5;
int led_7 = 2;
int led_8 = 3;
int rst = 4;

  unsigned long now;
  unsigned long prev = 0;
  unsigned long refreshInterval; 
//===========

void setup() {

    Serial.begin(9600);
    pinMode(led_1,OUTPUT);    //left slow
    pinMode(led_2,OUTPUT);    //left fast
    pinMode(led_3,OUTPUT);    //right slow
    pinMode(led_4,OUTPUT);    //right fast 
    pinMode(led_5,OUTPUT);    //down slow
    pinMode(led_6,OUTPUT);    //down fast
    pinMode(led_7,OUTPUT);    //up slow
    pinMode(led_8,OUTPUT);    //up fast 
    pinMode(rst, OUTPUT);   
    Serial.println("SimpleRx Starting");
    SPI.begin();    
    radio.begin();
    
    radio.setChannel(90);
    network.begin(this_node);
    radio.setDataRate( RF24_250KBPS );
    radio.setRetries(3,5);
    //radio.openReadingPipe(1, this_node);
    //radio.startListening();
}

//=============

void loop() {
    network.update();
    getData();
    showData();
}

//==============

void getData() {
    aux =1;

    while ( network.available() ) {
     
        RF24NetworkHeader header;
        network.read(header, &payload, sizeof(payload));
        Serial.println("packet received");
        delay(10); //time given to properly read data and then move on to next instruction
        newData = true;
        aux = 0;
    }
   
}
void(* resetFunc) (void) = 0; 

void showData() {
    if (newData == true) {
        Serial.print("Data received ");
        Serial.println(payload.dataReceived);
        delay(5);        
        Serial.println(payload.commandreceived);                   
        if(payload.commandreceived[0] == '1')
        {// Serial.println("bock executed");
          digitalWrite(led_1, LOW);
          digitalWrite(led_2, HIGH);
          digitalWrite(led_3,HIGH);
          digitalWrite(led_4,HIGH);
          digitalWrite(led_5,HIGH);
          digitalWrite(led_6,HIGH);
          digitalWrite(led_7,HIGH);
          digitalWrite(led_8,HIGH);
                  }
        else if (payload.commandreceived[1] == '1')
        {         
          digitalWrite(led_1, HIGH);  
          digitalWrite(led_2, LOW);
          digitalWrite(led_3,HIGH);
          digitalWrite(led_4,HIGH);
          digitalWrite(led_5,HIGH);
          digitalWrite(led_6,HIGH);
          digitalWrite(led_7,HIGH);
          digitalWrite(led_8,HIGH);
          
        }else if (payload.commandreceived[2] == '1')
        {
          digitalWrite(led_1,HIGH);  
          digitalWrite(led_2,HIGH) ;
          digitalWrite(led_3,LOW);
          digitalWrite(led_4,HIGH);
          digitalWrite(led_5,HIGH);
          digitalWrite(led_6,HIGH);
          digitalWrite(led_7,HIGH);
          digitalWrite(led_8,HIGH);
          
        }else if(payload.commandreceived[3] == '1')
        {
          digitalWrite(led_1,HIGH);  
          digitalWrite(led_2,HIGH);
          digitalWrite(led_3,HIGH);
          digitalWrite(led_4,LOW);
          digitalWrite(led_5,HIGH);
          digitalWrite(led_6,HIGH);
          digitalWrite(led_7,HIGH);
          digitalWrite(led_8,HIGH);
        }
        else if(payload.commandreceived[4] == '1'){
          digitalWrite(led_1,HIGH);          
          digitalWrite(led_2,HIGH);
          digitalWrite(led_3,HIGH);          
          digitalWrite(led_4,HIGH);
          digitalWrite(led_5,LOW);
          digitalWrite(led_6,HIGH);
          digitalWrite(led_7,HIGH);
          digitalWrite(led_8,HIGH);           
        }else if(payload.commandreceived[5] == '1'){
          digitalWrite(led_1,HIGH);          
          digitalWrite(led_2,HIGH);
          digitalWrite(led_3,HIGH);          
          digitalWrite(led_4,HIGH);
          digitalWrite(led_5,HIGH);
          digitalWrite(led_6,LOW);
          digitalWrite(led_7,HIGH);
          digitalWrite(led_8,HIGH);
        }else if(payload.commandreceived[6] == '1'){
          digitalWrite(led_1,HIGH);          
          digitalWrite(led_2,HIGH);
          digitalWrite(led_3,HIGH);          
          digitalWrite(led_4,HIGH);
          digitalWrite(led_5,HIGH);
          digitalWrite(led_6,HIGH);
          digitalWrite(led_7,LOW);
          digitalWrite(led_8,HIGH);
        }else if(payload.commandreceived[7] == '1'){
          digitalWrite(led_1,HIGH);          
          digitalWrite(led_2,HIGH);
          digitalWrite(led_3,HIGH);          
          digitalWrite(led_4,HIGH);
          digitalWrite(led_5,HIGH);
          digitalWrite(led_6,HIGH);
          digitalWrite(led_7,HIGH);
          digitalWrite(led_8,LOW);
        }else{
          digitalWrite(led_1,HIGH);          
          digitalWrite(led_2,HIGH);
          digitalWrite(led_3,HIGH);          
          digitalWrite(led_4,HIGH);
          digitalWrite(led_5,HIGH);
          digitalWrite(led_6,HIGH);
          digitalWrite(led_7,HIGH);
          digitalWrite(led_8,HIGH);
        }

        newData = false;


}  
delay(5);
           if (counter1%2 == 0){
             aux2 = aux;
             counter1 = 0;
           }else{
             aux1 = aux;
           }
           counter1++;
           if(aux1 * aux2 == 1){
            counter++;             
           }if(aux1 + aux2 == 1){
            counter= 0;
                       }                       
Serial.println(counter);          
            if(counter >50){
Serial.println("leds off.....");  
        digitalWrite(led_1,HIGH);          
          digitalWrite(led_2,HIGH);
          digitalWrite(led_3,HIGH);          
          digitalWrite(led_4,HIGH);
          digitalWrite(led_5,HIGH);
          digitalWrite(led_6,HIGH);
          digitalWrite(led_7,HIGH);
          digitalWrite(led_8,HIGH);
          resetFunc();
/*while(!network.available()){

counter2++;
}*/          
            }
          Serial.print("aux : ");
       Serial.println(aux);
}
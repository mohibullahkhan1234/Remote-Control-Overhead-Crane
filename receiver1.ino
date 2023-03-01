// SimpleRx - the slave or the receiver
#include <RF24Network.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN   7
#define CSN_PIN 8
#define  A0 led_1
#define  A1 led_2
#define  A2 led_3
#define  A3 led_4
#define  A4 led_5
#define  A5 led_6
const uint16_t this_node = 03;
const uint16_t other_node = 00;

RF24 radio(CE_PIN, CSN_PIN);
RF24Network network(radio);
bool newData = false;
struct payload_t{
char dataReceived[10]; // this must match dataToSend in the TX
char commandreceived[10];
int txIntervalreceived;
};
payload_t payload;
int led_1,led_2,led_3,led_4,led_5,led_6;

int led_7 = 2;
int led_8 = 3;
int vcc;
int aux;
int aux1;
int aux2;
int vccpin = 4;
int counter;
int counter1;
unsigned long currentMillis;
unsigned long prevMillis;
unsigned long txIntervalMillis = 1000;
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
    pinMode(vccpin, OUTPUT); // vcc for relay module    
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
aux = 1;
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
        if(payload.commandreceived[0] == '1' )
        {// Serial.println("bock executed");
          digitalWrite(led_1, LOW);
          digitalWrite(led_2, HIGH);
          digitalWrite(led_3,HIGH);
          digitalWrite(led_4,HIGH);
          digitalWrite(led_5,HIGH);
          digitalWrite(led_6,HIGH);
                  }
        else if (payload.commandreceived[1] == '1')
        {         
          digitalWrite(led_1, HIGH);  
          digitalWrite(led_2, HIGH);
          digitalWrite(led_3,LOW);
          digitalWrite(led_4,HIGH);
          digitalWrite(led_5,HIGH);
          digitalWrite(led_6,HIGH);

          
        }else if (payload.commandreceived[2] == '1')
        {
          digitalWrite(led_1,HIGH);  
          digitalWrite(led_2,HIGH) ;
          digitalWrite(led_3, HIGH);
          digitalWrite(led_4,LOW);
          digitalWrite(led_5,HIGH);
          digitalWrite(led_6,HIGH);
   
        }else if(payload.commandreceived[3] == '1')
        {
          digitalWrite(led_1,HIGH);  
          digitalWrite(led_2,HIGH);
          digitalWrite(led_3,HIGH);
          digitalWrite(led_4,HIGH);
          digitalWrite(led_5,LOW);
          digitalWrite(led_6,HIGH);

        }
        else if(payload.commandreceived[0] == '1' && payload.commandreceived[4] == '1' ){
          digitalWrite(led_1,LOW);          
          digitalWrite(led_2,HIGH);
          digitalWrite(led_3,LOW);          
          digitalWrite(led_4,HIGH);
          digitalWrite(led_5,HIGH);
          digitalWrite(led_6,HIGH);
          
        }else if(payload.commandreceived[1] == '1' && payload.commandreceived[4] == '1'){
          digitalWrite(led_1,HIGH);          
          digitalWrite(led_2, LOW);
          digitalWrite(led_3,LOW);          
          digitalWrite(led_4,HIGH);
          digitalWrite(led_5,HIGH);
          digitalWrite(led_6,HIGH);
        }else if(payload.commandreceived[2] == '1' && payload.commandreceived[4] == '1'){
          digitalWrite(led_1,HIGH);          
          digitalWrite(led_2,HIGH);
          digitalWrite(led_3,HIGH);          
          digitalWrite(led_4,LOW);
          digitalWrite(led_5,HIGH);
          digitalWrite(led_6,LOW);
        }else if(payload.commandreceived[3] == '1' && payload.commandreceived[5] == '1'){
          digitalWrite(led_1,HIGH);          
          digitalWrite(led_2,HIGH);
          digitalWrite(led_3,HIGH);          
          digitalWrite(led_4,HIGH);
          digitalWrite(led_5,LOW);
          digitalWrite(led_6,LOW);
        }else{
          digitalWrite(led_1,HIGH);          
          digitalWrite(led_2,HIGH);
          digitalWrite(led_3,HIGH);          
          digitalWrite(led_4,HIGH);
          digitalWrite(led_5,HIGH);
          digitalWrite(led_6,HIGH);
        }
         //currentMillis = millis();
 /*   if (currentMillis - prevMillis >= payload.txIntervalreceived) {
          digitalWrite(led_1,1);          
          digitalWrite(led_2,1);
          digitalWrite(led_3,1);          
          digitalWrite(led_4,1);
          digitalWrite(led_5,1);
          digitalWrite(led_6,1);
          digitalWrite(led_7,1);
          digitalWrite(led_8,1);
        prevMillis = millis(); }*/
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

          resetFunc();
/*while(!network.available()){

counter2++;
}*/          
            }
         // Serial.print("aux : ");
      // Serial.println(aux);
}

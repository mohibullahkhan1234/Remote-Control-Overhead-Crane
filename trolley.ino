// SimpleRx - the slave or the receiver
#include <RF24Network.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN   7
#define CSN_PIN 8
const uint16_t this_node = 02;
const uint16_t other_node = 00;
int led_1 = 2;
int led_2 = 3;
bool newData;
int counter;
int counter1;
int aux;
int aux1;
int aux2;

struct payloadreceived{
  char y_motor[3]="";
};
payloadreceived payloadr;
RF24 radio(CE_PIN, CSN_PIN);
RF24Network network(radio);


//char y_motor[3]; 
void setup(){
Serial.begin(9600);
 SPI.begin();    
    radio.begin();
  
    radio.setChannel(90);
      
    network.begin(this_node);
    radio.setDataRate( RF24_250KBPS );
    radio.setRetries(3,5);
pinMode(led_1,OUTPUT);    
pinMode(led_2,OUTPUT);  
}

void loop() {
 
    network.update();
    getData();
    showData();
}
void(* resetFunc) (void) = 0; 

void getData() {
   aux =1;
    while ( network.available() ) {
        RF24NetworkHeader header1;
        network.read(header1, &payloadr, sizeof(payloadr));
        delay(10); //time given to properly read data and then move on to next instruction
        newData = true;
   aux = 0;
    }
}
void showData() {
    if (newData == true) {
        Serial.print("Data received ");
        Serial.println(payloadr.y_motor);
        delay(5);
        if(payloadr.y_motor[0] == '1')
{  Serial.println(payloadr.y_motor);
digitalWrite(led_1, HIGH);
digitalWrite(led_2, LOW);
}else if(payloadr.y_motor[1] == '1')
{
  digitalWrite(led_1, LOW);
digitalWrite(led_2, HIGH);
}else
{
digitalWrite(led_1, LOW);
digitalWrite(led_2, LOW); 
Serial.println("Executed....");      
}
        newData = false;
    } 
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
        digitalWrite(led_1,LOW);          
          digitalWrite(led_2,LOW);   
          resetFunc();
/*while(!network.available()){

counter2++;
}*/          
            }
          Serial.print("aux : ");
       Serial.println(aux);   
}
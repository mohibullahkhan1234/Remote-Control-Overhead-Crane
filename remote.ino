// SimpleTx - the master or the transmitter
#include <RF24Network.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


#define CE_PIN   7
#define CSN_PIN 8
#define  A0 input_pin1
#define  A1 input_pin2
#define  A2 input_pin3
#define  A3 input_pin4
#define  A4 input_pin5
#define  A5 input_pin6
//#define  2  input_pin7
//#define  3  input_pin8
RF24 radio(CE_PIN, CSN_PIN); // Create a Radio
RF24Network network(radio);
const uint16_t this_node = 00;
const uint16_t other_node = 01;
const uint16_t another_node = 03;
const uint16_t another_another_node = 02;
//bool k;
bool rslt;
int emergency_pin =  5;
int input_pin1 = A0;
int input_pin2 = A1;
int input_pin3 = A2;
int input_pin4 = A3;
int input_pin5 = A4;
int input_pin6 = A5;
int input_pin7 = 2;
int input_pin8 = 3;
int a,c;

char txNum = '0'; 
 // send once per second

unsigned long currentMillis;
unsigned long prevMillis;
//unsigned long txIntervalMillis = 500;
struct payload_t{
char dataToSend[10] = "message 0";
char commandsent[7] = "000000";
unsigned long txIntervalMillis = 100;
};

payload_t payload;

char y_motor[3] = "00"; 


void setup() {
    SPI.begin();

    Serial.begin(9600);
    pinMode(input_pin1, INPUT );
    pinMode(input_pin2, INPUT );
    pinMode(input_pin3, INPUT);
    pinMode(input_pin4, INPUT);
    pinMode(input_pin5, INPUT );
    pinMode(input_pin6, INPUT );
    pinMode(input_pin7, INPUT);
    pinMode(input_pin8, INPUT);
  

    //Serial.println("SimpleTx Starting");  
    radio.begin();
    
    radio.setChannel(90);
    network.begin(this_node);
    radio.setDataRate( RF24_250KBPS );
    radio.setRetries(3,5); // delay, count
   // radio.openWritingPipe(node01);
 
}

//====================

void loop() { 
  
    network.update();    
    currentMillis = millis();
    if (currentMillis - prevMillis >= payload.txIntervalMillis) {
        send();
        prevMillis = millis();
    }
    
}     

//====================
void switch_select(){
if(digitalRead(input_pin8)){
  a++;
  if(a>400){
    c = !c;
  }
}
    if (c){
    RF24NetworkHeader header(other_node);        
    rslt = network.write( header, &payload, sizeof(payload) );   
    }
    else
    {
    RF24NetworkHeader header1(another_node); 
    rslt = network.write( header1, &payload, sizeof(payload));
    }  
}


void send() {
  
    //char dataToSend[10] = "Message 0"; 
    switch_select();
            
    if( digitalRead(input_pin1)){
         payload.commandsent[0] = '1';
         payload.commandsent[1] = '0';
         payload.commandsent[2] = '0';
         payload.commandsent[3] = '0';
         payload.commandsent[4] = '0';
         
              
        // Always use sizeof() as it gives the size as the number of bytes.
        // For example if dataToSend was an int sizeof() would correctly return 2
    }else if( digitalRead(input_pin2)){
         payload.commandsent[0] = '0';   
         payload.commandsent[1] = '1';   
         payload.commandsent[2] = '0';
         payload.commandsent[3] = '0';
         payload.commandsent[4] = '0';

                  
        // Always use sizeof() as it gives the size as the number of bytes.
        // For example if dataToSend was an int sizeof() would correctly return 2
    }else if( digitalRead(input_pin3)) {
   payload.commandsent[0] = '0';
   payload.commandsent[1] = '0';      
   payload.commandsent[2] = '1';
   payload.commandsent[3] = '0';
   payload.commandsent[4] = '0';


       } else if ( digitalRead(input_pin4)){
   payload.commandsent[0] = '0';
   payload.commandsent[1] = '0';      
   payload.commandsent[2] = '0';
   payload.commandsent[3] = '1';
   payload.commandsent[4] = '0';
                    
       }else if( digitalRead(input_pin1) && digitalRead(input_pin7)){
         payload.commandsent[0] = '1';
         payload.commandsent[1] = '0';
         payload.commandsent[2] = '0';
         payload.commandsent[3] = '0';
         payload.commandsent[4] = '1';
         
              
        // Always use sizeof() as it gives the size as the number of bytes.
        // For example if dataToSend was an int sizeof() would correctly return 2
    }else if( digitalRead(input_pin2)&& digitalRead(input_pin7)){
         payload.commandsent[0] = '0';   
         payload.commandsent[1] = '1';   
         payload.commandsent[2] = '0';
         payload.commandsent[3] = '0';
         payload.commandsent[4] = '1';

                  
        // Always use sizeof() as it gives the size as the number of bytes.
        // For example if dataToSend was an int sizeof() would correctly return 2
    }else if( digitalRead(input_pin3)&& digitalRead(input_pin7)) {
   payload.commandsent[0] = '0';
   payload.commandsent[1] = '0';      
   payload.commandsent[2] = '1';
   payload.commandsent[3] = '0';
   payload.commandsent[4] = '1';


       } else if ( digitalRead(input_pin4)&& digitalRead(input_pin7)){
   payload.commandsent[0] = '0';
   payload.commandsent[1] = '0';      
   payload.commandsent[2] = '0';
   payload.commandsent[3] = '1';
   payload.commandsent[4] = '1';
                    
       }else {
   payload.commandsent[0] = '0';
   payload.commandsent[1] = '0';      
   payload.commandsent[2] = '0';
   payload.commandsent[3] = '0';
   payload.commandsent[4] = '0';
                      
       }
       

    if ( digitalRead(input_pin5)){
    y_motor[0]= '1';
     y_motor[1]= '0';
    RF24NetworkHeader header2(another_another_node);
    network.write(header2, &y_motor, sizeof(y_motor));
//Serial.println("sent...");
    }
    else if(digitalRead(input_pin6)){
    y_motor[0]= '0';
     y_motor[1]= '1';
    RF24NetworkHeader header2(another_another_node);
    network.write(header2, &y_motor, sizeof(y_motor));            
    //Serial.println("executed...");
    }else{
      y_motor[0]= '0';
     y_motor[1]= '0';
    RF24NetworkHeader header2(another_another_node);
    network.write(header2, &y_motor, sizeof(y_motor));            
    //Serial.println("executed...");
    }
  
}

//================

void updateMessage() {
        // so you can see that new data is being sent
    txNum += 1;
    if (txNum > '9') {
        txNum = '0';
    }
    payload.dataToSend[8] = txNum;
}

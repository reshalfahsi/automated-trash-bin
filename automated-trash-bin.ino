#include <Servo.h>
#include <NewPing.h>


#define INF 9999

const int led = 13; //default: 13
const int vcc_hcsr_04 = 49; //default: 49
const int trigger_pin = 51; //default: 51
const int echo_pin = 53; //default: 53

int counter = 0;

int data[5];

Servo myservo;
NewPing hcsr(trigger_pin,echo_pin,200);

void sortdata(){

  for(int i = 0; i<5; i++)
    for(int j = 0; j<5; j++)
      if(data[i]>data[j]){
        int temp = data[i];
        data[i] = data[j];
        data[j] = temp;
      }
 
}


void setup(){

for(int i=0; i<5; i++) data[i] = INF;  
pinMode(vcc_hcsr_04,OUTPUT);
digitalWrite(vcc_hcsr_04,HIGH);
pinMode(led,OUTPUT);
digitalWrite(led,HIGH);
myservo.attach(9);
Serial.begin(115200);

}

void loop(){

if(counter>4) counter = 0;

int reading = hcsr.ping_cm();
Serial.print("RAW DATA: ");
Serial.println(reading);

//MEDIAN FILTER
data[counter++] = reading;

if(counter==4){
sortdata();
Serial.print("FILTERED DATA: ");
Serial.println(data[2]);
if(data[2]>10 || data[2]<2){
  myservo.write(120);
  digitalWrite(led,HIGH);
}

if(data[2]<=10 && data[2]>=2){
  myservo.write(10);
  digitalWrite(led,LOW);
}
}

}
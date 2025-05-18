//using L293D H-bridge
const int forwardPin = 4;
const int backwardPin = 5;
const int delayTime = 1000;
const int but1pin = 7;
const int but2pin = 8;
const int potpin = A5;
const int speedpin = 9;

int but1;
int but2;
int pot;
int speed;

void setup(){
    pinMode(forwardPin,OUTPUT);
    pinMode(backwardPin,OUTPUT);
    pinMode(but1pin,INPUT_PULLUP);
    pinMode(but2pin,INPUT_PULLUP);
}

void loop(){
    but1 = digitalRead(but1pin);
    but2 = digitalRead(but2pin);
    pot = analogRead(potpin);
    speed = map(pot,0,1023,0,255);
    analogWrite(speedpin,speed);

    if(but1 == HIGH){
        digitalWrite(forwardPin,LOW);
    }
    else{
        digitalWrite(forwardPin,HIGH);
    }
    if(but2 == HIGH){
        digitalWrite(backwardPin,LOW);
    }
    else{
        digitalWrite(backwardPin,HIGH);
    }
}

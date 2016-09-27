const int led0 = 8;
const int led1 = 9;
const int led2 = 10;
const int led3 = 11;
const int button0 = 2;
const int button1 = 3;
const int button2 = 4;
const int button3 = 5;
const int lcd = 12;
const int speaker = 13;

void setup() {
  // put your setup code here, to run once:
pinMode(led0,OUTPUT);
pinMode(led1,OUTPUT);
pinMode(led1,OUTPUT);
pinMode(led1,OUTPUT);
pinMode(button0,INPUT_PULLUP);
pinMode(button1,INPUT_PULLUP);
pinMode(button2,INPUT_PULLUP);
pinMode(button3,INPUT_PULLUP);
digitalWrite(led0, LOW);
digitalWrite(led1, LOW);
digitalWrite(led2, LOW);
digitalWrite(led3, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
if (digitalRead(button0) == LOW) {
  digitalWrite(led0,HIGH);
} else {
  digitalWrite(led0,LOW);
}
}

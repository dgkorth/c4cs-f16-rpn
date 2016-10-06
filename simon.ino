#include "pitches.h"
//pins
#define B0 2
#define B1 3
#define B2 4
#define B3 5
#define L0 8
#define L1 9
#define L2 10
#define L3 11
#define LCD 12
#define SPKR 13

// game state
enum game{INSTRUCTION,PROMPT,WIN,LOSE};
game state;

// buttonSequence of buttons to be pressed
const int buttonSequence[] = {B1,B3,B2,B0};
const int ledSequence[] = {L1,L3,L2,L0};

// game levels
int level = 0;

//varibles for PROMPT 
int usrB;
int sublevel = 0;

void setup() {
// initialize serial monitor
Serial.begin(9600);
delay(1000);

// initialize LED pins
pinMode(L0,OUTPUT);
pinMode(L1,OUTPUT);
pinMode(L2,OUTPUT);
pinMode(L3,OUTPUT);

// initialize buttons
pinMode(B0,INPUT_PULLUP);
pinMode(B1,INPUT_PULLUP);
pinMode(B2,INPUT_PULLUP);
pinMode(B3,INPUT_PULLUP);

// test and reset LEDs
Serial.println("test leds");
digitalWrite(L0,HIGH);
digitalWrite(L1,HIGH);
digitalWrite(L2,HIGH);
digitalWrite(L3,HIGH);
delay(3000);
digitalWrite(L0,LOW);
digitalWrite(L1,LOW);
digitalWrite(L2,LOW);
digitalWrite(L3,LOW);

//test speaker
Serial.println("test speaker");
tone(SPKR,NOTE_C4,1000);

//set game to start
state = INSTRUCTION;
level = 0;
}

void gameplay();

void light(int led, int duration);

void lightPattern(int pattern, int reps);

void loop() {
    gameplay();
}

void gameplay() {
    // determine game state
    switch (state) {
    // tell player sequence to be entered
    case INSTRUCTION:
        Serial.println("instruction");
        for (int i = 0; i < (level + 1); i++) {
            light(ledSequence[i],500);
        }
        sublevel = 0;
        state = PROMPT;
        Serial.println("prompt"); 
        break;
    // recieve input from player
    case PROMPT: 
        usrB = -1;
        if (digitalRead(B0) == LOW) {
            usrB = B0;
            light(L0,500);
            while(digitalRead(B0) == LOW) {}
        }
        else if (digitalRead(B1) == LOW) {
            usrB = B1;
            light(L1,500);
            while(digitalRead(B1) == LOW) {}
        }
        else if (digitalRead(B2) == LOW) {
            usrB = B2;
            light(L2,500);
            while(digitalRead(B2) == LOW) {}
        }
        else if (digitalRead(B3) == LOW) {
            usrB = B3;
            light(L3,500);
            while(digitalRead(B3) == LOW) {}
        }
        if (usrB == -1) {
            break;
        }
        if (usrB == buttonSequence[sublevel]) {
            sublevel++;
            if (sublevel == (level + 1)) {
                state = WIN;
                break;
            }
            break;
        } 
        else  {
            state = LOSE;
            break;
        }
        break;
    // tell player they succeeded and move on to next level
    case WIN: 
        Serial.println("win");
        lightPattern(2,2);
        lightPattern(0,3);
        level++;
        delay(1000);
        state = INSTRUCTION;
        Serial.println("prompt");
        break;
    // tell player they lost and reset entire game
    case LOSE:
        Serial.println("lose");
        level = 0;
        lightPattern(1,10);
        delay(20); 
        lightPattern(1,10);
        delay(20);
        lightPattern(1,10);
        delay(2000);
        state = INSTRUCTION;
        break;
    }
}

void light(int led, int duration) {
    Serial.println("light");
    int note;
        if (led == L0) {
            note = NOTE_C2; 
        }
        if (led == L1) {
            note = NOTE_C3; 
        }
        if (led == L2) {
            note = NOTE_C4; 
        }
        if (led == L3) {
            note = NOTE_C5; 
        }
    note = note + (level * 50);
    digitalWrite(led,HIGH);
    tone(SPKR,note,duration);
    delay(duration);
    digitalWrite(led,LOW);
    return;
}

void lightPattern(int pattern, int reps) {
    Serial.println("lightPattern");
    int dur = 100;
    if (pattern == 0) {
        for (int i = 0; i < reps; i++) {
            light(L0,dur);
            light(L1,dur);
            light(L2,dur);
            light(L3,dur);
        }
    }
    if (pattern == 1) {
        dur = 5;
        for (int i = 0; i < reps; i++) {
            light(L3,dur);
            light(L2,dur);
            light(L1,dur);
            light(L0,dur);
        }
    }
    if (pattern == 2) {
        for (int i = 0; i < reps; i ++) {
            light(L3,(dur/2));
            light(L0,(dur/2));
            light(L2,(dur/2));
            light(L1,(dur/2));
        }
    }
    return;
}

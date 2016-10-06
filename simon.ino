#include "pitches.h"
//pins
#define B0 2
#define B1 3
#define B2 4
#define B3 5
#define L0 8
#define L1 8
#define L2 8
#define L3 8
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


void setup() {
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
digitalWrite(L0,HIGH);
digitalWrite(L1,HIGH);
digitalWrite(L2,HIGH);
digitalWrite(L3,HIGH);
delay(3000);
digitalWrite(L0,LOW);
digitalWrite(L1,LOW);
digitalWrite(L2,LOW);
digitalWrite(L3,LOW);
// initialize serial monitor
Serial.begin(9600);
delay(1000);
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
        for (int i = 0; i < level + 1; i++) {
            light(ledSequence[i],500);
        }
        state = PROMPT;
        Serial.println("prompt"); 
        break;
    // recieve input from player
    case PROMPT: 
        usrB = 0;
        if (digitalRead(B0) == LOW) {
            usrB = B0;
            light(L0,500);
        }
        if (digitalRead(B1) == LOW) {
            usrB = B1;
            light(L1,500);
        }
        if (digitalRead(B2) == LOW) {
            usrB = B2;
            light(L2,500);
        }
        if (digitalRead(B3) == LOW) {
            usrB = B3;
            light(L3,500);
        }
        if (usrB == buttonSequence[level]) {
            state = WIN;
        } 
        else if (usrB == 0) {
        }
        else {
            state = LOSE;
        }
        break;
    // tell player they succeeded and move on to next level
    case WIN: 
        Serial.println("win");
        lightPattern(2,2);
        lightPattern(0,3);
        level++;
        state = PROMPT;
        Serial.println("prompt");
        break;
    // tell player they lost and reset entire game
    case LOSE:
        Serial.println("lose");
        lightPattern(2,2);
        lightPattern(1,3);
        level = 0;
        state = PROMPT;
        Serial.println("prompt");
        break;
    }
}

void light(int led, int duration) {
    Serial.println("light");
    int note;
        if (L0) {
            note = NOTE_C3; 
        }
        if (L1) {
            note = NOTE_C4; 
        }
        if (L2) {
            note = NOTE_C5; 
        }
        if (L3) {
            note = NOTE_C6; 
        }
    digitalWrite(led,HIGH);
    tone(8,note,duration);
    delay(duration);
    digitalWrite(led,LOW);
    return;
}

void lightPattern(int pattern, int reps) {
    Serial.println("lightPattern");
    if (pattern == 0) {
        for (int i = 0; i < reps; i++) {
            light(L0,300);
            light(L1,300);
            light(L2,300);
            light(L3,300);
        }
    }
    if (pattern == 1) {
        for (int i = 0; i < reps; i++) {
            light(L3,300);
            light(L2,300);
            light(L1,300);
            light(L0,300);
        } 
    }
    if (pattern == 2) {
        for (int i = 0; i < reps; i ++) {
            light(L3,300);
            light(L0,300);
            light(L2,300);
            light(L1,300);
        }
    }
    return;
}

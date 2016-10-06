#include "pitches.h"
//pins
#DEFINE B1 = 2;
#DEFINE B2 = 3;
#DEFINE B3 = 4;
#DEFINE B4 = 5;
#DEFINE L1 = 8;
#DEFINE L1 = 8;
#DEFINE L1 = 8;
#DEFINE L1 = 8;
#DEFINE LCD = 12;
#DEFINE SPKR = 13;
// game state
enum game{INSTRUCTION,PROMPT,WIN,LOSE};
game state;
// buttonSequence of buttons to be pressed
const int buttonSequence[] = {B1,B2,B2,B0};
const int ledSequence[] = {L1,L3,L2,L0};
// game levels
int level = 0;



void setup() {
// initialize LED pins
pinMode(L0,OUTPUT);
pinMode(L1,OUTPUT);
pinMode(L1,OUTPUT);
pinMode(L1,OUTPUT);
// initialize buttons
pinMode(BUTTON0,INPUT_PULLUP);
pinMode(BUTTON1,INPUT_PULLUP);
pinMode(BUTTON2,INPUT_PULLUP);
pinMode(BUTTON3,INPUT_PULLUP);
// reset LEDs
digitalWrite(L0, LOW);
digitalWrite(L1, LOW);
digitalWrite(L2, LOW);
digitalWrite(L3, LOW);
// initialize serial monitor
Serial.begin(9600);
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
        Serial.println("instruction start");
        for (int i = 0; i < level + 1; i++) {
            light(ledSequence[i],500);
        }
        state = PROMPT;
        Serial.println("change state to prompt"); 
        break;
    // recieve input from player
    case PROMPT: 
        Serial.println("prompt start");
        int i = 0;
        if (digitalRead(B0) == LOW) {
            i = B0;
            light(L0,500);
        }
        if (digitalRead(B1) == LOW) {
            i = B1;
            light(L1,500);
        }
        if (digitalRead(B2) == LOW) {
            i = B2;
            light(L2,500);
        }
        if (digitalRead(B3) == LOW) {
            i = B3;
            light(L3,500);
        }
        if (i == buttonSequence[level]) {
            state = WIN;
            break;
        } 
        if (i == 0) {
        break;
        }
        else {
            state = LOSE;
            break;
        }
    // tell player they succeeded and move on to next level
    case WIN: 
        Serial.println("win");
        lightPattern(2,2);
        lightPattern(0,3);
        level++;
    // tell player they lost and reset entire game
    case LOSE:
        Serial.println("lose");
        lightPattern(2,2);
        lightPattern(1,3);
        level = 0;
    }
}

void light(int led, int duration) {
    Serial.println("call light");
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
    Serial.println("call lightPattern");
    if (pattern == 0) {
        for (int i = 0; i < reps * 4; i++) {
            light(L0,300);
            light(L1,300);
            light(L2,300);
            light(L3,300);
        }
    }
    if (pattern == 1) {
        for (int i = 0; i < reps * 4; i++) {
            light(L3,300);
            light(L2,300);
            light(L1,300);
            light(L0,300);
        } 
    }
    if (pattern == 2) {
        for (int i = 0; i < reps * 4; i ++) {
            light(L3,300);
            light(L0,300);
            light(L2,300);
            light(L1,300);
        }
    }
    return;
}

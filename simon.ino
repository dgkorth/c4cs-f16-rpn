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
// game state
enum game{INSTRUCTION,PROMPT,WIN,LOSE};
game state;
// buttonSequence of buttons to be pressed
char* buttonSequence[] = {button1,button3,button2,button0};
char* ledSequence[] = {led1,led3,led2,led0};
// game levels
int level = 0;

void setup() {
// initialize LED pins
pinMode(led0,OUTPUT);
pinMode(led1,OUTPUT);
pinMode(led1,OUTPUT);
pinMode(led1,OUTPUT);
// initialize buttons
pinMode(button0,INPUT_PULLUP);
pinMode(button1,INPUT_PULLUP);
pinMode(button2,INPUT_PULLUP);
pinMode(button3,INPUT_PULLUP);
// reset LEDs
digitalWrite(led0, LOW);
digitalWrite(led1, LOW);
digitalWrite(led2, LOW);
digitalWrite(led3, LOW);
// initialize serial monitor
Serial.begin(9600);
//set game to start
state = INSTRUCTION;
}

void gameplay();

void light(char* led, int duration);

void lightPattern(int pattern, int reps);

void loop() {
    gameplay();
}

void gameplay() {
    // determine game state
    switch (state) {
    // tell player sequence to be entered
    case INSTRUCTION:
        for (int i = 0; i < level + 1; i++) {
            light(ledSequence[i],500);
        }
        state = PROMPT;
        break;
    // recieve input from player
    case PROMPT:
        char* i;
        if (digitalRead(button0) == HIGH) {
            i = button0;
            light(led0,500);
        }
        if (digitalRead(button1) == HIGH) {
            i = button1;
            light(led1,500);
        }
        if (digitalRead(button2) == HIGH) {
            i = button2;
            light(led2,500);
        }
        if (digitalRead(button3) == HIGH) {
            i = button3;
            light(led3,500);
        }
        if (i == buttonSequence[level]) {
            state = WIN;
        } else if (i == 0) {
                break;
            }
        state = LOSE;
        break;
    // tell player they succeeded and move on to next level
    case WIN: 
        lightPattern(2,2);
        lightPattern(0,3);
        level++;
    // tell player they lost and reset entire game
    case LOSE:
        lightPattern(2,2);
        lightPattern(1,3);
        level = 0;
    }
}

void light(char* led, int duration) {
    char* note;
        if (led0) {
            note = "NOTE_C3"; 
        }
        if (led1) {
            note = "NOTE_C4"; 
        }
        if (led2) {
            note = "NOTE_C5"; 
        }
        if (led3) {
            note = "NOTE_C6"; 
        }
    digitalWrite(led,HIGH);
    tone(8,note,duration);
    digitalWrite(led,LOW);
    return;
}

void lightPattern(int pattern, int reps) {
    if (pattern == 0) {
        for (int i = 0; i < reps * 4; i++) {
            light(led0,100);
            light(led1,100);
            light(led2,100);
            light(led3,100);
        }
    }
    if (pattern == 1) {
        for (int i = 0; i < reps * 4; i++) {
            light(led3,200);
            light(led2,200);
            light(led1,200);
            light(led0,200);
        } 
    }
    if (pattern == 2) {
        for (int i = 0; i < reps * 4; i ++) {
            light(led3,100);
            light(led0,100);
            light(led2,100);
            light(led1,100);
        }
    }
    return;
}

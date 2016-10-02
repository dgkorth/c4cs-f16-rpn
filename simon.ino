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
string buttonSequence[] = {button1,button3,button2,button0};
string ledSequence[] = {led1,led3,led2,led0};
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
}

void loop() {
    gameplay();
}

void gameplay() {
    // determine game state
    switch (state) {
    // tell player sequence to be entered
    case INSTRUCTION:
        for (int i = 0; i < level + 1; i++) {
            digitalWrite(ledSequence[i], HIGH);
            delay(500);
            digitalWrite(ledSequence[i], LOW);
        }
        state = PROMPT;
        break;
    // recieve input from player
    case PROMPT:
        int i = 0;
        if (digitalRead(button0) == HIGH) {
            i = button0;
        }
        if (digitalRead(button1) == HIGH) {
            i = button1;
        }
        if (digitalRead(button2) == HIGH) {
            i = button2;
        }
        if (digitalRead(button3) == HIGH) {
            i = button3;
        }
        if (i == buttonSequence[level]) {
            state = WIN;
        } else if {
            if (i == 0) {
                break;
            }
            state = LOSE;
            break;
        }
    // tell player they succeeded and move on to next level
    case WIN:
        // implement LED thing
        level++;
    // tell player they lost and reset entire game
    case LOSE:
        // implement sad LED thing
        level = 0;
    }
}


#include <Keypad.h>
int button = 10;
int ledPin = 13;
int speaker = 12;
int numberNotes = 8;
int notes[] = {0, 2, 4, 5, 7, 9, 11, 12};
int sound[] = {'C', 'D', 'E', 'F', 'G', 'A', 'B', 'H'};
char song[] = {'C', 'D', 'E', 'F', 'G', 'A', 'B', 'H'};
bool newSong = false;
bool songState = false;
int i = 0;

int ledState = HIGH;
int buttonState;
int lastState = LOW;

unsigned long lastTime = 0;
unsigned long debounceDelay = 50;
const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 7, 6}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
void setup() {
  pinMode(button, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(speaker, OUTPUT);
  noTone(speaker);
  Serial.begin(9600);


  digitalWrite(ledPin, ledState);
}

void loop() {


  int reading = digitalRead(button);


  if (reading != lastState) {

    lastTime = millis();
  }

  if ((millis() - lastTime) > debounceDelay) {

    if (reading != buttonState) {
      buttonState = reading;


      if (buttonState == HIGH) {
        ledState = !ledState;
        songState = !songState;
        
      }
    }
  }


  digitalWrite(ledPin, ledState);
 
  if (!songState) {
    if (i == numberNotes) {
      i = 0;
    }
    int tran = 0;
    for (int j = 0; j < 8; j++) {
      if (song[i] == sound[j]) {
        tran = j;
        break;
      }

    }
    double tmp = (261.2 * (pow(2.0, ((notes[tran]) / 12.0))));

    tone(speaker, tmp);
    i = i + 1;
    //if (songState) break;
    delay(tmp);


  } else {
    noTone(speaker);
    Serial.print(newSong);
    if (!newSong){
      for (int j = 0; j < 8; j++) {
        noTone(speaker);
        char key = keypad.getKey();
        bool check = false;
        while (!key) {
                  
          key = keypad.getKey();
        }
        if (key) {
          Serial.println(key);
          if (key == 49) {
            song[j] = 'C';
          }
          if (key == 50) {
            song[j] = 'D';
          }
          if (key == 51) {
            song[j] = 'E';
          }
          if (key == 52) {
            song[j] = 'F';
          }
          if (key == 53) {
            song[j] = 'G';
          }
          if (key == 54) {
            song[j] = 'A';
          }
          if (key == 55) {
            song[j] = 'B';
          }
          if (key == 56) {
            song[j] = 'H';

          }
        }
      }
      for (int j = 0; j < 8; j++) {
        Serial.print(song[j]);
      }
      i = 0;
      newSong = true;
    }
  }

  lastState = reading;
}

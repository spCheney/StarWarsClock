int PIN = 9;
int SevSeg[4][7];
const bool one[7] = {true, false, false, false, false, false, true};
const bool two[7] = {true, true, false, true, true, true, false};
const bool three[7] = {true, true, false, true, false, true, true};
const bool four[7] = {true, false, true, true, false, false, true};

double noteToFrequency(char note, int octave, bool sharp = false, bool flat = false) {

  int noteNum;
  int actualOctave;
  int octNoteNum;

  switch (note) {
    case 'A':
      octNoteNum = 10;
      break;
    case 'B':
      octNoteNum = 12;
      break;
    case 'C':
      octNoteNum = 1;
      break;
    case 'D':
      octNoteNum = 3;
      break;
    case 'E':
      octNoteNum = 5;
      break;
    case 'F':
      octNoteNum = 6;
      break;
    case 'G':
      octNoteNum = 8;
      break;
  }

  if (sharp) {
    octNoteNum++;
  }
  else if (flat) {
    octNoteNum--;
  }

  if (octNoteNum > 13) {
    actualOctave = octave + 1;
    octNoteNum -= 12;
  }
  else if (octNoteNum < 1) {
    actualOctave = octave - 1;
    octNoteNum += 12;
  }
  else {
    actualOctave = octave;
  }

  noteNum = (((actualOctave - 1) * 12) + 3 + octNoteNum);

  return ((pow(1.059463, (noteNum - 49))) * 440);
}

int beatToTime(int bpm, double noteType, bool dotted = false) {
  int milSecBetweenBeats = (60000 / bpm);
  int delayTime;
  int dottedTime;

  if (noteType == (1.0 / 1.0)) {
    delayTime = milSecBetweenBeats * 4;
  }
  else if (noteType == (1.0 / 2.0)) {
    delayTime = milSecBetweenBeats * 2;
  }
  else if (noteType == (1.0 / 4.0)) {
    delayTime = milSecBetweenBeats;
  }
  else if (noteType == (1.0 / 8.0)) {
    delayTime = milSecBetweenBeats / 2;
  }
  else if (noteType == (1.0 / 16.0)) {
    delayTime = milSecBetweenBeats / 4;
  }
  else if (noteType == (1.0 / 32.0)) {
    delayTime = milSecBetweenBeats / 8;
  }
  else {
    delayTime = 0;
  }

  if (dotted) {
    dottedTime = delayTime / 2;
  }
  else {
    dottedTime = 0;
  }

  return delayTime + dottedTime;
}

void playStarWars() {
  int bpm = 80;
  tone(PIN, noteToFrequency('G', 3), beatToTime(bpm, 1.0 / 4.0));
  delay(beatToTime(bpm, 1.0 / 4.0));
  noTone(PIN);
  tone(PIN, noteToFrequency('G', 3), beatToTime(bpm, 1.0 / 4.0));
  delay(beatToTime(bpm, 1.0 / 4.0));
  noTone(PIN);
  tone(PIN, noteToFrequency('G', 3), beatToTime(bpm, 1.0 / 4.0));
  delay(beatToTime(bpm, 1.0 / 4.0));
  noTone(PIN);
  tone(PIN, noteToFrequency('E', 3, false, true), beatToTime(bpm, 1.0 / 8.0, true));
  delay(beatToTime(bpm, 1.0 / 8.0, true));
  noTone(PIN);
  tone(PIN, noteToFrequency('B', 3, false, true), beatToTime(bpm, 1.0 / 16.0));
  delay(beatToTime(bpm, 1.0 / 16.0));
  noTone(PIN);

  tone(PIN, noteToFrequency('G', 3), beatToTime(bpm, 1.0 / 4.0));
  delay(beatToTime(bpm, 1.0 / 4.0));
  noTone(PIN);
  tone(PIN, noteToFrequency('E', 3, false, true), beatToTime(bpm, 1.0 / 8.0, true));
  delay(beatToTime(bpm, 1.0 / 8.0, true));
  noTone(PIN);
  tone(PIN, noteToFrequency('B', 3, false, true), beatToTime(bpm, 1.0 / 16.0));
  delay(beatToTime(bpm, 1.0 / 16.0));
  noTone(PIN);
  tone(PIN, noteToFrequency('G', 3), beatToTime(bpm, 1.0 / 2.0));
  delay(beatToTime(bpm, 1.0 / 2.0));
  noTone(PIN);

  tone(PIN, noteToFrequency('D', 4), beatToTime(bpm, 1.0 / 4.0));
  delay(beatToTime(bpm, 1.0 / 4.0));
  noTone(PIN);
  tone(PIN, noteToFrequency('D', 4), beatToTime(bpm, 1.0 / 4.0));
  delay(beatToTime(bpm, 1.0 / 4.0));
  noTone(PIN);
  tone(PIN, noteToFrequency('D', 4), beatToTime(bpm, 1.0 / 4.0));
  delay(beatToTime(bpm, 1.0 / 4.0));
  noTone(PIN);
  tone(PIN, noteToFrequency('E', 4, false, true), beatToTime(bpm, 1.0 / 8.0, true));
  delay(beatToTime(bpm, 1.0 / 8.0, true));
  noTone(PIN);
  tone(PIN, noteToFrequency('B', 3, false, true), beatToTime(bpm, 1.0 / 16.0));
  delay(beatToTime(bpm, 1.0 / 16.0));
  noTone(PIN);

  tone(PIN, noteToFrequency('G', 3, false, true), beatToTime(bpm, 1.0 / 4.0));
  delay(beatToTime(bpm, 1.0 / 4.0));
  noTone(PIN);
  tone(PIN, noteToFrequency('E', 3, false, true), beatToTime(bpm, 1.0 / 8.0, true));
  delay(beatToTime(bpm, 1.0 / 8.0, true));
  noTone(PIN);
  tone(PIN, noteToFrequency('B', 3, false, true), beatToTime(bpm, 1.0 / 16.0));
  delay(beatToTime(bpm, 1.0 / 16.0));
  noTone(PIN);
  tone(PIN, noteToFrequency('G', 3), beatToTime(bpm, 1.0 / 2.0));
  delay(beatToTime(bpm, 1.0 / 2.0));
  noTone(PIN);

  tone(PIN, noteToFrequency('G', 4), beatToTime(bpm, 1.0 / 4.0));
  delay(beatToTime(bpm, 1.0 / 4.0));
  noTone(PIN);
  tone(PIN, noteToFrequency('G', 3), beatToTime(bpm, 1.0 / 8.0, true));
  delay(beatToTime(bpm, 1.0 / 8.0, true));
  noTone(PIN);
  tone(PIN, noteToFrequency('G', 3), beatToTime(bpm, 1.0 / 16.0));
  delay(beatToTime(bpm, 1.0 / 16.0));
  noTone(PIN);
  tone(PIN, noteToFrequency('G', 4), beatToTime(bpm, 1.0 / 4.0));
  delay(beatToTime(bpm, 1.0 / 4.0));
  noTone(PIN);
  tone(PIN, noteToFrequency('G', 4, false, true), beatToTime(bpm, 1.0 / 8.0, true));
  delay(beatToTime(bpm, 1.0 / 8.0, true));
  noTone(PIN);
  tone(PIN, noteToFrequency('F', 4), beatToTime(bpm, 1.0 / 16.0));
  delay(beatToTime(bpm, 1.0 / 16.0));
  noTone(PIN);

  tone(PIN, noteToFrequency('E', 4), beatToTime(bpm, 1.0 / 16.0));
  delay(beatToTime(bpm, 1.0 / 16.0));
  noTone(PIN);
  tone(PIN, noteToFrequency('D', 4, true), beatToTime(bpm, 1.0 / 16.0));
  delay(beatToTime(bpm, 1.0 / 16.0));
  noTone(PIN);
  tone(PIN, noteToFrequency('E', 4), beatToTime(bpm, 1.0 / 8.0));
  delay(beatToTime(bpm, 1.0 / 8.0) * 3);                                          //rest
  noTone(PIN);
  tone(PIN, noteToFrequency('G', 3, true), beatToTime(bpm, 1.0 / 8.0));
  delay(beatToTime(bpm, 1.0 / 8.0));
  noTone(PIN);
  tone(PIN, noteToFrequency('C', 4, true), beatToTime(bpm, 1.0 / 4.0));
  delay(beatToTime(bpm, 1.0 / 4.0));
  noTone(PIN);
  tone(PIN, noteToFrequency('B', 4, true), beatToTime(bpm, 1.0 / 8.0, true));
  delay(beatToTime(bpm, 1.0 / 8.0, true));
  noTone(PIN);
  tone(PIN, noteToFrequency('B', 4), beatToTime(bpm, 1.0 / 16.0));
  delay(beatToTime(bpm, 1.0 / 16.0));
  noTone(PIN);

  tone(PIN, noteToFrequency('B', 3, false, true), beatToTime(bpm, 1.0 / 16.0));
  delay(beatToTime(bpm, 1.0 / 16.0));
  noTone(PIN);
  tone(PIN, noteToFrequency('A', 3), beatToTime(bpm, 1.0 / 16.0));
  delay(beatToTime(bpm, 1.0 / 16.0));
  noTone(PIN);
  tone(PIN, noteToFrequency('B', 3, false, true), beatToTime(bpm, 1.0 / 8.0));
  delay(beatToTime(bpm, 1.0 / 8.0) * 3);                                              //rest
  noTone(PIN);
  tone(PIN, noteToFrequency('E', 3, false, true), beatToTime(bpm, 1.0 / 8.0));
  delay(beatToTime(bpm, 1.0 / 8.0));
  noTone(PIN);
  tone(PIN, noteToFrequency('G', 3, false, true), beatToTime(bpm, 1.0 / 4.0));
  delay(beatToTime(bpm, 1.0 / 4.0));
  noTone(PIN);
  tone(PIN, noteToFrequency('E', 3, false, true), beatToTime(bpm, 1.0 / 8.0, true));
  delay(beatToTime(bpm, 1.0 / 8.0, true));
  noTone(PIN);
  tone(PIN, noteToFrequency('B', 3, false, true), beatToTime(bpm, 1.0 / 16.0));
  delay(beatToTime(bpm, 1.0 / 16.0));
  noTone(PIN);

  tone(PIN, noteToFrequency('B', 3, false, true), beatToTime(bpm, 1.0 / 4.0));
  delay(beatToTime(bpm, 1.0 / 4.0));
  noTone(PIN);
  tone(PIN, noteToFrequency('G', 3), beatToTime(bpm, 1.0 / 8.0, true));
  delay(beatToTime(bpm, 1.0 / 8.0, true));
  noTone(PIN);
  tone(PIN, noteToFrequency('B', 3, false, true), beatToTime(bpm, 1.0 / 16.0));
  delay(beatToTime(bpm, 1.0 / 16.0));
  noTone(PIN);
  tone(PIN, noteToFrequency('D', 3), beatToTime(bpm, 1.0 / 2.0));
  delay(beatToTime(bpm, 1.0 / 2.0));
  noTone(PIN);

  tone(PIN, noteToFrequency('E', 4), beatToTime(bpm, 1.0 / 16.0));
  delay(beatToTime(bpm, 1.0 / 16.0));
  noTone(PIN);
  tone(PIN, noteToFrequency('D', 4, true), beatToTime(bpm, 1.0 / 16.0));
  delay(beatToTime(bpm, 1.0 / 16.0));
  noTone(PIN);
  tone(PIN, noteToFrequency('E', 4), beatToTime(bpm, 1.0 / 8.0));
  delay(beatToTime(bpm, 1.0 / 8.0) * 3);                                          //rest
  noTone(PIN);
  tone(PIN, noteToFrequency('G', 3, true), beatToTime(bpm, 1.0 / 8.0));
  delay(beatToTime(bpm, 1.0 / 8.0));
  noTone(PIN);
  tone(PIN, noteToFrequency('C', 4, true), beatToTime(bpm, 1.0 / 4.0));
  delay(beatToTime(bpm, 1.0 / 4.0));
  noTone(PIN);
  tone(PIN, noteToFrequency('B', 4, true), beatToTime(bpm, 1.0 / 8.0, true));
  delay(beatToTime(bpm, 1.0 / 8.0, true));
  noTone(PIN);
  tone(PIN, noteToFrequency('B', 4), beatToTime(bpm, 1.0 / 16.0));
  delay(beatToTime(bpm, 1.0 / 16.0));
  noTone(PIN);

  tone(PIN, noteToFrequency('B', 3, false, true), beatToTime(bpm, 1.0 / 16.0));
  delay(beatToTime(bpm, 1.0 / 16.0));
  noTone(PIN);
  tone(PIN, noteToFrequency('A', 3), beatToTime(bpm, 1.0 / 16.0));
  delay(beatToTime(bpm, 1.0 / 16.0));
  noTone(PIN);
  tone(PIN, noteToFrequency('B', 3, false, true), beatToTime(bpm, 1.0 / 8.0));
  delay(beatToTime(bpm, 1.0 / 8.0) * 3);                                        //rest
  noTone(PIN);
  tone(PIN, noteToFrequency('E', 3, false, true), beatToTime(bpm, 1.0 / 8.0));
  delay(beatToTime(bpm, 1.0 / 8.0));
  noTone(PIN);
  tone(PIN, noteToFrequency('G', 3, false, true), beatToTime(bpm, 1.0 / 4.0));
  delay(beatToTime(bpm, 1.0 / 4.0));
  noTone(PIN);
  tone(PIN, noteToFrequency('E', 3, false, true), beatToTime(bpm, 1.0 / 8.0, true));
  delay(beatToTime(bpm, 1.0 / 8.0, true));
  noTone(PIN);
  tone(PIN, noteToFrequency('B', 3, false, true), beatToTime(bpm, 1.0 / 16.0));
  delay(beatToTime(bpm, 1.0 / 16.0));
  noTone(PIN);

  tone(PIN, noteToFrequency('G', 3), beatToTime(bpm, 1.0 / 4.0));
  delay(beatToTime(bpm, 1.0 / 4.0));
  noTone(PIN);
  tone(PIN, noteToFrequency('E', 3, false, true), beatToTime(bpm, 1.0 / 8.0, true));
  delay(beatToTime(bpm, 1.0 / 8.0, true));
  noTone(PIN);
  tone(PIN, noteToFrequency('B', 3, false, true), beatToTime(bpm, 1.0 / 16.0));
  delay(beatToTime(bpm, 1.0 / 16.0));
  noTone(PIN);
  tone(PIN, noteToFrequency('G', 3), beatToTime(bpm, 1.0 / 2.0));
  delay(beatToTime(bpm, 1.0 / 2.0));
  noTone(PIN);

  return;
}


void TurnOn(bool sym[], int digit) {
    for(int i = 0;i < 7;i++){
        if(sym[i]) {
            digitalWrite(SevSeg[digit][i], LOW);
        }
        else {
            digitalWrite(SevSeg[digit][i], HIGH);
        }
    }
}

void SevSegOutput(String message) {
    for(int i = 0;i < 4;i++){
        switch (message.charAt(i)) {
            case '1':
                TurnOn(one, i);
                break;
            case '2':
                TurnOn(two, i);
                break;
            case '3':
                TurnOn(three, i);
                break;
            case '4':
                TurnOn(four, i);
                break;
        }
    }
}


void setup() {
    pinMode(PIN, OUTPUT);
    int pinSetup = 53;
    pinMode(PIN, OUTPUT);

    for(int r = 0;r < 4;r++){
        for(int c = 0;c < 7;c++){
            SevSeg[r][c] = pinSetup;
            pinSetup--;
            pinMode(SevSeg[r][c], OUTPUT);
            digitalWrite(SevSeg[r][c], HIGH);
        }
        pinSetup--;
    }

    SevSegOutput("1234");
    // playStarWars();
}

void loop() {
    
}

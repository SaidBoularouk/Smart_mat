
int oldSajda = -1, oldRaqa = -1, oldMax = -1;
int raqa = 0, sajda = 0, maxraqa = 0,  counter = 0;
long oldtheTime = -1;
bool isSajda = false, oldIsSajda, isRaqa , oldIsRaqa;

unsigned long startTime, endTime, _theTime = 0, rTime, theTime;
unsigned long timesajda;
int _time = 0;
// set pin numbers
const int touchPin = 4;
// change with your threshold value
const int threshold = 40;
// variable for storing the touch pin value
int touchValue = 0;

int _detectedValue = 0;
int _olddetectedValue = 0;



bool detectSajda() {

  touchValue = touchRead(touchPin);
  timesajda = 0;
  if (touchValue < threshold) {
    _detectedValue = 1;
    if (_detectedValue == 1 && _olddetectedValue == 0) {
      _olddetectedValue = _detectedValue;
      _theTime = millis();
    }
    theTime = millis() - _theTime;

    if (theTime > 3000 ) {
      isSajda = true;
      oldIsSajda = true;
    }
  }

  if (touchValue > threshold) {
    _detectedValue = 0;
    _olddetectedValue = 0;
    oldIsSajda = false;
  }

  return isSajda;
}



void countSajda() {
  if (detectSajda() == true && oldIsSajda == false) {
    sajda = sajda + 1;
    counter = counter + 1;
    timesajda = int((millis() - _theTime) / 1000);
    oldIsSajda = true;
    oldIsRaqa = false;
    isSajda = false;
  } else {
    sajda = sajda;
  }


}

void countRaqa() {
  if (sajda == 2) {
    isRaqa = true;
    if (isRaqa == true && oldIsRaqa == false) {
      raqa = raqa + 1;
      rTime = millis();
      oldIsRaqa = true;
    }
  } else {
    isRaqa = false;
  }

}

void reset() {
  if ( sajda >= 2) {
    long currentTime = millis();
    if (currentTime - rTime >= 5000) {
      sajda = 0;
    }
  }

  if (raqa >= maxraqa && sajda == 0) {
    long currentTime = millis();
    if (currentTime - rTime >= 10000) {
      raqa = maxraqa;
      sajda = raqa * 2;
    }

  }

}


void initialize() {
  raqa = 0;
  sajda = 0;
  timesajda = 0;
  maxraqa = 0;
  counter = 0;

  oldtheTime = 0;
  oldRaqa = 0;
  oldSajda = 0;
  oldMax = 0;

}

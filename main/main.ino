int trigPin = 9;
int echoPin = 10;
int detect = 10; //cm

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

bool isSafeClosed() {
  long duration, distance;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  if (distance <= detect) {
    return true;
  } else {
    return false;
  }
}

//이 밑의 코드는 5초 이상 닫힘 감지시 닫히는 코드
const int trigPin = 9; // replace with your actual trigPin
const int echoPin = 10; // replace with your actual echoPin
const int detect = 10; // replace with your desired detection distance in cm
const unsigned long closeDuration = 5000; // replace with your desired close duration in milliseconds

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  long duration, distance;
  static unsigned long startTime = 0;
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.println(distance);

  if (distance <= detect) { // cm 이하 감지
    if (startTime == 0) {
      startTime = millis(); // capture the start time
    } else {
      unsigned long elapsedTime = millis() - startTime;
      if (elapsedTime >= closeDuration) {
        Serial.println("가나다라");
        startTime = 0; // reset the start time
      }
    }
  } else {
    startTime = 0; // reset the start time if distance is greater than detect
  }

  delay(1000);
}

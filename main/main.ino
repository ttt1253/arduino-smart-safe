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

//이 밑의 코드는 5초 이상 닫힘 감지시 닫히는 코드
int closeDuration = 5000; 

void loop() {
  long duration, distance;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  if (distance <= closeThreshold) { //cm 이하 감지
    static unsigned long startTime = 0;
    if (millis() - startTime >= closeDuration) {
      // 문을 닫는 코드
      startTime = 0;
    } else {
      if (startTime == 0) {
        startTime = millis();
      }
    }
  } else {
    startTime = 0;
  }
  delay(1000);
}

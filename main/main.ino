#include <LiquidCrystal.h>
#include <Servo.h>

enum Status {
  CLOSED,       // 금고가 잠긴 상태
  OPEN,         // 금고가 열린 상태
  RESET,        // 비밀번호 초기화
};

// 비동기 딜레이를 위한 타이머
class Timer {
public:
  Timer() {}
  Timer(int millis) {
    period = millis;
  }

  bool isPassed() {
    int currentTime = millis();
    return currentTime - prevTime >= period;
  }

  void reset() { prevTime = millis(); }

private:
  int prevTime;
  int period;
};

// ############## 금고 변수 ###################
int password[] = {0, 0, 0, 0};
int set_password[] = {0, 0, 0, 0};
int cntWrongPassword = 0;
Status status = CLOSED;
// ###########################################

// ##############  핀 정의  ###################
int pinDoorlock = 11;
int okbuttonPin = 2;
int resetbuttonPin = 3;
int potenpin[] = {A0, A1, A2, A3}; // 가변저항 핀
// ##########################################

// ############## 타이머 #####################
Timer timDebug(1000);
// ##########################################

Servo doorLock;
LiquidCrystal lcd(44, 45, 46, 47, 48, 49); //LCD 연결

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < 4; i++) {
    pinMode(potenpin[i], INPUT);
  }
  lcd.begin(16,2);
  doorLock.attach(pinDoorlock);
  lockSafe();

  pinMode(okbuttonPin, INPUT);
  pinMode(resetbuttonPin, INPUT);
  Serial.begin(9600);

  // 타이머 정의
  timDebug = Timer(1000);
}


void loop() {
  run(status);
}

void run(Status status) {
  switch (status) {
    case OPEN:
      break;
    case CLOSED:
      readPassword();
      displayPassword();
      if (isOKButtonPressed()){
        if (isCorrectPassword()) {
          unlockSafe();
        }
        else if(cntWrongPassword == 5) warning();
        delay(100); // 디버깅
      }
      break;
    case RESET:
      break;
    default:
      break;
  }
}


void displayPassword(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Enter Password");
  lcd.setCursor(0,1);
  for(int i=0; i<4; i++){
    lcd.print("[");
    lcd.print(password[i]);
    lcd.print("]");
  }
  
  // 1초마다 디버깅
  if (timDebug.isPassed()) {
    for (int i=0; i<4; i++) Serial.print(password[i]);
    Serial.println();
    timDebug.reset();
  }
}

void displayjudgePassword(){
  lcd.clear();
  if(isCorrectPassword()){  // 비밀번호 일치 시 화면 출력
    lcd.setCursor(0,0);
    lcd.print("Correct Password");
    lcd.setCursor(0,1);
    lcd.print("Open the door");
    delay(2000);
  }else{ // 비밀번호 틀릴 시 화면 출력
    lcd.setCursor(0,0);
    lcd.print("Wrong Password");
    lcd.setCursor(0,1);
    lcd.print("Wrong "); // 틀린 횟수 출력
    lcd.print(cntWrongPassword);
    lcd.print(" time(s)");
    delay(2000);
  }
}

void readPassword() {
  for (int i = 0; i < 4; i++) {
    int readpin = analogRead(potenpin[i]); // 가변저항 값 읽기
    password[i] = map(readpin, 0, 1023, 0, 9); // 가변저항 값 대입
  }
}

void warning(){ // 5회 틀릴 시 오류메시지 표시
  for(int s; s<10; s++){
    lcd.setCursor(0,0);
    lcd.print("Warning");
    lcd.setCursor(0,1);
    lcd.print("Try again after "); // 틀린 횟수 출력
    lcd.print("s");
    lcd.print("seconds");
    delay(1000);
    cntWrongPassword = 0;
  }
}

bool isOKButtonPressed() {
  return digitalRead(okbuttonPin) == HIGH;
}

bool isCorrectPassword() {
  for (int i = 0; i < 4; i++) {
    if (set_password[i] != password[i]) {
      cntWrongPassword++;
      return false;
    }
  }
  return true;
}

bool resetButtonPressed() {
  return digitalRead(resetbuttonPin) == HIGH;
}

void readresetPassword() {
  for (int i = 0; i < 4; i++) {
    int readpin = analogRead(potenpin[i]); // 가변저항 값 읽기
    set_password[i] = map(readpin, 0, 1023, 0, 9); // 가변저항 값 대입
  }
}

void lockSafe() { doorLock.write(90); }
void unlockSafe() { doorLock.write(0); }
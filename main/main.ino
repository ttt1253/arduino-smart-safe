#include <LiquidCrystal.h>
#include <Servo.h>

enum Status {
  CLOSED,
  OPEN,
};

int password[] = {0, 0, 0, 0};
int set_password[] = {0, 0, 0, 0};
int cntWrongPassword = 0;

int isopen = 1;

// ##############  핀 정의  ###################
int pinDoorlock = 11;
int okbuttonPin = 2;
int resetbuttonPin = 3;
int potenpin[] = {A0, A1, A2, A3}; // 가변저항 핀
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
}


void loop() {
  // 1. 사용자의 비밀번호 확인
  readPassword();

  // 2. LCD에 표시
  displayPassword();

  // 3. 버튼이 눌리면 비밀번호가 맞는지 확인한다.
  if (isOKButtonPressed()){
    if (isCorrectPassword()) {
      unlockSafe();
    }
    delay(100); // 디버깅
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

    Serial.print(password[i]);
  }
  
  Serial.println();
  delay(1000);
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
#include <LiquidCrystal.h>

int password[] = {0, 0, 0, 0};
int WrongCount = 0;
int potenpin[] = {A0, A1, A2, A3}; // 가변저항 핀
int set_password[] = {0, 0, 0, 0};
LiquidCrystal lcd(44, 45, 46, 47, 48, 49); //LCD 연결

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < 4; i++) {
    pinMode(potenpin[i], INPUT);
  }
  lcd.begin(16,2);

}

void loop() {
  // 1. 사용자의 비밀번호 확인
  readPassword();

  // 2. LCD에 표시
  displayPassword();

  // 3. 버튼이 눌리면 비밀번호가 맞는지 확인한다.
  if (isCorrectPassword()) {
    lockSafe();
  } else {
    unlockSafe();
  }
}

void displayPassword(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Enter Password");
  lcd.setCursor(0,1);
  for(int i=0; i<4; i++){
    lcd.print("[ ");
    lcd.print(password[i]);
    lcd.print(" ]");
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
    lcd.print(WrongCount);
    lcd.print(" time(s)");
    delay(2000);
  }
}
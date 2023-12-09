int password[] = {0, 0, 0, 0};
int numWrongPassword = 0;
int potenpin[] = {A0, A1, A2, A3}; // 가변저항 핀
int set_password[] = {0, 0, 0, 0};

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < 4; i++) {
    pinMode(potenpin[i], INPUT);
  }

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


void readPassword() {
  for (int i = 0; i < 4; i++) {
    int readpin = analogRead(potenpin[i]); // 가변저항 값 읽기
    password[i] = map(readpin, 0, 1023, 0, 9); // 가변저항 값 대입
  }
}

bool isCorrectPassword() {
  for (int i = 0; i < 4; i++) {
    if (set_password[i] != password[i]) {
      return false;
    }
  }
  return true;
}
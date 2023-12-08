int password[] = {0, 0, 0, 0};
int numWrongPassword = 0;

void setup() {
  // put your setup code here, to run once:

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

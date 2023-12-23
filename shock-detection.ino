int shockPin  = A4;

void setup() {
}

void loop() {
  int shock = analogRead(shockPin);
   if(shock>512){
    displayShock();
   }
   delay(1000);
}

void displayShock(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("SHOCK DETECTION!");
}
String CurrentButton;
void InitAccelerometer(){
  TFTscreen.background(0, 0, 0);
  CurrentButton = "";
}

void LoopAccelerometer(){
  HandleKeyInputAccelerometer();
  drawAccelerometer();
  if(Modus != 9){
    TFTscreen.background(0, 0, 0);
  }
}

void drawAccelerometer(){
  lis.read(); 
  setColor(0, 0, 0);
  TFTscreen.rect(30, 25, 75, 75);
  TFTscreen.setTextSize(2);
  setColor(255, 255, 255);
  sensors_event_t event; 
  lis.getEvent(&event);
  for(int i = 0; i < 3; i++){
    String accelText = "";
    switch(i){
      case 0:
        accelText += "X: ";
        accelText += event.acceleration.x;
      break;
      case 1:
        accelText += "Y: ";
        accelText += event.acceleration.y;
      break;
      case 2:
        accelText += "Z: ";
        accelText += event.acceleration.z;
      break;
    }
    char accelBuff[64];
    accelText.toCharArray(accelBuff, 64);
    TFTscreen.text(accelBuff, 10, 25+(25*i));
    CurrentButton.toCharArray(accelBuff, 64);
    TFTscreen.text(accelBuff, 10, 100);
  }
}

void HandleKeyInputAccelerometer() {
  if (digitalRead(l2) == LOW) {
    GameSpeed = 100;
    CurrentButton = "L2";
    Modus = 1;
  }
  if (digitalRead(r2) == LOW) {
    CurrentButton = "R2";
    setColor(0, 0, 0);
    TFTscreen.rect(10, 100, 75, 28);
  }
  if (digitalRead(t2) == LOW) {
    CurrentButton = "T2";
    setColor(0, 0, 0);
    TFTscreen.rect(10, 100, 75, 28);
  }
  if (digitalRead(b2) == LOW) {
    CurrentButton = "B2";
    setColor(0, 0, 0);
    TFTscreen.rect(10, 100, 75, 28);
  }
  if (digitalRead(l1) == LOW) {
    CurrentButton = "L1";
    setColor(0, 0, 0);
    TFTscreen.rect(10, 100, 75, 28);
  }
  if (digitalRead(r1) == LOW) {
    CurrentButton = "R1";
    setColor(0, 0, 0);
    TFTscreen.rect(10, 100, 75, 28);
  }
  if (digitalRead(t1) == LOW) {
    CurrentButton = "T1";
    setColor(0, 0, 0);
    TFTscreen.rect(10, 100, 75, 28);
  }
  if (digitalRead(b1) == LOW) {
    CurrentButton = "B1";
    setColor(0, 0, 0);
    TFTscreen.rect(10, 100, 75, 28);
  }
}

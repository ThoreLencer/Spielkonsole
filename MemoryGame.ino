int8_t clicks, mem[50], guessindex, timer;
bool guess, drawmem[4], error, keys[4];
void InitMemory() {
  GameSpeed = 20;
  TFTscreen.background(0, 0, 0);
  DrawMemory();
  clicks = 0;
  guessindex = 0;
  guess = false;
  for(int8_t i = 0; i < 4; i++){
    drawmem[i] = false;
    keys[i] = false;
  }
  error = false;
  enableInput = true;
  timer = 0;
}
void LoopMemory() {
  if (error == true) {
     setColor(255, 0, 0);
     TFTscreen.setTextSize(2);
     TFTscreen.text("Game over!", 20, 50);
     String scoreText = "";
     scoreText += "Score: ";
     scoreText += clicks;
     char scoreBuff[64];
     scoreText.toCharArray(scoreBuff, 64);
     TFTscreen.setTextSize(1);
     setColor(255, 255, 255);
     TFTscreen.text(scoreBuff, 60, 80);
     HandleKeyInputMemory();
  } else {
  if (guess == true) {
    HandleKeyInputMemory();
      if (error == true) 
       TFTscreen.background(0, 0, 0);
      if(!error) {
        if (guessindex == clicks) {
          guess = false;
      }
    }
    if(enableInput == false){
      timer++;
      if (timer == 15){
        timer = 0;
        DrawMemory();
        enableInput = true;
      }
    }
    delay(GameSpeed);
    if(guess == false){
      DrawMemory();
      delay(600);
    }
  } else {
    //Rand Memory
    mem[clicks] = random(1, 5);
    for (int8_t i = 0; i < clicks + 1; i++) {
      DrawMemory();
      delay(300);
      drawmem[mem[i] - 1] = true;
      DrawMemory();
      delay(600);
    }
    DrawMemory();
    clicks++;
    guess = true;
    guessindex = 0;
  }
  if (Modus != 8)
    TFTscreen.background(0, 0, 0);
  }
}

void DrawMemory() {
  TFTscreen.fill(255, 255, 255);
  TFTscreen.stroke(255, 255, 255);
  if (drawmem[0] == true)
    TFTscreen.fill(255, 0, 0);
  TFTscreen.rect(65, 19, 30, 30);
  TFTscreen.fill(255, 255, 255);
  if (drawmem[1] == true)
    TFTscreen.fill(0, 255, 0);
  TFTscreen.rect(30, 49, 30, 30);
  TFTscreen.fill(255, 255, 255);
  if (drawmem[2] == true)
    TFTscreen.fill(0, 255, 255);
  TFTscreen.rect(100, 49, 30, 30);
  TFTscreen.fill(255, 255, 255);
  if (drawmem[3] == true)
    TFTscreen.fill(0, 0, 255);
  TFTscreen.rect(65, 78, 30, 30);
  String scoreText = "";
  scoreText += "Score: ";
  scoreText += clicks;
  char scoreBuff[64];
  scoreText.toCharArray(scoreBuff, 64);
  TFTscreen.setTextSize(1);
  TFTscreen.fill(0, 0, 0);
  TFTscreen.stroke(0, 0, 0);
  TFTscreen.rect(10, 110, 100, 18);
  setColor(255, 255, 255);
  TFTscreen.text(scoreBuff, 10, 118);
  for(int8_t i = 0; i < 4; i++){
    drawmem[i] = false;
  }
}

void HandleKeyInputMemory() {
  if (digitalRead(l2) == LOW) {
    GameSpeed = 100;
    TFTscreen.background(0, 0, 0);
    Modus = 1;
  }
  if (digitalRead(l1) == LOW) { //LEFT
    if(enableInput){
      enableInput = false;
      keys[1] = true;
      drawmem[1] = true;
      DrawMemory();
    }
  } else {
    if (keys[1] == true) {
      keys[1] = false;
      if (mem[guessindex] != 2)
        error = true;
      guessindex ++;
    }
  }
  if (digitalRead(r1) == LOW) { //RIGHT
    if(enableInput){
      enableInput = false;
      keys[2] = true;
      drawmem[2] = true;
      DrawMemory();
    }
  } else {
    if (keys[2] == true) {
      keys[2] = false;
      if (mem[guessindex] != 3)
        error = true;
      guessindex ++;
    }
  }
  if (digitalRead(b1) == LOW) { //DOWN
    if(enableInput){
      enableInput = false;
      keys[3] = true;
      drawmem[3] = true;
      DrawMemory();
    }
  } else {
    if (keys[3] == true) {
      keys[3] = false;
      if (mem[guessindex] != 4)
        error = true;
      guessindex ++;
    }
  }
  if (digitalRead(t1) == LOW) { //UP
    if(enableInput){
      enableInput = false;
      keys[0] = true;
      drawmem[0] = true;
      DrawMemory();
    }
  } else {
    if (keys[0] == true) {
      keys[0] = false;
      if (mem[guessindex] != 1)
        error = true;
      guessindex ++;
    }
  }
}

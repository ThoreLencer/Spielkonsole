int16_t xpos, ypos, jumpspeed, jumpScore;
bool jump;
void InitJump() {
  GameSpeed = 15;
  enableInput = true;
  jump = false;
  jumpspeed = 2;
  jumpScore = 0;
  TFTscreen.background(0, 0, 0);
  xpos = 150;
  ypos = 108;
}
void LoopJump() {
  HandleKeyInputJump();
  if (jumpScore >= 0) {
    DrawJump();
    CollisionJump();
    if (xpos - jumpspeed > 0) {
      xpos -= jumpspeed;
    } else {
      xpos = 150;
      jumpScore++;
      setColor(0, 0, 0);
      TFTscreen.rect(45, 0, 50, 18);
      if(jumpScore % 10 == 0){
        jumpspeed++;
      }
      setColor(0, 0, 0);
      TFTscreen.rect(0, 108, 20, 20);
    }
    if ((jump == false) && (ypos < 108))
      ypos += jumpspeed - 1;
    if ((jump == true) && (ypos > 75))
      ypos -= 2 * (jumpspeed - 1);
    if ((jump == true) && (ypos <= 75))
      jump = false;
    if (ypos >= 100)
      enableInput = true;
  }
    if (Modus != 7)
      TFTscreen.background(0, 0, 0);
}

void CollisionJump() {
  if (ypos > 88) {
    if (xpos > 10 && xpos < 20) {
      //Collision
      jumpScore = -1;
      setColor(255, 0, 0);
      TFTscreen.setTextSize(2);
      TFTscreen.text("Game over!", 20, 50);
    }
  }
}

void DrawJump() {
  setColor(0, 255, 0);
  TFTscreen.rect(xpos, 108, 10, 20);
  setColor(0, 0, 0);
  TFTscreen.rect(xpos + 10, 105, 20, 23);
  TFTscreen.rect(xpos - 30, 105, 20, 23);

  setColor(0, 0, 255);
  TFTscreen.rect(10, ypos, 10, 20);
  if(xpos > 20){
  setColor(0, 0, 0);
  TFTscreen.rect(10, ypos - 20, 10, 20);
  TFTscreen.rect(10, ypos + 30, 10, 10);
  }
  String scoreText = "";
  scoreText += "Score: ";
  scoreText += jumpScore;
  char scoreBuff[64];
  scoreText.toCharArray(scoreBuff, 64);
  TFTscreen.setTextSize(1);
  setColor(255, 255, 255);
  TFTscreen.text(scoreBuff, 10, 0);
}

void HandleKeyInputJump() {
  if (digitalRead(l2) == LOW) {
    GameSpeed = 100;
    Modus = 1;
  }
  if (enableInput) {
    if (digitalRead(l1) == LOW) { //LEFT

    } else if (digitalRead(r1) == LOW) { //RIGHT

    } else if (digitalRead(b1) == LOW) { //DOWN

    } else if (digitalRead(t1) == LOW) { //UP
      enableInput = false;
      jump = true;
      setColor(0, 0, 0);
      TFTscreen.rect(10, 100, 10, 28);
    }
  }
}

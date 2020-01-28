struct SnakeBody {
  int16_t x;
  int16_t y;
};

SnakeBody Snake[100] = {};
int16_t Timer, Richtung, CoinX, CoinY, Score, SnakeLength;

void SnakeInit() {
  GameSpeed = 80;
  for (int16_t i = 0; i < 100; i++) {
    Snake[i].x = 161;
    Snake[i].y = 129;
  }
  Timer = 0;
  CoinX = random(0, 15);
  CoinY = random(0, 11);
  Richtung = 1;
  Score = 0;
  SnakeLength = 1;
  TFTscreen.background(0, 0, 0);
  Snake[0].x = 80;
  Snake[0].y = 60;
}

void SnakeDraw() {
  if (Snake[0].x != -10) {
    setColor(0, 0, 255);
    TFTscreen.stroke(0, 0, 84);
    TFTscreen.rect(CoinX * 10, CoinY * 10, 10, 10);
    for (int16_t i = 0; i < SnakeLength; i++) {
      setColor(0, 255, 0);
      TFTscreen.stroke(0, 84, 22);
      TFTscreen.rect(Snake[i].x, Snake[i].y, 10, 10);
    }
    setColor(255, 255, 255);
    TFTscreen.setTextSize(1);
    String scoreText = "";
    scoreText += "Score: ";
    scoreText += Score;
    scoreText += "/";
    scoreText += SnakeHighScore;
    char scoreBuff[64];
    scoreText.toCharArray(scoreBuff, 64);
    TFTscreen.text(scoreBuff, 5, 118);
  }
}

void SnakeMove() {
  setColor(0, 0, 0);
  TFTscreen.rect(Snake[SnakeLength - 1].x, Snake[SnakeLength - 1].y, 10, 10);
  for (int16_t i = SnakeLength; i > 0; i--) {
    Snake[i].x = Snake[i - 1].x;
    Snake[i].y = Snake[i - 1].y;
  }
  switch (Richtung) {
    case 1:
      Snake[0].y += 10;
      break;
    case 2:
      Snake[0].y -= 10;
      break;
    case 3:
      Snake[0].x -= 10;
      break;
    case 4:
      Snake[0].x += 10;
      break;
  }
}
void SnakeColision() {
  if (Snake[0].x == -10 || Snake[0].x == 160 || Snake[0].y == -10 || Snake[0].y == 120) {
    //Write value to EEPROM
    if (SnakeHighScore < Score) {
      EEPROM.put(0, Score);
      SnakeHighScore = Score;
    }
    SnakeInit();
  }
  for (int16_t i = 1; i < SnakeLength; i++) {
    if (Snake[i].x == CoinX * 10 && Snake[i].y == CoinY * 10) {
      CoinX = random(0, 15);
      CoinY = random(0, 11);
    }
  }
  for (int16_t i = 2; i < SnakeLength; i++) {
    if (Snake[i].x == Snake[0].x && Snake[i].y == Snake[0].y) {
      //Write value to EEPROM
      if (SnakeHighScore < Score) {
        EEPROM.put(0, Score);
        SnakeHighScore = Score;
      }
      SnakeInit();
      break;
    }
  }
  if (Snake[0].x == CoinX * 10 && Snake[0].y == CoinY * 10) {
    CoinX = random(0, 15);
    CoinY = random(0, 11);
    Score++;
    setColor(0, 0, 0);
    TFTscreen.rect(40, 118, 160, 10);
    if (SnakeLength < 99) {
      SnakeLength++;
    }
  }
}

void HandleKeyInputSnake() {
  if (digitalRead(l2) == LOW) {
    //Write value to EEPROM
    if (SnakeHighScore < Score) {
      EEPROM.put(0, Score);
      SnakeHighScore = Score;
    }
    GameSpeed = 100;
    Modus = 1;
  }
  //UP
  if (digitalRead(t1) == LOW) {
    if (Richtung != 1)
      Richtung = 2;
  } else if (digitalRead(b1) == LOW) { //DOWN
    if (Richtung != 2)
      Richtung = 1;
  } else if (digitalRead(l1) == LOW) { //LEFT
    if (Richtung != 4)
      Richtung = 3;
  } else if (digitalRead(r1) == LOW) { //RIGHT
    if (Richtung != 3)
      Richtung = 4;
  }
}

void SnakeLoop() {
  HandleKeyInputSnake();
  SnakeColision();
  if (Timer == 2) {
    SnakeMove();
    Timer = 0;
  }
  Timer++;
  SnakeDraw();
  if (Modus != 3)
    TFTscreen.background(0, 0, 0);
}

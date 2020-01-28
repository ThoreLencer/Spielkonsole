int16_t tiles[16] = {}, InputTimer;
bool enableInput;
void Init2048() {
  GameSpeed = 30;
  for (int16_t i = 0; i < 16; i++) {
    tiles[i] = 0;
  }
  tiles[random(0, 16)] = 2;
  tiles[random(0, 16)] = 2;
  TFTscreen.background(0, 0, 0);
  enableInput = true;
  InputTimer = 0;
  Draw2048();
}

void Loop2048() {
  HandleKeyInput2048();
  if (Modus != 6)
    TFTscreen.background(0, 0, 0);
  if (!enableInput) {
    InputTimer ++;
    if (InputTimer == 3) {
      enableInput = true;
      InputTimer = 0;
    }
  }
}

void Draw2048() {
  //Draw Tiles
  for (int16_t i = 0; i < 4; i++) {
    for (int16_t i1 = 0; i1 < 4; i1++) {
      setColor(255, 255, 255);
      TFTscreen.noFill();
      TFTscreen.rect(16 + (i1 * 32), 0 + (i * 32), 32, 32);
    }
  }
  //Color Tiles
  for (int16_t i = 0; i < 4; i++) {
    for (int16_t i1 = 0; i1 < 4; i1++) {
      switch (tiles[(i * 4) + i1]) {
        case 0:
          setColor(0, 0, 0);
          break;
        case 2: //PINK
          setColor(255, 158, 250);
          break;
        case 4: //ROT
          setColor(10, 10, 244);
          break;
        case 8: //ORANGE
          setColor(12, 123, 242);
          break;
        case 16: //HELL GELB
          setColor(155, 246, 255);
          break;
        case 32: //GELB
          setColor(0, 232, 255);
          break;
        case 64: //HELL GRÜN
          setColor(0, 255, 153);
          break;
        case 128: //GRÜN
          setColor(17, 201, 4);
          break;
        case 256: //TÜRKIS
          setColor(250, 255, 90);
          break;
        case 512: //HELL BLAU
          setColor(255, 191, 50);
          break;
        case 1024: //BLAU
          setColor(255, 29, 0);
          break;
        case 2048: //LILA
          setColor(252, 2, 185);
          Init2048();
          break;
      }
      TFTscreen.rect(17 + (i1 * 32), 1 + (i * 32), 30, 30);
    }
  }
}

void MoveTilesLeft() {
  for (int16_t z = 0; z < 4; z++) {
    for (int16_t i = 1; i < 4; i++) {
      if (tiles[i + z * 4] != 0) {
        for (int16_t i1 = i; i1 > 0; i1--) {
          if (tiles[i1 + z * 4 - 1] == 0) {
            tiles[i1 + z * 4 - 1] = tiles[i1 + z * 4];
            tiles[i1 + z * 4] = 0;
          } else if (tiles[i1 + z * 4 - 1] == tiles[i1 + z * 4]) {
            tiles[i1 + z * 4 - 1] = tiles[i1 + z * 4] * 2;
            tiles[i1 + z * 4] = 0;
          } else {
            break;
          }
        }
      }
    }
  }
}

void MoveTilesRight() {
  for (int16_t z = 0; z < 4; z++) {
    for (int16_t i = 2; i > -1; i--) {
      if (tiles[i + z * 4] != 0) {
        for (int16_t i1 = i; i1 < 3; i1++) {
          if (tiles[i1 + z * 4 + 1] == 0) {
            tiles[i1 + z * 4 + 1] = tiles[i1 + z * 4];
            tiles[i1 + z * 4] = 0;
          } else if (tiles[i1 + z * 4 + 1] == tiles[i1 + z * 4]) {
            tiles[i1 + z * 4 + 1] = tiles[i1 + z * 4] * 2;
            tiles[i1 + z * 4] = 0;
          } else {
            break;
          }
        }
      }
    }
  }
}

void MoveTilesUp() {
  for (int16_t s = 0; s < 4; s++) {
    for (int16_t i = 1; i < 4; i++) {
      if (tiles[i * 4 + s] > 0) {
        for (int16_t i1 = i; i1 > 0; i1 --) {
          if (tiles[i1 * 4 + s - 4] == 0) {
            tiles[i1 * 4 + s - 4] = tiles[i1 * 4 + s];
            tiles[i1 * 4 + s] = 0;
          } else if (tiles[i1 * 4 + s - 4] == tiles[i1 * 4 + s]) {
            tiles[i1 * 4 + s - 4] = tiles[i1 * 4 + s] * 2;
            tiles[i1 * 4 + s] = 0;
          } else {
            break;
          }
        }
      }
    }
  }
}

void MoveTilesDown() {
  for (int16_t s = 0; s < 4; s++) {
    for (int16_t i = 2; i > -1; i--) {
      if (tiles[i * 4 + s] > 0) {
        for (int16_t i1 = i; i1 < 3; i1++) {
          if (tiles[i1 * 4 + s + 4] == 0) {
            tiles[i1 * 4 + s + 4] = tiles[i1 * 4 + s];
            tiles[i1 * 4 + s] = 0;
          } else if (tiles[i1 * 4 + s + 4] == tiles[i1 * 4 + s]) {
            tiles[i1 * 4 + s + 4] = tiles[i1 * 4 + s] * 2;
            tiles[i1 * 4 + s] = 0;
          } else {
            break;
          }
        }
      }
    }
  }
}

void HandleKeyInput2048() {
  if (digitalRead(l2) == LOW) {
    GameSpeed = 100;
    Modus = 1;
  }
  if (enableInput) {
    bool moved = false;
    if (digitalRead(l1) == LOW) { //LEFT
      MoveTilesLeft();
      moved = true;
    } else if (digitalRead(r1) == LOW) { //RIGHT
      MoveTilesRight();
      moved = true;
    } else if (digitalRead(b1) == LOW) { //DOWN
      MoveTilesDown();
      moved = true;
    } else if (digitalRead(t1) == LOW) { //UP
      MoveTilesUp();
      moved = true;
    }
    if (moved) {
      //REPAint16_t IF MOVED
      Draw2048();
      enableInput = false;
      for (int16_t i = 0; i < 1; i++) {
        int16_t zufall = random(0, 16);
        if (tiles[zufall] != 0) {
          i--;
        } else {
          tiles[zufall] = 2;
        }
      }
      bool tilefree = false;
      for (int16_t i1 = 0; i1 < 16; i1++) {
        if (tiles[i1] == 0) {
          tilefree = true;
          break;
        }
      }
      if (!tilefree) {
        Init2048();
      }
    }
  }
}

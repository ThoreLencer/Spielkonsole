bool Player, Win;
int16_t PlayerSquareX, PlayerSquareY, Feld[9] = {};
void TicTacToeLoop(){
  HandleKeyInputTicTacToe();
  checkForWin();
  TicTacToeDraw();
 if(Modus!=4)
  TFTscreen.background(0, 0, 0);
}

void TicTacToeInit(){
 for(int16_t i = 0; i < 9; i++){
  Feld[i] = 0;
 }
 Player = true;
 Win = false;
 PlayerSquareX = 21;
 PlayerSquareY = 5;
 GameSpeed = 150;
 TFTscreen.background(0, 0, 0);
}

void checkForWin(){
  setColor(255, 255, 255);
  if(Feld[0] == Feld[1] && Feld[1] == Feld[2] && Feld[0] != 0){
    TFTscreen.line(21, 24, 139, 24);
    Win = true;
  }
  if(Feld[3] == Feld[4] && Feld[4] == Feld[5] && Feld[3] != 0){
    TFTscreen.line(21, 64, 139, 64); 
    Win = true;
  }
  if(Feld[6] == Feld[7] && Feld[7] == Feld[8] && Feld[6] != 0){
    TFTscreen.line(21, 104, 139, 104); 
    Win = true;
  }
  if(Feld[0] == Feld[3] && Feld[3] == Feld[6] && Feld[0] != 0){
    TFTscreen.line(40, 4, 40, 124); 
    Win = true;
  }
  if(Feld[1] == Feld[4] && Feld[4] == Feld[7] && Feld[1] != 0){
    TFTscreen.line(80, 4, 80, 124); 
    Win = true;
  }
  if(Feld[2] == Feld[5] && Feld[5] == Feld[8] && Feld[2] != 0){
    TFTscreen.line(120, 4, 120, 124); 
    Win = true;
  }
  if(Feld[0] == Feld[4] && Feld[4] == Feld[8] && Feld[0] != 0){
    TFTscreen.line(21, 4, 139, 124); 
    Win = true;
  }
  if(Feld[2] == Feld[4] && Feld[4] == Feld[6] && Feld[2] != 0){
    TFTscreen.line(139, 4, 21, 124); 
    Win = true;
  }
  for(int16_t i = 0; i < 9; i++){
    if(Feld[i] == 0)
    break;
    if(Feld[i] != 0 && i == 8)
    Win = true;
  }
}

void TicTacToeDraw(){
 TFTscreen.setTextSize(1);
 setColor(0, 255, 0);
 if(Player){
  TFTscreen.text("P1", 4, 59); 
 } else {
  TFTscreen.text("P2", 4, 59); 
 }
 setColor(0, 0, 255);
 TFTscreen.noFill();
 TFTscreen.rect(20, 4, 121, 121);
 for(int16_t i = 1; i < 3; i++){
  TFTscreen.line(20 + (40 * i), 4, 20 + (40 * i), 124);
  TFTscreen.line(20, 4 + (40 * i), 140, 4 + (40 * i));   
 }
 setColor(0, 255, 255);
 TFTscreen.noFill();
 TFTscreen.rect(PlayerSquareX, PlayerSquareY, 39, 39);
}

void HandleKeyInputTicTacToe(){
 if(digitalRead(l1) == LOW){
    GameSpeed = 100;
    Modus = 1;
 }
 //UP 
 if(digitalRead(r1) == LOW){
  if(!Win){
  int16_t Zeile;
  int16_t Spalte;
  int16_t FeldNum;
  switch(PlayerSquareY){
    case 5:
    Zeile = 1;
    break;
    case 45:
    Zeile = 2;
    break;
    case 85:
    Zeile = 3;
    break;
  }
  switch(PlayerSquareX){
    case 21:
    Spalte = 1;
    break;
    case 61:
    Spalte = 2;
    break;
    case 101:
    Spalte = 3;
    break;
  }
  FeldNum = ((Zeile - 1) * 3) + Spalte;
  if(Feld[FeldNum - 1] == 0){
  if(Player){
   Feld[FeldNum - 1] = 1;
   setColor(255, 0, 0);
   TFTscreen.line(PlayerSquareX, PlayerSquareY, PlayerSquareX + 38, PlayerSquareY + 38); 
   TFTscreen.line(PlayerSquareX, PlayerSquareY + 38, PlayerSquareX + 38, PlayerSquareY); 
  } else {
   Feld[FeldNum - 1] = 2;
   setColor(255, 0, 0);
   TFTscreen.noFill();
   TFTscreen.circle(PlayerSquareX + 19, PlayerSquareY + 19, 18);
  }
  Player = !Player;
  setColor(0, 0, 0);
  TFTscreen.rect(0, 0, 20, 128);
  }
  } else {
   TicTacToeInit(); 
  }
 }else if(digitalRead(b2) == LOW){ //DOWN
  if(PlayerSquareY != 85){
   erasePlayerSquare();
   PlayerSquareY += 40; 
  } else {
   erasePlayerSquare();
   PlayerSquareY = 5;  
  }
 }else if(digitalRead(t2) == LOW){ //TOP
  if(PlayerSquareY != 5){
   erasePlayerSquare();
   PlayerSquareY -= 40; 
  } else {
   erasePlayerSquare();
   PlayerSquareY = 85;  
  }
 }else if(digitalRead(l2) == LOW){ //LEFT
  if(PlayerSquareX != 21){
   erasePlayerSquare();
   PlayerSquareX -= 40; 
  }else{
    erasePlayerSquare();
    PlayerSquareX = 101;
  }
 } else if(digitalRead(r2) == LOW){ //RIGHT
  if(PlayerSquareX != 101){
   erasePlayerSquare();
   PlayerSquareX += 40; 
  } else {
    erasePlayerSquare();
    PlayerSquareX = 21;
  }
 }  
}

void erasePlayerSquare(){
 setColor(0, 0, 0);
 TFTscreen.noFill();
 TFTscreen.rect(PlayerSquareX, PlayerSquareY, 39, 39); 
}

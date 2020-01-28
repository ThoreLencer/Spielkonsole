int16_t PlayerX, PlayerY, ComputerX, ComputerY, BallX, BallY, PlayerScore, ComputerScore, BallManipulationX, BallManipulationY;
bool BallMoveTop, BallMoveLeft;
void PongLoop(){
   HandleKeyInputPong();
   HandleAccelerometerPong();
   BallColision();
   MoveBall();
   MoveComputer();
   DrawPong();
   if(Modus != 2){
    TFTscreen.background(0, 0, 0);
   }
}

void HandleAccelerometerPong(){
  lis.read();
  sensors_event_t event; 
  lis.getEvent(&event);
  int val = (int)event.acceleration.y + 3;
  val = val * -1;
  if((PlayerY + val > 0) && (PlayerY + val < 78))
    PlayerY += val;
  if(PlayerY + val < 0)
    PlayerY = 0;
  if(PlayerY + val > 78)
    PlayerY = 78;
}
void PongInit(){
  GameSpeed = 70;
  TFTscreen.background(0, 0, 0);
  PlayerScore = 0;
  ComputerScore = 0;
  PlayerX = 145;
  PlayerY = 41;
  ComputerX = 5;
  ComputerY = 41;
  BallX = 75;
  BallY = 60;
  BallMoveTop = false;
  BallMoveLeft = false;
  BallManipulationX = 0;
  BallManipulationY = 0;
}
void HandleKeyInputPong(){
  if(digitalRead(l2) == LOW){
    GameSpeed = 100;
    Modus = 1;
  }
  //UP 
  if(digitalRead(t1) == LOW){
    if(PlayerY - 3 >= 0)
    PlayerY -= 3;
  }
  //DOWN
  if(digitalRead(b1) == LOW){
    if(PlayerY + 3 <=78)
    PlayerY += 3;
  }
}
void DrawPong(){
 setColor(255, 255, 255);
 TFTscreen.setTextSize(1);
 String scoreText = "";
 scoreText += ComputerScore;
 scoreText += ":";
 scoreText += PlayerScore;
 char scoreBuff[64];
 scoreText.toCharArray(scoreBuff, 64);
 TFTscreen.text(scoreBuff, (160 - ((scoreText.length() * 5) - 2 + (scoreText.length() - 1))) / 2, 2); 
 setColor(0, 0, 0);
 drawAroundV(PlayerX, PlayerY, 50, 10, 10);
 drawAroundV(ComputerX, ComputerY, 50, 10, 3);
 if(BallX > ComputerX + 10)
 TFTscreen.rect(BallX - 5-BallManipulationX, BallY - 5-BallManipulationY, 5+BallManipulationX, 5+BallManipulationY);
 if(BallX < PlayerX - 5)
 TFTscreen.rect(BallX + 5 + BallManipulationX, BallY - 5 - BallManipulationY, 5+BallManipulationX, 5+BallManipulationY);
 if(BallX > ComputerX + 10)
 TFTscreen.rect(BallX - 5 - BallManipulationX, BallY + 5 + BallManipulationY, 5+BallManipulationX, 5+BallManipulationY);
 if(BallX < PlayerX - 5)
 TFTscreen.rect(BallX + 5 + BallManipulationX, BallY + 5 + BallManipulationY, 5+BallManipulationX, 5+BallManipulationY);
 if(BallX > ComputerX + 10)
 TFTscreen.rect(BallX - 5 - BallManipulationX, BallY, 5+BallManipulationX, 5+BallManipulationY);
 if(BallX < PlayerX - 5)
 TFTscreen.rect(BallX + 5 + BallManipulationX, BallY, 5+BallManipulationX, 5+BallManipulationY);  
 setColor(0, 255, 0);
 TFTscreen.rect(BallX, BallY, 5, 5);
 setColor(0, 0, 255);
 TFTscreen.rect(PlayerX, PlayerY, 10, 50);
 TFTscreen.rect(ComputerX, ComputerY, 10, 50);
}

void randBallManipulation(){
  BallManipulationX = random(0, 3);
  BallManipulationY = random(0, 4);
}

void MoveBall(){
 if(BallMoveTop){
  BallY -= 4 + BallManipulationY; 
 } else {
  BallY += 4 + BallManipulationY;
 }
 if(BallMoveLeft){
  BallX -= 5 + BallManipulationX;
 } else {
  BallX += 5 + BallManipulationX;
 }
}
void BallColision(){
 if(BallX <= -5){
  PlayerScore ++;
  setColor(0, 0, 0);
  TFTscreen.rect(0, 0, 160, 128);
  BallX = 75;
  BallY = 60;
  BallMoveLeft = false;
  randBallManipulation();
 }
 if(BallX >= 160){
  BallX = 75;
  BallY = 60;
  BallMoveLeft = false;
  randBallManipulation();
  ComputerScore ++;
  setColor(0, 0, 0);
  TFTscreen.rect(0, 0, 160, 128);
 }
 if(BallY <= 0){
  BallMoveTop = false;
  randBallManipulation();
 }
 if(BallY >= 123){
  BallMoveTop = true;
  randBallManipulation();
 }

 if(BallX >= PlayerX - 5){
  if(BallY >= PlayerY && BallY <= PlayerY + 50){
   BallMoveLeft = true;
   setColor(0, 0, 0);
   TFTscreen.rect(155, 0, 5, 128);
   randBallManipulation();
  }
 }

 if(BallX <= ComputerX + 10){
  if(BallY >= ComputerY && BallY <= ComputerY + 50){
   BallMoveLeft = false;
   randBallManipulation();
   setColor(0, 0, 0);
   TFTscreen.rect(0, 0, 5, 128);
  }
 }
}
void MoveComputer(){
  if(BallMoveLeft){
  if(BallX < 100){
   if(BallY < ComputerY + 15)
   if(ComputerY - 2 >= 0)
    ComputerY-=2;
   if(BallY > ComputerY + 45)
   if(ComputerY + 2 <= 78)
    ComputerY+=2; 
  }
  }
}

#include <Vector.h>
struct Projectile {
  int16_t x;
  int16_t y;
};
struct Asteroid {
  int16_t x;
  int16_t y;
  int16_t type;
  int16_t lives;
};
int16_t SpaceShipX, SpaceShipY, ShootingTimer, AsteroidsScore, rotation;
Projectile projectile_array[10];
Vector<Projectile> projectiles(projectile_array);

Asteroid asteroid_array[4];
Vector<Asteroid> asteroids(asteroid_array);
void AsteroidsInit() {
  GameSpeed = 50;
  SpaceShipX = 80;
  SpaceShipY = 64;
  AsteroidsScore = 0;
  ShootingTimer = 0;
  rotation = 0;
  asteroids.clear();
  projectiles.clear();
  TFTscreen.background(0, 0, 0);
  for (int16_t i = 0; i < 4; i++) {
    CreateAsteroid();
  }
}

void SpaceShipColision() {
  for (int16_t i = 0; i < asteroids.size(); i++) {
    if (SpaceShipX > asteroids.at(i).x && SpaceShipX < asteroids.at(i).x + 20 && SpaceShipY > asteroids.at(i).y && SpaceShipY < asteroids.at(i).y + 20 || SpaceShipX + 10 > asteroids.at(i).x && SpaceShipX + 10 < asteroids.at(i).x + 20 && 125 > asteroids.at(i).y && 125 < asteroids.at(i).y + 20) {
      setColor(0, 0, 0);
      TFTscreen.rect(SpaceShipX - 20, 80, 40, 48);
      asteroids.remove(i);
      CreateAsteroid();
      AsteroidsInit();
      setColor(0, 0, 0);
      TFTscreen.rect(36, 0, 120, 15);
    }
  }
}

void ProjectileColision() {
  for (int16_t i = 0; i < projectiles.size(); i++) {
    for (int16_t i1 = 0; i1 < asteroids.size(); i1++) {
      if (projectiles.at(i).x > asteroids.at(i1).x && projectiles.at(i).x < asteroids.at(i1).x + 20 && projectiles.at(i).y > asteroids.at(i1).y && projectiles.at(i).y < asteroids.at(i1).y + 20) {
        asteroids.at(i1).lives --;
        if (asteroids.at(i1).lives == 0) {
          setColor(0, 0, 0);
          TFTscreen.rect(asteroids.at(i1).x - 2, asteroids.at(i1).y - 2, 32, 32);
          projectiles.remove(i);
          asteroids.remove(i1);
          CreateAsteroid();
          AsteroidsScore += 4;
          setColor(0, 0, 0);
          TFTscreen.rect(36, 0, 120, 15);
        }
      }
    }
  }
}

void CreateAsteroid() {
  Asteroid newAsteroid;
  newAsteroid.x = random(0, 150);
  newAsteroid.y = random(0, 20);
  newAsteroid.type = random(1, 3);
  newAsteroid.lives = random(1, 5);
  asteroids.push_back(newAsteroid);
}

void AsteroidsLoop() {
  HandleKeyInputAsteroids();
  ProjectileMove();
  AsteroidMove();
  ProjectileColision();
  SpaceShipColision();
  AsteroidsDraw();
  if (Modus != 5)
    TFTscreen.background(0, 0, 0);
}

void AsteroidsDraw() {

  setColor(0, 255, 0);
  TFTscreen.line(SpaceShipX, SpaceShipY, SpaceShipX + 10 * cos(rotation * (PI / 180)), SpaceShipY + 10 * sin(rotation * (PI / 180)));
  TFTscreen.line(SpaceShipX, SpaceShipY, SpaceShipX + 15 * cos((rotation + 289.5) * (PI / 180)), SpaceShipY + 15 * sin((rotation + 289.5) * (PI / 180)));
  TFTscreen.line(SpaceShipX + 10 * cos(rotation * (PI / 180)), SpaceShipY + 10 * sin(rotation * (PI / 180)), SpaceShipX + 15 * cos((rotation + 289.5) * (PI / 180)), SpaceShipY + 15 * sin((rotation + 289.5) * (PI / 180)));

  for (int16_t i = 0; i < projectiles.size(); i++) {
    setColor(0, 0, 0);
    drawAroundV(projectiles.at(i).x, projectiles.at(i).y, 2, 2, 8);
    setColor(0, 255, 255);
    TFTscreen.rect(projectiles.at(i).x, projectiles.at(i).y, 2, 2);
  }
  for (int16_t i = 0; i < asteroids.size(); i++) {
    setColor(0, 0, 0);
    drawAroundV(asteroids.at(i).x, asteroids.at(i).y, 20, 20, 2);
    setColor(145, 111, 88);
    TFTscreen.circle(asteroids.at(i).x + 10, asteroids.at(i).y + 10, asteroids.at(i).type * 3);
  }
  TFTscreen.setTextSize(1);
  setColor(255, 255, 255);
  String scoreText = "";
  scoreText += "Score: ";
  scoreText += AsteroidsScore;
  char scoreBuff[64];
  scoreText.toCharArray(scoreBuff, 64);
  TFTscreen.text(scoreBuff, 0, 5);
}

void AsteroidMove() {
  for (int16_t i = 0; i < asteroids.size(); i++) {
    if (asteroids.at(i).y + 1 < 129) {
      asteroids.at(i).y += 2;
    } else {
      asteroids.remove(i);
      CreateAsteroid();
      AsteroidsScore -= 10;
      setColor(0, 0, 0);
      TFTscreen.rect(36, 0, 120, 15);
    }
  }
}

void ProjectileMove() {
  for (int16_t i = 0; i < projectiles.size(); i++) {
    if (projectiles.at(i).y - 8 > -16) {
      projectiles.at(i).y -= 8;
    } else {
      projectiles.remove(i);
    }
  }
}

void clearShip() {
  setColor(0, 0, 0);
  TFTscreen.line(SpaceShipX, SpaceShipY, SpaceShipX + 10 * cos(rotation * (PI / 180)), SpaceShipY + 10 * sin(rotation * (PI / 180)));
  TFTscreen.line(SpaceShipX, SpaceShipY, SpaceShipX + 15 * cos((rotation + 289.5) * (PI / 180)), SpaceShipY + 15 * sin((rotation + 289.5) * (PI / 180)));
  TFTscreen.line(SpaceShipX + 10 * cos(rotation * (PI / 180)), SpaceShipY + 10 * sin(rotation * (PI / 180)), SpaceShipX + 15 * cos((rotation + 289.5) * (PI / 180)), SpaceShipY + 15 * sin((rotation + 289.5) * (PI / 180)));
}

void HandleKeyInputAsteroids() {
  if (digitalRead(l2) == LOW) {
    GameSpeed = 100;
    Modus = 1;
  }
  //UP
  if (digitalRead(t1) == LOW) {
    //MOVE
    clearShip();
    SpaceShipX = SpaceShipX + 3 * cos((rotation + 270) * (PI / 180));
    SpaceShipY = SpaceShipY + 3 * sin((rotation + 270) * (PI / 180));
    //SHOOT
    if (ShootingTimer == 2) {
      Projectile newProjectile;
      newProjectile.x = SpaceShipX + 5;
      newProjectile.y = 103;
      projectiles.push_back(newProjectile);
      ShootingTimer = 0;
    }
    ShootingTimer++;
  }
  if (digitalRead(l1) == LOW) { //LEFT
    clearShip();
    rotation -= 10;
  } else if (digitalRead(r1) == LOW) { //RIGHT
    clearShip();
    rotation += 10;
  }
}

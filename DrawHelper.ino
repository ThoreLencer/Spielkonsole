void setColor(int16_t r, int16_t g, int16_t b){
  TFTscreen.stroke(r, g, b);
  TFTscreen.fill(r, g, b); 
}

void drawAroundV(int16_t x, int16_t y, int16_t ObjHeight, int16_t ObjWidth, int16_t drawHeight){
 TFTscreen.rect(x, y - drawHeight, ObjWidth, drawHeight);
 TFTscreen.rect(x, y + ObjHeight, ObjWidth, drawHeight); 
}

void drawAroundH(int16_t x, int16_t y, int16_t ObjHeight, int16_t ObjWidth, int16_t drawWidth){
 TFTscreen.rect(x - drawWidth, y, drawWidth, ObjHeight);
 TFTscreen.rect(x + ObjWidth, y, drawWidth, ObjHeight); 
}

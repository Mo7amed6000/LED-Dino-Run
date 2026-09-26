const int g1 = 3 ;
const int g2 = 4 ;
const int g3 = 5 ;
const int g4 = 6 ;
const int g5 = 7 ;
const int g6 = 8 ;
const int g7 = 9 ;
const int g8 = 10;

int a = 0 ;
int i ;

double OLD = 0 ;
double OLD1 = 0 ;
double OLD2 = 0 ;
double NEW = 0 ;

boolean mod = 0 ;
boolean mod1 = 0 ;
boolean jmod = 0 ;
boolean lose = 0 ;
int gnd[8] = {g1,g2,g3,g4,g5,g6,g7,g8} ;

int Speed = 500 ;
int data = A0 ;
int Rclock = A1 ;
int SRclock = A2 ;

boolean b [8][8] =
{ 
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0}
};

boolean sun [4][4] = 
{
{1,0,1,1},
{0,1,1,1},
{1,1,1,1},
{1,1,1,1}
};

typedef struct pose{
  
   int x  ;
   int y  ;
   
   int xmax ;
   int ymax ;
   
   pose(int x ,int y ,int xmax ,int ymax){
   this-> x = x ;
   this-> y = y ;
   this-> xmax = xmax ;
   this-> ymax = ymax ;
   }
}pose;

pose obj = pose(0 ,0 , 0,1) ;

pose tree1 = pose(7 ,0 , 0,2) ;

void setup() {
  Serial.begin(9600);
  for(int i =0 ; i<8 ;i++){
    pinMode (gnd[i],OUTPUT);
    digitalWrite(gnd[i] , HIGH);
  }
  pinMode (data,OUTPUT);
  pinMode (SRclock,OUTPUT);
  pinMode (Rclock,OUTPUT);
}

void loop() {
  NEW  = millis();
  if(lose == 0){
    clean();
    jump();
    drawobj(tree1);
    drawobj(obj);
    disOut(b);
    if(collusion(obj , tree1) == true){
      lose = 1;
      Speed = 500 ;
    }
    if(NEW - OLD2 > Speed){
      tree1.x -= 1 ;
      OLD2 = NEW ;
    }
    if(tree1.x < 0){
      Speed -= 50 ;
      tree1.x = 7 ;
    }
  }
  else{
    drawRandom();
    disOut(b);
    obj.x = 0 ;
    obj.y = 5 ;
    tree1.x = 7 ;
  }
  buttenRead();
}

boolean collusion(struct pose obj1 , struct pose obj2){
  if(obj1.x <= obj2.x + obj2.xmax
  && obj1.x + obj1.xmax >= obj2.x
  && obj1.y < obj2.y + obj2.ymax
  && obj1.ymax + obj1.y > obj2.y)
        {
          return true ;
        }
        return false ;
}

void jump(){
  if(jmod == 0 && obj.y != 0 && NEW - OLD > 100 - i){
    obj.y-- ;
    OLD = NEW ;
    i += 10 ;
  }
  if(jmod == 1 && NEW - OLD > 20 + i){
    obj.y++ ;
    OLD = NEW ;
    i += 10 ;
  }
  if(obj.y >= 5){
    jmod = 0;
    i = 0 ;
  }
}

void Update(){
  if(NEW - OLD > 100 ) {
    obj.xmax ++ ; 
    obj.ymax ++ ;
    OLD = NEW ;
  }
  if(all1(b) == true){
    obj.x = random(0 , 8);
    obj.y = random(0 , 8);
    obj.xmax = 0; 
    obj.ymax = 0;
  }
}

void drawImage(int x_image , int y_image ,boolean a[4][4] ,int x , int y){
  for(int i = 0 ; i<x_image  ; i++){
    for(int j = 0 ; j<y_image  ; j++){
      b[i+x][j+y] = a[i][j];
    }
  }  
}

void drawobj(struct pose obj){
  for(int i = 0 ; i<=obj.xmax ; i++){
    for(int j = 0; j<=obj.ymax ; j++){
      int xx ;
      int yy ;
      if(obj.x + i > 7 ){
        xx = obj.x + i - 8;
      }
      else{
        xx = obj.x + i;
      }
      if(obj.y + j > 7 ){
        yy = obj.y + j - 8;
      }
      else{
        yy = obj.y + j;
      }
      b[xx][yy] = 1;
    }
  }
}

void clean(){
  for(int i = 0 ; i<8 ; i++){
    for(int j = 0 ; j<8 ; j++){
      b[i][j] = 0;
    }
  }
}

void drawRandom(){

  if(all0(b) == true){
    mod = 0 ;
    lose = 0 ;
  }
  else if (all1(b) == true){
    mod = 1 ;
  }
  
  obj.x = random(0 , 8) ;
  obj.y = random(0 , 8) ;
  if (mod == 0){
    if((NEW - OLD )> 0){
    b[obj.x][obj.y] = 1;
    OLD = NEW ;
    }
  }
  else if(mod == 1){
    if((NEW - OLD )> 0){
    b[obj.x][obj.y] = 0;
    OLD = NEW ;
    }
  }
}


void buttenRead(){
  double NEW = millis();
  if(digitalRead(A4) == 1 && (NEW - OLD1 )> 100){
    obj.x += 1 ;
    OLD1 = NEW ;
  }
  if(obj.x > 7){
    obj.x = 0 ;
  }
  if(digitalRead(A5) == 1 && (NEW - OLD1 )> 100 && obj.y == 0){
    jmod = 1 ;
    OLD1 = NEW ;
  }
}

boolean all1(boolean mat[8][8]){
  for(int i = 0 ;i<8 ;i++){
    for(int j = 0 ;j<8 ;j++){
      if(mat[i][j] == 0){
        return false ;
      }
    }
  }
  return true ;
}

boolean all0(boolean mat[8][8]){
  for(int i = 0 ;i<8 ;i++){
    for(int j = 0 ;j<8 ;j++){
      if(mat[i][j] == 1){
        return false ;
      }
    }
  }
  return true ;
}

void shiftout(boolean b[]){
  for (int i =0 ; i<8 ; i++){
    digitalWrite(data , LOW);
    ck(); 
  }
  for (int i =0 ; i<8 ; i++){
    digitalWrite(data , b[i]);
    ck(); 
  }
  delayMicroseconds(2250);
}

void disOut(boolean mat[8][8]){
  for(int i = 0 ; i<8 ; i++){
    digitalWrite(gnd[i],LOW);
    shiftout(mat[i]);
    digitalWrite(gnd[i],HIGH);
  }
  
}

void ck(){
  digitalWrite(SRclock , LOW);
  digitalWrite(SRclock  , HIGH);
  digitalWrite(Rclock  , LOW);
  digitalWrite(Rclock , HIGH);
}

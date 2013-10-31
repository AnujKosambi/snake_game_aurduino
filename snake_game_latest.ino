#include <FrequencyTimer2.h>

 
#define W { \
    {0, 0, 0, 0, 0, 0, 0, 0}, \
    {0, 1, 0, 0, 0, 1, 0, 0}, \
    {0, 1, 0, 0, 0, 1, 0, 0}, \
    {0, 1, 0, 1, 0, 1, 0, 0}, \
    {0, 1, 0, 1, 0, 1, 0, 0}, \
    {0, 1, 1, 0, 1, 1, 0, 0}, \
    {0, 1, 0, 0, 0, 1, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0}  \
}
class snake{
public:
	int x;
	int y;
	int oldx;
	int oldy;
	snake* next;
};
int length=1;
snake* head;
void addTail();
void positionSnake(int,int);
byte col = 0;
byte leds[8][8];
class food{
public:
	int x;
	int y;
};
 
int pins[17]= {-1, 4,6,8,9,7,11,5,2,0,10,12,3,0,0,13,0};

// col[xx] of leds = pin yy on led matrix
//int cols[8] = {pins[13], pins[3], pins[4], pins[10], pins[06], pins[11], pins[15], pins[16]};
int cols[8]={0,8,9,10,11,12,13,0};
// row[xx] of leds = pin yy on led matrix
int rows[8] = {pins[9], pins[14], pins[8], pins[12], pins[1], pins[7], pins[2], pins[5]};
//int rows[8]= {0,0,2,3,4,5,6,7};

int pattern = 0;
byte WON[8][8] = W;

food* packet;
void setup() {
   packet=new food;
  packet->x=3;
  packet->y=3;
  
  // sets the pins as output
  for (int i = 1; i <= 16; i++) {
    pinMode(pins[i], OUTPUT);
  }
  
  // set up cols and rows
  for (int i = 1; i <= 8; i++) {
    digitalWrite(cols[i - 1], HIGH);
  }
 
  for (int i = 1; i <= 8; i++) {
    digitalWrite(rows[i - 1], HIGH);
  }
  clearLeds();
  head=new snake;
 
  FrequencyTimer2::disable();
  FrequencyTimer2::setPeriod(2000);
  FrequencyTimer2::setOnOverflow(display);
//Serial.begin(110);

}

int LEFT=1;
int TOP=0;
int X=3;
int Y=0;
int counter=0;
int Speed=300;
void loop() {
  
 
  
  int leftSwitch=analogRead(A5);
  int topSwitch=analogRead(A3);
   counter++;
 
  if(analogRead(A5)>=1020)
  {
   if(LEFT!=0)
     {
       LEFT=0;
       TOP=1;
     }
   else
   
     {
       LEFT=1;
       TOP=0;
     }
  }
   if(analogRead(A3)>=1020)
  {
   if(LEFT!=0)
     {
       LEFT=0;
       TOP=-1;
     }
   else
        {
       LEFT=-1;
       TOP=0;
     }
  }
    X=X+LEFT;
    Y=Y+TOP;
    if(Y==6)
      Y=0;
    if(X==7)
     X=1;
      
      clearLeds();
      
        leds[packet->x][packet->y]=1;
        
        if(head->x==packet->x && head->y==packet->y)
        {
          addTail();
          packet->x=random(1,6);
          packet->y=random(0,5);
          
        }
        snake* temp=head;
			while(temp!=NULL){
                               
				leds[temp->x][temp->y]=1;
				temp=temp->next;
			}
     positionSnake(X,Y);
     
     
    if(length==6)
  {
     clearLeds();
    for(int i=0;i<8;i++)
      for(int j=0;j<8;j++)
         leds[i][j]=1;
         //leds[i][j]=WON[i][j];
         delay(2000);
         head->next=NULL;
         length=1;
         Speed=Speed*0.8;
  }
    delay(Speed);

  
  
}  
 
void clearLeds() {
  
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      leds[i][j] = 0;
    }
  }
}

void addTail(){
    length++;
	snake* temp=head;
	while(temp->next){
		temp=temp->next;
	}
	temp->next=new snake;
}
void positionSnake(int x,int y){
	head->oldx=head->x;
	head->oldy=head->y;
	head->x=x;
	head->y=y;
	snake* temp=head;
		while(temp->next!=NULL)
		{
			temp->next->oldx=temp->next->x;
			temp->next->oldy=temp->next->y;
			temp->next->x=temp->oldx;
			temp->next->y=temp->oldy;

			temp=temp->next;
		}


}

void display() {
  digitalWrite(cols[col], HIGH);  
  col++;
  if (col == 8) {
    col = 0;
  }
  for (int row = 0; row < 8; row++) {
    if (leds[col][7 - row] == 1) {
      digitalWrite(rows[row], HIGH);  
    }
    else {
      digitalWrite(rows[row], LOW); 
    }
  }
  digitalWrite(cols[col], LOW); 
}

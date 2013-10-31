
class snake{
public:
	int x;
	int y;
	int oldx;
	int oldy;
	snake* next;
};
#define leftPin 8
#define rightPin 9
#define topPin 10
#define bottomPin 11
snake* head;
char matrix[8][8];
int left=1;
int top=0;

void setup(){
      // setting up rows of 8x8 led matrix
        pinMode(2,OUTPUT);
        pinMode(3,OUTPUT);
        pinMode(4,OUTPUT);
        // setting up columns of 8x8 led matrix
        pinMode(5,OUTPUT);
        pinMode(6,OUTPUT);
        pinMode(7,OUTPUT);
        // setting up 4 switches
        pinMode(leftPin,INPUT);
        pinMode(rightPin,INPUT);
        pinMode(topPin,INPUT);
        pinMode(bottomPin,INPUT);
        
        head=new snake;
	//addTail();addTail();addTail();addTail();
	head->x=4;
	head->y=4;
}

void loop(){
  int leftReading = digitalRead(leftPin);
  int rightReading = digitalRead(rightPin);
  int topReading= digitalRead(topPin);
  int bottomReading = digitalRead(bottomPin);
  
}

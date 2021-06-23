#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_G3 196
#define NOTE_A3 220
#define NOTE_B3 246
#define NOTE_G4 415
#define NOTE_F4 369
#define NOTE_E 329

int i;
int melody1[] = {
  NOTE_G4,NOTE_F4,NOTE_E , NOTE_B3, NOTE_E,NOTE_F4,NOTE_G4,
  NOTE_E,NOTE_E3,NOTE_G3,NOTE_A3,NOTE_F3
};
int noteDuration[] = {
  4,4,4,4,4,4,4,4,4,4,4,4
};

int latchPin = 10;
int clockPin = 12;
int dataPin =11;
int buttonPin[8] = {9,8,7, 6, 5, 4, 3, 2};
int previousState[8]= {1};
int presentState[8]= {1};
int buttonFlag=0;
int startpin=1;
int pS=1,pviS=1;
int startState=0;

byte colDataMatrix[8] = {
  B11111110,
  B11111101,
  B11111011,
  B11110111,
  B11101111,
  B11011111,
  B10111111,
  B01111111
};



byte rowDataMatrix2[8]={
	B00010000,
    B00100000,
    B01000000,
    B10000000,
    B01000000,
    B00100000,  
    B00010000,
    B00001000    
};//last
byte rowDataMatrix1[8]={
	B00000001,
    B00000010,
    B00000100,
    B00001000,
    B00000100,
	B00000010,
    B00000001,
    B00000100 
};//first
void setup()
{
  pinMode(latchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(dataPin,OUTPUT);
  pinMode(startpin,INPUT_PULLUP);
  for(int i = 0; i < 8; i++)pinMode(buttonPin[i], INPUT_PULLUP);
}
int s=0;
void restart()
{
  for(int k=0;k<7;k++)
  {
  	rowDataMatrix1[k]=rowDataMatrix1[k+1];
  	rowDataMatrix1[7]=rowDataMatrix2[s];
  } 
  s++;
  if(s==7)
  {
  for(int r=0;r<7;r++)
  	{
    	rowDataMatrix1[r]=rowDataMatrix2[r+1];
	}
  }
}
void Start()
{
  
   for(i=0;i<12;i++)
    {
      	int noteDurations=1000/noteDuration[i];
    	tone(13,melody1[i],noteDurations);
     	int PauseBetweenNote=noteDurations*1.3;
    	delay(PauseBetweenNote);
    	noTone(13);
    } //when start button is pressed play the music
   	

      
    //when start button is pressed change the opening pattern 
    buttonFlag=1;
}
void loop()
{ 
   buttonFlag=0;
   //startState=digitalRead(startpin);
  //if(startState==LOW)Start();
  
  if (buttonFlag=1)
  {
  	for(int p=0; p<8; p++) presentState[p] = digitalRead(buttonPin[p]);
  	for(int i=0;i<8;i++)
    {
    	digitalWrite(latchPin,LOW);
      	shiftOut(dataPin, clockPin, MSBFIRST, colDataMatrix[i]);
		shiftOut(dataPin, clockPin, MSBFIRST, rowDataMatrix1[i]);
    	digitalWrite(latchPin, HIGH);
    	delay(1);
    }
     buttonFlag=0;
  }
  
  
  
  if(presentState[0] == 0 )
  {	
   
    tone(13, NOTE_G4,100);
    restart();
  }
  


  else if(presentState[1] ==0)
  {
 	
    tone(13, NOTE_F4,100);
    restart();
  }
    
  
  //G3
  else if(presentState[2] == 0)
  {
    
    tone(13, NOTE_E,100);
    restart();
  }
  
  
  //A3
  else if(presentState[3] == 0)
  {
  	
    tone(13, NOTE_B3,100);
   	restart();
  }
   
  
  //B3
  else if(presentState[4] == 0)
  {
	
    tone(13, NOTE_E3, 100);
    restart();
  }
    
  //G3
  else if(presentState[5] == 0)
  {
  	
    tone(13, NOTE_G3,100);
    restart();
  }
  
  //F4
  else if(presentState[6] == 0)
  {
   
    tone(13, NOTE_A3,100);
	restart();
  }
  
  //E
  else if(presentState[7] ==  0)
  {
    
    tone(13, NOTE_E,100);
    restart();
   }

 else if(presentState[8] == 0)
 {
   	
    tone(13, NOTE_F3,100);
    restart();
  } 
 
 
}

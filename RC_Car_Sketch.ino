#include <Stepper.h>

int stepperPins[]= {2,3,4,5};
int currentPos= 0;
int state=0;
int memoryRight=0;
int memoryLeft=0;
int memoryForward=0;
int memoryBack=0;
int y=0;
int speed=1;

void setupStepper()
{
  for(int x=0; x<4; x++)
  {
    pinMode (stepperPins[x], OUTPUT);
  }
}

void moveStepper(int direction)
{
  digitalWrite(stepperPins[currentPos], 0);
  currentPos= currentPos + direction;
  if (currentPos>3)
    currentPos= 0;
  if (currentPos<0)
    currentPos= 3;
  digitalWrite(stepperPins[currentPos], 1); 
}

void setup() { 
  setupStepper();
  Serial.begin(9600);
  pinMode (6, OUTPUT);
  pinMode (7, OUTPUT);
  pinMode (8, OUTPUT);
  pinMode (9, OUTPUT);
  pinMode (10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
}

void steerLeft()
{
  int del=3;
  for (int x=0; x<500; x++)
      {
         moveStepper(1);
         delay (del);
      }
}

void steerRight()
{
  int del=3;
  for (int x=0; x<500; x++)
      {
         moveStepper(-1);
         delay (del);
      }
}

void speedSelector()
{
  if (speed==0)
    {
      analogWrite(9, 100);////
      analogWrite(12, 100);////
    }

    if (speed==1)
    {
      analogWrite(9, 180);////
      analogWrite(12, 180);////
    }
    if (speed==2)
    {
      analogWrite(9, 255);////
      analogWrite(12, 255);////
    }
  
}


void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()>0)
  {
    state= Serial.read();
    
  }
  
  if (state=='0')
  {
    if (memoryBack==1)
      y=0;
    else if (memoryForward==0)
    {
      digitalWrite (7, HIGH);
      digitalWrite (10, HIGH);
      digitalWrite (8, LOW); 
      digitalWrite (11, LOW); 
      speedSelector();
      memoryForward=1;
    }
    else
    {
      digitalWrite (7, LOW);
      digitalWrite (10, LOW);
      memoryForward=0;
    }
  }
  
if (state=='1')
  {
    if (memoryForward==1)
      y=0;
    else if (memoryBack==0)
    {
      digitalWrite (7, LOW);
      digitalWrite (10, LOW);
      digitalWrite (8, HIGH); 
      digitalWrite (11, HIGH); 
      speedSelector();
      memoryBack=1;
    }
    else
    {
      digitalWrite (7, HIGH);
      digitalWrite (10, HIGH);
      memoryBack=0;
    }
  }
  

  if (state== '2') //right
    {
      if (memoryLeft==1)
        y=0;
      else if (memoryRight==0)
        {
          steerRight();
          memoryRight=1;
          
        }
      else
        {
        steerLeft();
        memoryRight=0;
        }
    }
    
  if (state== '3')//left
  {
    if (memoryRight==1)
      y=0;
    else if (memoryLeft==0)
        {
          steerLeft();
          memoryLeft=1;
          
        }
    else
        {
        steerRight();
        memoryLeft=0;
        }
  }
  
  if (state== '4')
    digitalWrite (6, HIGH);
    
  if (state== '5')
    digitalWrite (6, LOW);

   if (state== '6')
    {speed= 0;
    //speedSelector();
    }
    
  if (state== '7')
    {speed= 1;
    //speedSelector();
    }

   if (state== '8')
    {speed= 2;
    //speedSelector();
    }
    
  state=0;
}





#include <U8glib.h>

U8GLIB_ST7920_128X64 u8g(13, 11, 10, U8G_PIN_NONE); // SPI Com: SCK = en = 13, MOSI = rw = 11, CS = di = 0

//pin vars
const int BLEFT = 2;
const int BUP = 3;
const int BDOWN = 4;
const int BRIGHT = 5;

//console strings & command
String command;
String Createlabz;
String cons;

bool Start = false;
bool Stop = false;
bool arduinoControl = true;

char oudechar;

//global button bools
bool MLEFT = false;
bool MRIGHT = false;
bool MUP = false;
bool MDOWN = false;

//snake position & length
const int maxSnakeLength = 200;
int snakeLength = 6;

int snakeX[maxSnakeLength];
int snakeY[maxSnakeLength];

//food

int foodX = 6;
int foodY= 6;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Snake");
  pinMode(BLEFT, INPUT);
  pinMode(BUP, INPUT);
  pinMode(BDOWN, INPUT);
  pinMode(BRIGHT, INPUT);

  u8g.firstPage(); 
  do {
    first();
  } while( u8g.nextPage() );
  delay(2000);
  clearlcd();

  u8g.firstPage(); 
  do {
    second();
  } while( u8g.nextPage() );
    delay(2000);
  clearlcd();
  
  //random maken
  randomSeed(analogRead(0));

  snakeX[0] = 20;
  snakeY[0] = 20;
  GiveFood();
}

void loop() {
    first();
    second();
  if (OnScreen(snakeX[0], snakeY[0]))
  {
    TouchedItSelf();
    if (Eat())
    {
      GiveFood();
      PcControl();
      Buttons();
      Control();
    }
    else //geen eten aangeraakt
    {
      PcControl();
      Buttons();
      Control();
    }
    
    u8g.firstPage();
    do {
      draw(); //teken wat in de draw functie staat
    } while ( u8g.nextPage() );

  }
  else
  {
    Dead();
  }
}

void first() {
  u8g.setFont(u8g_font_unifont);
   u8g.drawStr( 20, 35, "CreateLabz");
   
   u8g.drawStr( 17, 52, "Tutorials");
}
void second() {
  u8g.setFont(u8g_font_unifont);
  u8g.drawStr( 12, 15, "C L A S S I C");
  
  u8g.drawStr( 25, 35, "S N A K E");
  
  u8g.drawStr( 30, 55, "G A M E");
}
void clearlcd(){
    u8g.firstPage(); 
    
    do {
      
    } while( u8g.nextPage() );
}
void draw(void) //tekenen van de snake op het scherm
{
  drawSnake();
  drawFood();
}

void drawSnake()
{
  for (int i = 0; i < snakeLength; i++)
  {
    u8g.drawBox(snakeX[i], snakeY[i], 6, 6);
  }
}

void drawFood()
{
  if (OnScreen(foodX, foodY))
  {
    u8g.drawBox(foodX, foodY, 6, 6);
  }
}

bool OnScreen(int x, int y) 
{
  if (x >= 0 && x < 128 && y >= 0 && y < 64)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void Dead()
{
  u8g.firstPage();
  do {
    u8g.setFont(u8g_font_unifont);
    u8g.drawStr( 10, 30, "ARE YOU READY!");
    u8g.drawStr( 25, 50, "LET'S GO");
  } while ( u8g.nextPage() );

  // rebuild the picture after some delay
  delay(5000);
  snakeX[0] = 20;
  snakeY[0] = 20;
  snakeLength = 1;
  MLEFT = false;
  MRIGHT = false;
  MUP = false;
  MDOWN = false;

  GiveFood();
}

void GiveFood()
{
  foodX = random(6, 122);
  foodY = random(6, 58);
}

bool Eat()
{
  if (snakeX[0] == foodX && snakeY[0] == foodY)
  {
    if(snakeLength < maxSnakeLength)
    {
      snakeLength++;
      u8g.drawBox(snakeX[0], snakeY[0], 6, 6);
    }
    return true;
  }
  else
  {
    return false;
  }
}

void PcControl()
{
  if (Serial.available() > 0)
  {
    int incomingByte = Serial.read();
    char incomingChar = (char)incomingByte;

    if (incomingChar == '#')
    {
      cons = "";
      Start = true;
    }

    if (Start == true && Stop == false)
    {
      cons += incomingChar;
    }

    if (incomingChar == '%')
    {
      Stop = true;
    }

    if (Start == true && Stop == true)
    {
      Start = false;
      Stop = false;
      command = cons;
      cons = "";
    }

    if (arduinoControl == true && command == "#REMOTE_CONTROL%")
    {
      if (Createlabz != command)
      {
        Createlabz = command;
        Serial.println(command);
      }
      command = "";

      arduinoControl = false;
    }

    if (arduinoControl == false) //commands vanaf pc
    {
      if (command == "#MOVE_LEFT%" && MRIGHT != true)
      {
        MLEFT = true;
        MRIGHT = false;
        MUP = false;
        MDOWN = false;
        command = "#LEFT%";
        if (Createlabz != command)
        {
          Createlabz = command;
          Serial.println(command);
        }
      }
      else if (command == "#MOVE_RIGHT%" && MLEFT != true)
      {
        MRIGHT = true;
        MLEFT = false;
        MUP = false;
        MDOWN = false;
        command = "#RIGHT%";
        if (Createlabz != command)
        {
          Createlabz = command;
          Serial.println(command);
        }
      }
      else if (command == "#MOVE_UP%" && MDOWN != true)
      {
        MUP = true;
        MLEFT = false;
        MRIGHT = false;
        MDOWN = false;
        command = "#UP%";
        if (Createlabz != command)
        {
          Createlabz = command;
          Serial.println(command);
        }
      }
      else if (command == "#MOVE_DOWN%" && MUP != true)
      {
        MDOWN = true;
        MLEFT = false;
        MUP = false;
        MRIGHT = false;
        command = "#DOWN%";
        if (Createlabz != command)
        {
          Createlabz = command;
          Serial.println(command);
        }
      }
    }
  }
}

void Control()
{
  for(int i = snakeLength; i  > 0; i--)
  {
    snakeX[i] = snakeX[i-1];
    snakeY[i] = snakeY[i-1];
  }
  if (MLEFT == true)
  {
    snakeX[0] =  snakeX[0] - 1;
  }
  else if (MUP == true)
  {
    snakeY[0] =  snakeY[0] - 1;
  }
  else if (MDOWN == true)
  {
    snakeY[0] =  snakeY[0] + 1;
  }
  else if (MRIGHT == true)
  {
    snakeX[0] =  snakeX[0] + 1;;
  }
}

bool IsSnake(int x, int y)
{
  for (int i = 0; i < snakeLength - 1; i++)
  {
    if ((x == snakeX[i]) && (y == snakeY[i]))
    {
      return true;
    }
    else
    {
      return false;
    }
  }
}


void TouchedItSelf()
{
  for (int i = 1; i < snakeLength; i++)
  {
    if ((snakeX[0] == snakeX[i]) && (snakeY[0] == snakeY[i]))
    {
      Dead();
    }
  }
}

void Buttons()
{
  if (arduinoControl == true)
  {
    if ((digitalRead(BLEFT)) == HIGH && MRIGHT != true && MLEFT != true)
    {
      delay(200);
      if ((digitalRead(BLEFT)) == LOW)
      {
        MLEFT = true;
        MUP = false;
        MDOWN = false;
        MRIGHT = false;
        Serial.println("Left");
      }
    }
    if ((digitalRead(BUP)) == HIGH && MDOWN != true && MUP != true)
    {
      delay(200);
      if ((digitalRead(BUP)) == LOW)
      {
        MLEFT = false;
        MUP = true;
        MDOWN = false;
        MRIGHT = false;
        Serial.println("Up");
      }
    }
    if ((digitalRead(BDOWN)) == HIGH && MUP != true && MDOWN != true)
    {
      delay(200);
      if ((digitalRead(BDOWN)) == LOW)
      {
        MLEFT = false;
        MUP = false;
        MDOWN = true;
        MRIGHT = false;
        Serial.println("Down");
      }
    }
    if ((digitalRead(BRIGHT)) == HIGH && MLEFT != true && MRIGHT != true)
    {
      delay(200);
      if ((digitalRead(BRIGHT)) == LOW)
      {
        MLEFT = false;
        MUP = false;
        MDOWN = false;
        MRIGHT = true;
        Serial.println("Right");
      }
    }
  }
}

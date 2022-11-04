#include <SoftwareSerial.h>
#include <Keypad.h>
/*************************************************/
SoftwareSerial mybluetooth(2, 1);  // 2:RX 3:TX, you can choose your favourite pins.
/*************************************************/
const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {13, 12, 11, 10};
byte colPins[COLS] = {9, 8, 7, 6};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

char Keypad_char()
{
  char  customKey = customKeypad.getKey();
  return customKey;
}
/*************************************************/
// ARROW LED Display PIN
#define ARROW_pin_up  5
#define ARROW_pin_middle 4
#define ARROW_pin_down 3
/*************************************************/
// ARROW LED Display Function
void ARROW_init();
void ARROW_up();
void ARROW_down();
void ARROW_OFF();
/*************************************************/
#define _7_Seg_pin_1  A0
#define _7_Seg_pin_2  A1
#define _7_Seg_pin_3  A2
#define _7_Seg_pin_4  A3

/***********************************************/

void Display_7_seg_zero();
void Display_7_seg_one();
void Display_7_seg_two();
void Display_7_seg_three();
void Display_7_seg_four();
void Display_7_seg_five();

void _7_Seg_init();
/***********************************************/
#define ground 48
#define zero   48
#define one    49
#define two    50
#define three  51
/***********************************************/
int current_floor  = ground;
int goto_floor = ground;
/***********************************************/

/***********************************************/

void setup() {
  Serial.begin(9600);
  mybluetooth.begin(9600);
  _7_Seg_init();
  ARROW_init();
}

void loop() {
  char Keypad_char_pressed = Keypad_char();
  int Keypad_int_pressed = (Keypad_char_pressed - '0') + ground;
  
  if (mybluetooth.available())
  {
    goto_floor = mybluetooth.read();
    Serial.println(goto_floor - 48);
  }
  //if( (current_floor < goto_floor) && (goto_floor < (ground + 4)) )
  if ( (current_floor < goto_floor) && (goto_floor < (ground + 4)) || ((current_floor < (Keypad_int_pressed)) && (Keypad_int_pressed < (ground + 4))))
  {
    
    goto_up();
    current_floor = goto_floor;
  }
  
  //else if ( (current_floor > goto_floor) && (goto_floor >= ground ) )
  else if ( (current_floor > goto_floor) && (goto_floor >= ground ) || ((current_floor > (Keypad_int_pressed)) && (Keypad_int_pressed >= (ground ))))
  {
    goto_down();
    current_floor = goto_floor;
  }
}

void goto_up()
{
  ARROW_up();
  switch (current_floor)
  {
    case zero:
      Display_7_seg_zero();
      delay(2000);
      if ( current_floor == goto_floor )
        break;
      current_floor++;
    case one:
      Display_7_seg_one();
      delay(2000);
      if ( current_floor == goto_floor )
        break;
      current_floor++;
    case two:
      Display_7_seg_two();
      delay(2000);
      if ( current_floor == goto_floor )
        break;
      current_floor++;
    case three:
      Display_7_seg_three();
      delay(2000);
      if ( current_floor == goto_floor )
        break;
      current_floor++;
  }
  ARROW_OFF();
}
void goto_down()
{
  ARROW_down();
  switch (current_floor)
  {
    case three:
      Display_7_seg_three();
      delay(2000);
      if ( current_floor == goto_floor )
        break;
      current_floor--;
    case two:
      Display_7_seg_two();
      delay(2000);
      if ( current_floor == goto_floor )
        break;
      current_floor--;
    case one:
      Display_7_seg_one();
      delay(2000);
      if ( current_floor == goto_floor )
        break;
      current_floor--;
    case zero:
      Display_7_seg_zero();
      delay(2000);
      if ( current_floor == goto_floor )
        break;
      current_floor--;
  }
  ARROW_OFF();
}

/**************************************************************************/
void ARROW_init()
{
  // ARROW LED Display PIN OUTPUT
  pinMode(ARROW_pin_up, OUTPUT);
  pinMode(ARROW_pin_down, OUTPUT);
  pinMode(ARROW_pin_middle, OUTPUT);
}
void ARROW_up()
{
  digitalWrite(ARROW_pin_up, HIGH);
  digitalWrite(ARROW_pin_middle, HIGH);
  digitalWrite(ARROW_pin_down, LOW);
}
void ARROW_down()
{
  digitalWrite(ARROW_pin_up, LOW);
  digitalWrite(ARROW_pin_middle, HIGH);
  digitalWrite(ARROW_pin_down, HIGH);
}
void ARROW_OFF()
{
  digitalWrite(ARROW_pin_up, LOW);
  digitalWrite(ARROW_pin_middle , LOW);
  digitalWrite(ARROW_pin_down , LOW);
}
/**************************************************************************/
void _7_Seg_init()
{
  pinMode(_7_Seg_pin_1, OUTPUT);
  pinMode(_7_Seg_pin_2, OUTPUT);
  pinMode(_7_Seg_pin_3, OUTPUT);
  pinMode(_7_Seg_pin_4, OUTPUT);
}
void Display_7_seg_zero()
{
  digitalWrite(_7_Seg_pin_1, 0);
  digitalWrite(_7_Seg_pin_2, 0);
  digitalWrite(_7_Seg_pin_3, 0);
  digitalWrite(_7_Seg_pin_4, 0);
}
void Display_7_seg_one()
{
  digitalWrite(_7_Seg_pin_1, 1);
  digitalWrite(_7_Seg_pin_2, 0);
  digitalWrite(_7_Seg_pin_3, 0);
  digitalWrite(_7_Seg_pin_4, 0);
}
void Display_7_seg_two()
{
  digitalWrite(_7_Seg_pin_1, 0);
  digitalWrite(_7_Seg_pin_2, 1);
  digitalWrite(_7_Seg_pin_3, 0);
  digitalWrite(_7_Seg_pin_4, 0);
}
void Display_7_seg_three()
{
  digitalWrite(_7_Seg_pin_1, 1);
  digitalWrite(_7_Seg_pin_2, 1);
  digitalWrite(_7_Seg_pin_3, 0);
  digitalWrite(_7_Seg_pin_4, 0);
}
void Display_7_seg_four()
{
  digitalWrite(_7_Seg_pin_1, 0);
  digitalWrite(_7_Seg_pin_2, 0);
  digitalWrite(_7_Seg_pin_3, 1);
  digitalWrite(_7_Seg_pin_4, 0);
}
void Display_7_seg_five()
{
  digitalWrite(_7_Seg_pin_1, 1);
  digitalWrite(_7_Seg_pin_2, 0);
  digitalWrite(_7_Seg_pin_3, 1);
  digitalWrite(_7_Seg_pin_4, 0);
}

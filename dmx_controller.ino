#include <SPI.h>
#include "LCD_Driver.h"
#include "GUI_Paint.h"
#include "image.h"
#include <DMXSerial.h>
#include "Adafruit_Keypad.h"

// define your specific keypad here via PID
#define KEYPAD_PID3844
// define your pins here
// can ignore ones that don't apply
#define R1    17
#define R2    16
#define R3    15
#define R4    14
#define C1    18
#define C2    19
#define C3    20
#define C4    21
// leave this import after the above configuration
#include "keypad_config.h"

//initialize an instance of class NewKeypad
Adafruit_Keypad customKeypad = Adafruit_Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);


int master = 0;
int red = 0;
int green = 0;
int blue = 0;

int myChannels[] = {master, red, green, blue};


const int button_up = 4;
int button_up_state = 0;
const int button_down = 5;
int button_down_state = 0;
int y1_start = 160;
int y1_end = 150;

bool key_1 = false;
bool key_2 = false;
bool key_3 = false;
bool key_4 = false;
bool key_5 = false;
bool key_6 = false;
bool key_7 = false;
bool key_8 = false;
bool key_9 = false;
bool key_10 = false;
bool key_11 = false;
bool key_12 = false;
bool key_13 = false;
bool key_14 = false;
bool key_15 = false;
bool key_16 = false;

int myKeys[] = {key_1, key_2, key_3, key_4, key_5, key_6, key_7, key_8, key_9, key_10, key_11, key_12, key_13, key_14, key_15, key_16};

int channel = 1;

void setup()
{

  DMXSerial.init(DMXController);
  pinMode(button_up, OUTPUT);  
  Config_Init();
  LCD_Init();
  //LCD_Clear(WHITE);
  //LCD_SetBacklight(100);
  Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 0, BLACK);
  Paint_Clear(BLACK);
  Paint_SetRotate(180);
	Paint_DrawString_EN(10, 10, "Tiny DMX Control",        &Font20,  WHITE, WHITE);  
	//Paint_DrawString_EN(30, 34, "ABC",        &Font24,  BLUE,   CYAN);
	//Paint_DrawFloatNum (30, 58 ,987.654321,3, &Font20,  WHITE,  BLACK);
	// Paint_DrawString_CN(50,180, "微雪电子",   &Font24CN,WHITE,  RED);
 

  
	Paint_DrawRectangle(5, y1_start, 25, y1_end, WHITE ,DOT_PIXEL_1X1,DRAW_FILL_EMPTY);
  Paint_DrawRectangle(35, 160, 55, 150, RED ,DOT_PIXEL_1X1,DRAW_FILL_EMPTY);
  Paint_DrawRectangle(65, 160, 85, 150, GREEN ,DOT_PIXEL_1X1,DRAW_FILL_EMPTY);
  Paint_DrawRectangle(95, 160, 115, 150, BLUE ,DOT_PIXEL_1X1,DRAW_FILL_EMPTY);
	Paint_DrawRectangle(125, 160, 145, 150, WHITE ,DOT_PIXEL_1X1,DRAW_FILL_EMPTY);
  Paint_DrawRectangle(155, 160, 175, 150, RED ,DOT_PIXEL_1X1,DRAW_FILL_EMPTY);
  Paint_DrawRectangle(185, 160, 205, 150, GREEN ,DOT_PIXEL_1X1,DRAW_FILL_EMPTY);
  Paint_DrawRectangle(215, 160, 235, 150, BLUE ,DOT_PIXEL_1X1,DRAW_FILL_EMPTY);
	Paint_DrawRectangle(5, 300, 25, 290, WHITE ,DOT_PIXEL_1X1,DRAW_FILL_EMPTY);
  Paint_DrawRectangle(35, 300, 55, 290, RED ,DOT_PIXEL_1X1,DRAW_FILL_EMPTY);
  Paint_DrawRectangle(65, 300, 85, 290, GREEN ,DOT_PIXEL_1X1,DRAW_FILL_EMPTY);
  Paint_DrawRectangle(95, 300, 115, 290, BLUE ,DOT_PIXEL_1X1,DRAW_FILL_EMPTY);
	Paint_DrawRectangle(125, 300, 145, 290, WHITE ,DOT_PIXEL_1X1,DRAW_FILL_EMPTY);
  Paint_DrawRectangle(155, 300, 175, 290, RED ,DOT_PIXEL_1X1,DRAW_FILL_EMPTY);
  Paint_DrawRectangle(185, 300, 205, 290, GREEN ,DOT_PIXEL_1X1,DRAW_FILL_EMPTY);
  Paint_DrawRectangle(215, 300, 235, 290, BLUE ,DOT_PIXEL_1X1,DRAW_FILL_EMPTY);
  
	Paint_DrawLine  (15, 160, 15, 40,    WHITE ,DOT_PIXEL_2X2,LINE_STYLE_SOLID);
	Paint_DrawLine  (45, 160, 45, 40,    RED ,DOT_PIXEL_2X2,LINE_STYLE_SOLID);
  Paint_DrawLine  (75, 160, 75, 40,    GREEN ,DOT_PIXEL_2X2,LINE_STYLE_SOLID);
  Paint_DrawLine  (105, 160, 105, 40,    BLUE ,DOT_PIXEL_2X2,LINE_STYLE_SOLID);
	Paint_DrawLine  (135, 160, 135, 40,    WHITE ,DOT_PIXEL_2X2,LINE_STYLE_SOLID);
	Paint_DrawLine  (165, 160, 165, 40,    RED ,DOT_PIXEL_2X2,LINE_STYLE_SOLID);
  Paint_DrawLine  (195, 160, 195, 40,    GREEN ,DOT_PIXEL_2X2,LINE_STYLE_SOLID);
  Paint_DrawLine  (225, 160, 225, 40,    BLUE ,DOT_PIXEL_2X2,LINE_STYLE_SOLID);
	Paint_DrawLine  (15, 300, 15, 180,    WHITE ,DOT_PIXEL_2X2,LINE_STYLE_SOLID);
	Paint_DrawLine  (45, 300, 45, 180,    RED ,DOT_PIXEL_2X2,LINE_STYLE_SOLID);
  Paint_DrawLine  (75, 300, 75, 180,    GREEN ,DOT_PIXEL_2X2,LINE_STYLE_SOLID);
  Paint_DrawLine  (105, 300, 105, 180,    BLUE ,DOT_PIXEL_2X2,LINE_STYLE_SOLID);
	Paint_DrawLine  (135, 300, 135, 180,    WHITE ,DOT_PIXEL_2X2,LINE_STYLE_SOLID);
	Paint_DrawLine  (165, 300, 165, 180,    RED ,DOT_PIXEL_2X2,LINE_STYLE_SOLID);
  Paint_DrawLine  (195, 300, 195, 180,    GREEN ,DOT_PIXEL_2X2,LINE_STYLE_SOLID);
  Paint_DrawLine  (225, 300, 225, 180,    BLUE ,DOT_PIXEL_2X2,LINE_STYLE_SOLID);
	// Paint_DrawCircle(150,100,  25,        BLUE    ,DOT_PIXEL_2X2,DRAW_FILL_EMPTY);
	// Paint_DrawCircle(180,100,  25,        BLACK   ,DOT_PIXEL_2X2,DRAW_FILL_EMPTY);
	// Paint_DrawCircle(210,100,  25,        RED     ,DOT_PIXEL_2X2,DRAW_FILL_EMPTY);
	// Paint_DrawCircle(165,125,  25,        YELLOW  ,DOT_PIXEL_2X2,DRAW_FILL_EMPTY);
	// Paint_DrawCircle(195,125,  25,        GREEN   ,DOT_PIXEL_2X2,DRAW_FILL_EMPTY);
  
  // Paint_DrawImage(gImage_70X70, 20, 80, 70, 70); 
  Serial.begin(9600);
  customKeypad.begin();
}
void loop()
{
  int brightness;
  Paint_DrawString_EN(7, 165, "",        &Font16,  BLACK, BLACK);
  Paint_DrawString_EN(7, 165, channel,        &Font16,  WHITE, WHITE);
  Paint_DrawString_EN(100, 165, "",        &Font16,  BLACK, BLACK);
  Paint_DrawString_EN(100, 165, myChannels[channel - 1],        &Font16,  WHITE, WHITE);
  DMXSerial.write(channel, myChannels[channel - 1]);
  Serial.println(channel);
  Serial.println(myChannels[channel - 1]);

  keypadEvent e = customKeypad.read();
  //Serial.print((char)e.bit.KEY);
  if(e.bit.EVENT == KEY_JUST_PRESSED) Serial.println(" pressed");
  else if(e.bit.EVENT == KEY_JUST_RELEASED) Serial.println(" released");


    // read the state of the pushbutton value:
  button_up_state = digitalRead(button_up);
  button_down_state = digitalRead(button_down);

  for (int i = 1; i <= 16; i++) {
    if ((char)e.bit.KEY == 'i' && e.bit.EVENT == KEY_JUST_PRESSED) {
      myKeys[i - 1] = true;
    }
    if ((char)e.bit.KEY == 'i' && e.bit.EVENT == KEY_JUST_RELEASED) {
      myKeys[i - 1] = false;
    }
  }

  // if ((char)e.bit.KEY == '1' && e.bit.EVENT == KEY_JUST_PRESSED) {
  //   key_1 = true;
  // }
  // if ((char)e.bit.KEY == '1' && e.bit.EVENT == KEY_JUST_RELEASED) {
  //   key_1 = false;
  // }
  // if ((char)e.bit.KEY == '2' && e.bit.EVENT == KEY_JUST_PRESSED) {
  //   key_2 = true;
  // }
  // if ((char)e.bit.KEY == '2' && e.bit.EVENT == KEY_JUST_RELEASED) {
  //   key_2 = false;
  // }
  // if ((char)e.bit.KEY == '3' && e.bit.EVENT == KEY_JUST_PRESSED) {
  //   key_3 = true;
  // }
  // if ((char)e.bit.KEY == '3' && e.bit.EVENT == KEY_JUST_RELEASED) {
  //   key_3 = false;
  // }
  // if ((char)e.bit.KEY == '4' && e.bit.EVENT == KEY_JUST_PRESSED) {
  //   key_4 = true;
  // }
  // if ((char)e.bit.KEY == '4' && e.bit.EVENT == KEY_JUST_RELEASED) {
  //   key_4 = false;
  // }
    
  // if ((char)e.bit.KEY == '5' && e.bit.EVENT == KEY_JUST_PRESSED) {
  //   key_5 = true;
  // }
  // if ((char)e.bit.KEY == '5' && e.bit.EVENT == KEY_JUST_RELEASED) {
  //   key_5 = false;
  // }
  // if ((char)e.bit.KEY == '6' && e.bit.EVENT == KEY_JUST_PRESSED) {
  //   key_6 = true;
  // }
  // if ((char)e.bit.KEY == '6' && e.bit.EVENT == KEY_JUST_RELEASED) {
  //   key_6 = false;
  // }
  // if ((char)e.bit.KEY == '7' && e.bit.EVENT == KEY_JUST_PRESSED) {
  //   key_7 = true;
  // }
  // if ((char)e.bit.KEY == '7' && e.bit.EVENT == KEY_JUST_RELEASED) {
  //   key_7 = false;
  // }
  // if ((char)e.bit.KEY == '8' && e.bit.EVENT == KEY_JUST_PRESSED) {
  //   key_8 = true;
  // }
  // if ((char)e.bit.KEY == '8' && e.bit.EVENT == KEY_JUST_RELEASED) {
  //   key_8 = false;
  // }
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:

  if (key_1 == true && myChannels[channel - 1] < 255) {
    y1_start += 1;
    y1_end += 1;
    if (myChannels[channel - 1] > 0){
      myChannels[channel - 1] -= 1;   
 
    };          
    Paint_DrawRectangle(5, y1_start - 10, 25, y1_end - 10, BLACK ,DOT_PIXEL_1X1,DRAW_FILL_EMPTY);
    Paint_DrawLine  (15, y1_start - 10, 15, y1_end - 10,    WHITE ,DOT_PIXEL_2X2,LINE_STYLE_SOLID); 
    Paint_DrawRectangle(5, y1_start, 25, y1_end, WHITE ,DOT_PIXEL_1X1,DRAW_FILL_EMPTY);         
  }  
  if (key_2 == true && myChannels[channel - 1] > -1)  {  
    y1_start -= 1;
    y1_end -= 1;
    if (myChannels[channel - 1] < 255){
      myChannels[channel - 1] += 1;      
   
    };             
    Paint_DrawRectangle(5, y1_start + 10, 25, y1_end + 10, BLACK ,DOT_PIXEL_1X1,DRAW_FILL_EMPTY);
    Paint_DrawLine  (15, y1_start + 10, 15, y1_end + 10,    WHITE ,DOT_PIXEL_2X2,LINE_STYLE_SOLID); 
    Paint_DrawRectangle(5, y1_start, 25, y1_end, WHITE ,DOT_PIXEL_1X1,DRAW_FILL_EMPTY);    
  };
  if ((char)e.bit.KEY == '5' && e.bit.EVENT == KEY_JUST_PRESSED && channel > 1)  {  
    channel -= 1;
    };    
  if ((char)e.bit.KEY == '6' && e.bit.EVENT == KEY_JUST_PRESSED && channel >= 1)  {  
    channel += 1;
    };        

  // RGBW Light Fixture 1
  customKeypad.tick();  
      
}



/*********************************************************************************************************
  END FILE
*********************************************************************************************************/

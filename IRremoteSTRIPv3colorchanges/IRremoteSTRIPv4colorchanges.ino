
#include <FastLED.h>
#include <IRremote.h>

#define NUM_LEDS  6  // <<--
#define Num_Strip1 6  // Values the Same



#define RECV_PIN 10
//#define BRIGHTNESS 180 /* Control the brightness of your leds */
#define SATURATION 0   /* Control the saturation of your leds */

int BRIGHT = 180;

uint8_t hue = 0;
CRGB Strip1[Num_Strip1];

IRrecv irrecv(RECV_PIN);
decode_results results;

int Program = 0;
int maxProgram = 2;
int Num = 0;
int Run = 0;
int Select = 0;
int Program0Delay = 100;
int Program1Delay = 100;
int Program2Delay = 100;
int Program3Delay = 100;
int Program4Delay = 100;

unsigned long DelayTime = 0;

bool Active = false;

int brightactive = 0;

CRGB leds[NUM_LEDS];
uint8_t colorIndex[NUM_LEDS];

uint8_t paletteIndex = 0;

DEFINE_GRADIENT_PALETTE(heatmap_gp) { 
  0, 255, 0, 0,
  80, 255, 0, 20,
  130, 255, 0, 50,
  255, 255, 255, 255
};

CRGBPalette16 myPal = heatmap_gp;

void setup()
{
  FastLED.addLeds<NEOPIXEL,12>(Strip1, Num_Strip1);
 // FastLED.addLeds<WS2812B,12,GRB>(Strip1, Num_Strip1); 
  FastLED.setBrightness(BRIGHT);
  Serial.begin(9600);
  irrecv.enableIRIn();


   
  }




void translateIR()
{
  switch(results.value)
  {
    case 0x20DF40BF: ProgramUP(); ClearStrip(); Active = true; Serial.println("VOL+");           break;
    case 0xB4B4629D: ClearStrip(); break;
    case 0x20DFC03F: ProgramDown(); ClearStrip(); Active = true; Serial.println("VOL-");         break;
    case 0xB4B422DD: Num = 0; Program = 0; Run = 0; ClearStrip(); Active = true; Serial.println("0");     break;
    case 0xB4B4DC23: Num = 0; Program = 1; Run = 0; ClearStrip(); Active = true; Serial.println("1");     break;
    case 0xB4B43CC3: Num = 0; Program = 2; ClearStrip(); Active = true; Serial.println("2");     break;
    case 0xB4B4BC43: SlowRainbow(); Serial.println("3");     break;  //StaticColour(0); Program = 6 && Program = 3 && 
    case 0xB4B47C83: BlueHue();  Serial.println("4");     break; // StaticColour(100); Program = 6 &&Program = 4 &&
    case 0xB4B4FC03: PinkOrange(); Serial.println("5");     break; //StaticColour(155); Program = 6 &&
    case 0xB4B402FD: outinlight(); Serial.println("6");     break;
    case 0xB4B4827D: christmas(); Serial.println("7");     break;
    case 0xB4B442BD: ChristmasFade(); Serial.println("8");     break;
    case 0xB4B4C23D: EarthDay(); Serial.println("9");     break;
    case 0xB4B40CF3: ClearStrip(); Serial.println("OFF"); break;
    case 0xB4B48C73: ColorPicker(); Serial.println("Play"); break;
    case 0xB4B41CE3: Serial.println("Pause"); break;
    case 0x77E120E8:  Num = 0; Program = 0; Run = 0; ClearStrip(); Active = true; Serial.println("0"); break; //apple remote



   case 0xB4B4F20D: red(); Serial.println("red"); break;
   case 0xB4B40AF5: orange(); Serial.println("orange"); break;
   case 0xB4B432CD: yellow(); Serial.println("yellow"); break;
   case 0xB4B46A95: green(); Serial.println("green"); break;
   case 0xB4B48679: cyan(); Serial.println("cyan"); break;
   case 0xB4B446B9: blue(); Serial.println("blue"); break;
   case 0xB4B4EA15: purple(); Serial.println("purple"); break;
   case 0xB4B426D9: pink(); Serial.println("pink"); break;
   case 0xB4B4EF10: white(); Serial.println("white"); break;
   case 0xB4B4CA35: lime(); Serial.println("lime"); break;
   case 0xB4B4AA55: magenta();  Serial.println("magenta"); break;

   case 0x20DF807F: 
      Serial.println("BRIGHTNESS CONTROL -");
      if (brightactive == 0) {
        BRIGHT=225;
        brightactive=1;
      }
      else if (brightactive == 1) {
        BRIGHT=170;
        brightactive=2;
      }
      else if (brightactive == 2) {
        BRIGHT=130;
        brightactive=3;
      }
      else if (brightactive == 3) {
        BRIGHT=90;
        brightactive=4;
      }
      else if (brightactive ==4) {
        BRIGHT=50;
        brightactive=5;
      }
      else if (brightactive == 5) {
        BRIGHT=20;
        brightactive=6;
      }
      else if (brightactive == 6) {
        BRIGHT=5;
        brightactive=0;
      }
      FastLED.setBrightness(BRIGHT);
      Serial.println(BRIGHT);
   break;
   
   case 0x20DF00FF: 
      Serial.println("BRIGHTNESS CONTROL +");
      if (brightactive == 0) {
        BRIGHT=225;
        brightactive=6;
      }
      else if (brightactive == 1) {
        BRIGHT=170;
        brightactive=0;
      }
      else if (brightactive == 2) {
        BRIGHT=130;
        brightactive=1;
      }
      else if (brightactive == 3) {
        BRIGHT=90;
        brightactive=2;
      }
      else if (brightactive ==4) {
        BRIGHT=50;
        brightactive=3;
      }
      else if (brightactive == 5) {
        BRIGHT=20;
        brightactive=4;
      }
      else if (brightactive == 6) {
        BRIGHT=5;
        brightactive=5;
      }
      FastLED.setBrightness(BRIGHT);
      Serial.println(BRIGHT);
   break;

    
 
    case 0x4AB0F7B6: Serial.println("Disregard"); break;
    default:
      Serial.println("other Button");
  }
  
}

void christmas() {
  Strip1[0].setRGB(255,0,0);
  Strip1[1].setRGB(0,0,255);
  Strip1[2].setRGB(255,0,0);
  Strip1[3].setRGB(0,0,255); 
  Strip1[4].setRGB(255,0,0);
  Strip1[5].setRGB(0,0,255);
  FastLED.show();

  
}
void ColorPicker() {
   
  
}


void BlueHue() {
  Strip1[0].setRGB(255,2,0);
  Strip1[1].setRGB(255,25,0);
  Strip1[2].setRGB(0,255,0);
  Strip1[3].setRGB(255,0,65); 
  Strip1[4].setRGB(0,0,255);
  Strip1[5].setRGB(255,175,0);
  FastLED.show();

  //CHSV
}

void PinkOrange() {
  Strip1[0].setRGB(255,14,14);
  Strip1[1].setRGB(255,0,20);
  Strip1[2].setRGB(255,14,14);
  Strip1[3].setRGB(255,0,20);
  Strip1[4].setRGB(255,14,14);
  Strip1[5].setRGB(255,0,20);
  FastLED.show();
  
}
void outinlight() {
  Strip1[0].setRGB(255,0,65);
  Strip1[1].setRGB(255,180,255);
  Strip1[2].setRGB(255,0,65);
  Strip1[3].setRGB(255,180,255);
  Strip1[4].setRGB(225,0,65);
  Strip1[5].setRGB(255,180,255);
  FastLED.show();
}

void WhiteBlue() {
  Strip1[0].setRGB(255,255,255);
  Strip1[1].setRGB(0,255,0);
  Strip1[2].setRGB(255,255,255);
  Strip1[3].setRGB(0,255,0);
  Strip1[4].setRGB(255,255,255);
  Strip1[5].setRGB(0,255,0);
  FastLED.show();
}
void EarthDay() {
  Strip1[0].setRGB(0,0,255);
  Strip1[1].setRGB(0,255,0);
  Strip1[2].setRGB(0,0,255);
  Strip1[3].setRGB(0,255,0);
  Strip1[4].setRGB(0,0,255);
  Strip1[5].setRGB(0,255,0);
  FastLED.show();
}

void ChristmasFade() {
Strip1[0].setRGB(255, 0, 0); // Red
Strip1[1].setRGB(0, 0, 255); // Green
Strip1[2].setRGB(225 ,0 , 50); // Yellow
Strip1[3].setRGB(255, 0, 0); // Red
Strip1[4].setRGB(0, 0, 255); // Green
Strip1[5].setRGB(225 ,0 , 50); // Yellow
FastLED.show();
}

void red() {
  fill_solid(Strip1, Num_Strip1, CRGB(255,0, 0));
  FastLED.show();
}
 void orange() {
  fill_solid(Strip1, Num_Strip1, CRGB(255, 0, 20));
  FastLED.show();
}
void yellow() {
  fill_solid(Strip1, Num_Strip1, CRGB(225 ,0 , 50));
  FastLED.show();
}
void green() {
  fill_solid(Strip1, Num_Strip1, CRGB(0 ,0 , 255));
  FastLED.show();
}
void cyan() {
  fill_solid(Strip1, Num_Strip1, CRGB(0 ,255 , 255));
  FastLED.show();
}
void blue() {
  fill_solid(Strip1, Num_Strip1, CRGB(0 ,255 , 0));
  FastLED.show();
}
void purple() {
  fill_solid(Strip1, Num_Strip1, CRGB(255 ,255 , 0));
  FastLED.show();
}
void pink() {
  fill_solid(Strip1, Num_Strip1, CRGB(255, 80, 10));
  FastLED.show();
}
void lime() {
  fill_solid(Strip1, Num_Strip1, CRGB(30,8,47));
  FastLED.show();
}
void magenta() {
  fill_solid(Strip1, Num_Strip1, CRGB(5,35,12));
  FastLED.show();
}

void white() {

  fill_solid(Strip1, Num_Strip1, CRGB(255,255,255));
  FastLED.show();
    
}
 
void Palette_Purple() {
  fill_palette(Strip1, NUM_LEDS, paletteIndex, 255 / NUM_LEDS, myPal, 255, LINEARBLEND);

  FastLED.show();
 
}

void SlowRainbow() {
   #define thisSpeed 5
    #define deltahue 10
    
   uint8_t thisHue = beat8(thisSpeed,255);                     // A simple rainbow march.
  
   fill_rainbow(Strip1, Num_Strip1, thisHue, deltahue);  
   
    FastLED.show();
}


void ClearStrip()
{
  Num = 0;
  for(; Num < Num_Strip1; Num++)
  {
    Strip1[Num] = CHSV(255, 255, 0);
  }
  FastLED.show();
  Num = 0;
}

void ProgramUP()
{
  Num = 0;
  Run = 0;
  if(Program < maxProgram)
  {
    Program++;
    for(; Num < Num_Strip1; Num++)
    {
      Strip1[Num] = CHSV(255, 255, 0);
    }
    FastLED.show();
  }
  else
  {
    Program = 0;
    for(; Num < Num_Strip1; Num++)
    {
      Strip1[Num] = CHSV(255, 255, 0);
    }
    FastLED.show();
  }
}

void ProgramDown()
{
  Num = 0;
  Run = 0;
  if(Program > 0)  {
    Program--;
    for(; Num < Num_Strip1; Num++)
    {
      Strip1[Num] = CHSV(255, 255, 0);
    }
    FastLED.show();
  }
  else
  {
    Program = maxProgram;
     for(; Num < Num_Strip1; Num++)
    {
      Strip1[Num] = CHSV(255, 255, 0);
    }
    FastLED.show();
  }
}

void StaticColour(int colour) {
  Num = 0;
  for(; Num < Num_Strip1; Num++)
  {
    Strip1[Num] = CHSV(colour, 255, 255);
  }
  FastLED.show();
}

void loop()
{
if(irrecv.decode(&results))
{
  Run = 0;
  Active = false;
  translateIR();
  Serial.println(results.value, HEX);
  irrecv.resume();
}

  if(Active == true && Program == 0 && Run == 0 && millis() - DelayTime >= Program0Delay)  {
    DelayTime = millis();

    #define thisSpeed 10
    #define deltahue 20
    
   uint8_t thisHue = beat8(thisSpeed,255);                     // A simple rainbow march.
  
   fill_rainbow(Strip1, Num_Strip1, thisHue, deltahue);  
   
    FastLED.show();
 
  }

  if(Active == true && Program == 0 && Run == 1 && millis() - DelayTime >= Program0Delay)  {
    DelayTime = millis();
    Strip1[Num] = CHSV(155, 255, 255);
    Num++;
    if(Num > Num_Strip1) {
      Run = 2;
      Num = 0;
    }
    FastLED.show();
  }

  if(Active == true && Program == 0 && Run == 2 && millis() - DelayTime >= Program0Delay)  {
    DelayTime = millis();
    Strip1[Num] = CHSV(158, 92, 94);
    Num++;
    if(Num > Num_Strip1)  {
      Run = 3;
      Num = Num_Strip1 - 1;
    }
    FastLED.show();
  }

  if(Active == true && Program == 0 && Run == 3 && millis() - DelayTime >= Program0Delay)  {
    DelayTime = millis();
    Strip1[Num] = CHSV(255, 255, 255);
    Num--;
    if(Num < 0)  {
      Run = 4;
      Num = Num_Strip1 - 1;
    }
    FastLED.show();
  }

  if(Active == true && Program == 0 && Run == 4 && millis() - DelayTime >= Program0Delay)  {
    DelayTime = millis();
    Strip1[Num] = CHSV(155, 255, 255);
    Num--;
    if(Num < 0)  {
      Run = 5;
      Num = Num_Strip1 - 1;
    }
    FastLED.show();
  }

  if(Active == true && Program == 0 && Run == 5 && millis() - DelayTime >= Program0Delay)  {
    DelayTime = millis();
    Strip1[Num] = CHSV(100, 255, 255);
    Num--;
    if(Num < 0)  {
      Run = 0;
      Num = 0;
    }
    FastLED.show();
  }

  if(Active == true && Program == 1 && Run == 0 && millis() - DelayTime >= Program1Delay)  {
    DelayTime = millis();
    Strip1[Num] = CHSV(255, 255, 255);
    Num++;
    Strip1[Num] = CHSV(155, 255, 255);
    if(Num >= Num_Strip1 - 1) {
      Run = 1;
    }
    FastLED.show();
  }
 
  if(Active == true && Program == 1 && Run == 1 && millis() - DelayTime >= Program1Delay)  {
    DelayTime = millis();
    Strip1[Num] = CHSV(255, 255, 255);
    Num--;
    Strip1[Num] = CHSV(155, 255, 255);
    if(Num <= 0)  {
      Run = 0;
    }
    FastLED.show();
  }

  if(Active == true && Program == 2 && millis() - DelayTime >= Program2Delay)  {
    Palette_Purple();
  }



}

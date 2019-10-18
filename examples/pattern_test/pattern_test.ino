#include <PxMatrix.h>
#include <Ticker.h>

Ticker display_ticker;
#define P_LAT 16
#define P_A 5
#define P_B 4
#define P_C 15
#define P_D 12`
#define P_E 0
#define P_OE 2

PxMATRIX display(32,16,P_LAT, P_OE,P_A,P_B,P_C);

static const uint8_t PROGMEM gamma_table[] = {
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,
  0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
  0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
  0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
  0x01,0x01,0x01,0x01,0x01,0x01,0x02,0x02,
  0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,
  0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,
  0x02,0x02,0x02,0x02,0x02,0x03,0x03,0x03,
  0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,
  0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x04,
  0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,
  0x04,0x04,0x04,0x04,0x04,0x04,0x05,0x05,
  0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,
  0x05,0x05,0x05,0x06,0x06,0x06,0x06,0x06,
  0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x07,
  0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,
  0x07,0x07,0x08,0x08,0x08,0x08,0x08,0x08,
  0x08,0x08,0x08,0x08,0x09,0x09,0x09,0x09,
  0x09,0x09,0x09,0x09,0x09,0x0a,0x0a,0x0a,
  0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,0x0b,0x0b,
  0x0b,0x0b,0x0b,0x0b,0x0b,0x0b,0x0c,0x0c,
  0x0c,0x0c,0x0c,0x0c,0x0c,0x0c,0x0d,0x0d,
  0x0d,0x0d,0x0d,0x0d,0x0d,0x0e,0x0e,0x0e,
  0x0e,0x0e,0x0e,0x0e,0x0f,0x0f,0x0f,0x0f
};

#define BLACK display.color565(0, 0, 0)
#define WHITE display.color565(255, 255, 255)
#define SHOWTIME 30
#define ANIMSPEED 150

void display_updater(){
  // display.displayTestPattern(70);
  // display.displayTestPixel(70);
  display.display(SHOWTIME);
}

uint16_t myCYAN = display.color565(127, 0, 255);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  display.begin(8);
  display.flushDisplay();
  display.setTextColor(myCYAN);
  display.setCursor(2,0);
  display.setFastUpdate(true);
  display.print("Pixel");
  Serial.println("hello");

  // display_ticker.attach(0.002, display_updater);
  display_ticker.attach_ms(2, display_updater);
  test();

  delay(2000);
}

void test(){
  Serial.println("running gfx test");
// Clear the buffer.
  display.clearDisplay();

  // draw a single pixel
  display.drawPixel(10, 10, WHITE);
  // Show the display buffer on the hardware.
  // NOTE: You _must_ call display after making any drawing commands
  // to make them visible on the display hardware!
  // display.display(SHOWTIME);
  delay(2000);
  display.clearDisplay();

  // plasma
  // plasma();
  // delay(2000);
  // display.clearDisplay();

  display_scrollText();
  delay(2000);
  display.clearDisplay();

  // draw many lines
  testdrawline();
  // display.display(SHOWTIME);
  delay(2000);
  display.clearDisplay();

  // draw rectangles
  testdrawrect();
  // display.display(SHOWTIME);
  delay(2000);
  display.clearDisplay();

  // draw multiple rectangles
  testfillrect();
  // display.display(SHOWTIME);
  delay(2000);
  display.clearDisplay();

  // draw mulitple circles
  testdrawcircle();
  // display.display(SHOWTIME);
  delay(2000);
  display.clearDisplay();

  // draw a white circle, 10 pixel radius
  display.fillCircle(display.width()/2, display.height()/2, 10, WHITE);
  // display.display(SHOWTIME);
  delay(2000);
  display.clearDisplay();

  testdrawroundrect();
  delay(2000);
  display.clearDisplay();

  testfillroundrect();
  delay(2000);
  display.clearDisplay();

  testdrawtriangle();
  delay(2000);
  display.clearDisplay();
   
  testfilltriangle();
  delay(2000);
  display.clearDisplay();

  // draw the first ~12 characters in the font
  testdrawchar();
  // display.display(SHOWTIME);
  delay(2000);
  display.clearDisplay();

  // draw scrolling text
  // testscrolltext();
  // delay(2000);
  // display.clearDisplay();

  // text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Hello, world!");
  display.setTextColor(BLACK, WHITE); // 'inverted' text
  display.println(3.141592);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.print("0x"); display.println(0xDEADBEEF, HEX);
  // display.display(SHOWTIME);
  display.setTextSize(1);
  delay(2000);
}

void testdrawchar(void) {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);

  for (uint8_t i=0; i < 168; i++) {
    if (i == '\n') continue;
    display.write(i);
    if ((i > 0) && (i % 21 == 0))
      display.println();
  }    
  // display.display(SHOWTIME);
  delay(ANIMSPEED);
}

void testdrawcircle(void) {
  for (int16_t i=0; i<display.height(); i+=2) {
    display.drawCircle(display.width()/2, display.height()/2, i, WHITE);
    // display.display(SHOWTIME);
    delay(ANIMSPEED);
  }
}

void testfillrect(void) {
  uint8_t color = 1;
  for (int16_t i=0; i<display.height()/2; i+=3) {
    // alternate colors
    display.fillRect(i, i, display.width()-i*2, display.height()-i*2, color%2);
    // display.display(SHOWTIME);
    delay(ANIMSPEED);
    color++;
  }
}

void testdrawtriangle(void) {
  for (int16_t i=0; i<min(display.width(),display.height())/2; i+=5) {
    display.drawTriangle(display.width()/2, display.height()/2-i,
                     display.width()/2-i, display.height()/2+i,
                     display.width()/2+i, display.height()/2+i, WHITE);
    // display.display(SHOWTIME);
    delay(ANIMSPEED);
  }
}

void testfilltriangle(void) {
  uint8_t color = WHITE;
  for (int16_t i=min(display.width(),display.height())/2; i>0; i-=5) {
    display.fillTriangle(display.width()/2, display.height()/2-i,
                     display.width()/2-i, display.height()/2+i,
                     display.width()/2+i, display.height()/2+i, WHITE);
    if (color == WHITE) color = BLACK;
    else color = WHITE;
    // display.display(SHOWTIME);
    delay(ANIMSPEED);
  }
}

void testdrawroundrect(void) {
  for (int16_t i=0; i<display.height()/2-2; i+=2) {
    display.drawRoundRect(i, i, display.width()-2*i, display.height()-2*i, display.height()/4, WHITE);
    // display.display(SHOWTIME);
    delay(ANIMSPEED);
  }
}

void testfillroundrect(void) {
  uint8_t color = WHITE;
  for (int16_t i=0; i<display.height()/2-2; i+=2) {
    display.fillRoundRect(i, i, display.width()-2*i, display.height()-2*i, display.height()/4, color);
    if (color == WHITE) color = BLACK;
    else color = WHITE;
    // display.display(SHOWTIME);
    delay(ANIMSPEED);
  }
}
   
void testdrawrect(void) {
  for (int16_t i=0; i<display.height()/2; i+=2) {
    display.drawRect(i, i, display.width()-2*i, display.height()-2*i, WHITE);
    // display.display(SHOWTIME);
    delay(ANIMSPEED);
  }
}

void testdrawline() {  
  for (int16_t i=0; i<display.width(); i+=4) {
    display.drawLine(0, 0, i, display.height()-1, WHITE);
    // display.display(SHOWTIME);
    delay(ANIMSPEED);
  }
  for (int16_t i=0; i<display.height(); i+=4) {
    display.drawLine(0, 0, display.width()-1, i, WHITE);
    // display.display(SHOWTIME);
    delay(ANIMSPEED);
  }
  delay(250);
  
  display.clearDisplay();
  for (int16_t i=0; i<display.width(); i+=4) {
    display.drawLine(0, display.height()-1, i, 0, WHITE);
    // display.display(SHOWTIME);
    delay(ANIMSPEED);
  }
  for (int16_t i=display.height()-1; i>=0; i-=4) {
    display.drawLine(0, display.height()-1, display.width()-1, i, WHITE);
    // display.display(SHOWTIME);
    delay(ANIMSPEED);
  }
  delay(250);
  
  display.clearDisplay();
  for (int16_t i=display.width()-1; i>=0; i-=4) {
    display.drawLine(display.width()-1, display.height()-1, i, 0, WHITE);
    // display.display(SHOWTIME);
    delay(ANIMSPEED);
  }
  for (int16_t i=display.height()-1; i>=0; i-=4) {
    display.drawLine(display.width()-1, display.height()-1, 0, i, WHITE);
    // display.display(SHOWTIME);
    delay(ANIMSPEED);
  }
  delay(250);

  display.clearDisplay();
  for (int16_t i=0; i<display.height(); i+=4) {
    display.drawLine(display.width()-1, 0, 0, i, WHITE);
    // display.display(SHOWTIME);
    delay(ANIMSPEED);
  }
  for (int16_t i=0; i<display.width(); i+=4) {
    display.drawLine(display.width()-1, 0, i, display.height()-1, WHITE); 
    // display.display(SHOWTIME);
    delay(ANIMSPEED);
  }
  delay(250);
}

void plasma(){
  int      x, y, hue;
  float    dx, dy, d;
  uint8_t  sat, val;
  uint16_t c;

  for(y=0; y < display.width(); y++) {
    dy = 15.5 - (float)y;
    for(x=0; x < display.height(); x++) {
      dx = 15.5 - (float)x;
      d  = dx * dx + dy * dy;
      if(d <= (16.5 * 16.5)) { // Inside the circle(ish)?
        hue = (int)((atan2(-dy, dx) + PI) * 1536.0 / (PI * 2.0));
        d = sqrt(d);
        if(d > 15.5) {
          // Do a little pseudo anti-aliasing along perimeter
          sat = 255;
          val = (int)((1.0 - (d - 15.5)) * 255.0 + 0.5);
        } else
        {
          // White at center
          sat = (int)(d / 15.5 * 255.0 + 0.5);
          val = 255;
        }
        c = ColorHSV(hue, sat, val, true);
      } else {
        c = 0;
      }
      display.drawPixel(x, y, c);
    }
  }
  delay(ANIMSPEED);
}

uint16_t ColorHSV(
  long hue, uint8_t sat, uint8_t val, boolean gflag) {

  uint8_t  r, g, b, lo;
  uint16_t s1, v1;

  // Hue
  hue %= 1536;             // -1535 to +1535
  if(hue < 0) hue += 1536; //     0 to +1535
  lo = hue & 255;          // Low byte  = primary/secondary color mix
  switch(hue >> 8) {       // High byte = sextant of colorwheel
    case 0 : r = 255     ; g =  lo     ; b =   0     ; break; // R to Y
    case 1 : r = 255 - lo; g = 255     ; b =   0     ; break; // Y to G
    case 2 : r =   0     ; g = 255     ; b =  lo     ; break; // G to C
    case 3 : r =   0     ; g = 255 - lo; b = 255     ; break; // C to B
    case 4 : r =  lo     ; g =   0     ; b = 255     ; break; // B to M
    default: r = 255     ; g =   0     ; b = 255 - lo; break; // M to R
  }

  // Saturation: add 1 so range is 1 to 256, allowig a quick shift operation
  // on the result rather than a costly divide, while the type upgrade to int
  // avoids repeated type conversions in both directions.
  s1 = sat + 1;
  r  = 255 - (((255 - r) * s1) >> 8);
  g  = 255 - (((255 - g) * s1) >> 8);
  b  = 255 - (((255 - b) * s1) >> 8);

  // Value (brightness) & 16-bit color reduction: similar to above, add 1
  // to allow shifts, and upgrade to int makes other conversions implicit.
  v1 = val + 1;
  if(gflag) { // Gamma-corrected color?
    r = pgm_read_byte(&gamma_table[(r * v1) >> 8]); // Gamma correction table maps
    g = pgm_read_byte(&gamma_table[(g * v1) >> 8]); // 8-bit input to 4-bit output
    b = pgm_read_byte(&gamma_table[(b * v1) >> 8]);
  } else { // linear (uncorrected) color
    r = (r * v1) >> 12; // 4-bit results
    g = (g * v1) >> 12;
    b = (b * v1) >> 12;
  }
  return (r << 12) | ((r & 0x8) << 8) | // 4/4/4 -> 5/6/5
         (g <<  7) | ((g & 0xC) << 3) |
         (b <<  1) | ( b        >> 3);
}


void display_scrollText() {
    display.clearDisplay();
    display.setTextWrap(false);  // we don't wrap text so it scrolls nicely
    display.setTextSize(1);
    display.setRotation(0);
    for (int8_t x=7; x>=-42; x--) {
        display.clearDisplay();
        display.setCursor(x,0);
        // display.setTextColor(LED_GREEN_HIGH);
        display.print("Hello");
        if (display.height()>11) {
            display.setCursor(-20-x,display.height()-7);
            // display.setTextColor(LED_ORANGE_HIGH);
            display.print("World");
        }
        // display.show();
        delay(ANIMSPEED);
    }

    display.setRotation(3);
    // display.setTextColor(LED_BLUE_HIGH);
    for (int8_t x=7; x>=-45; x--) {
        display.clearDisplay();
        display.setCursor(x,display.width()/2-4);
        display.print("Rotate");
        // display.show();
        delay(ANIMSPEED);
    }
    display.setRotation(0);
    display.setCursor(0,0);
    // display.show();
}

void loop(){
  // Serial.println(micros());
  display.clearDisplay();
  display.setCursor(2,0);
  display.print(millis());
  delay(100);
}

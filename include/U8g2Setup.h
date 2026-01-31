#ifndef ug2Setup_h
#define ug2Setup_h
#include <U8g2lib.h>

// Create an instance of the U8G2 display
// Using SSD1306 72x40 display with hardware I2C
// Reset pin not used, clock on GPIO 6, data on GPIO 5
// Adjust pins as necessary for your setup
U8G2_SSD1306_72X40_ER_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ 6, /* data=*/ 5);

// Display layout parameters
// Adjust these values based on your display and font size
//  Row height for text lines
//  Starting position for text
//  Current row tracker
//  These values may need to be tuned for different fonts or display sizes
const int rowHeight = 12;// Height of each text row
const int startRow = 12;// Starting row for text
const int startColumn = 2;// Starting column for text
const int maxRows = 3;// Maximum number of text rows that fit on the display
int currentRow = 0;


String displayLines[maxRows];

// Font selection
// Using a built-in font from U8g2 library
// Change to any other available font as needed
// For a list of fonts, refer to U8g2 documentation
// Example: u8g2_font_ncenB08_tr, u8g2_font_6x10_tf, etc.
const uint8_t* fontName = u8g2_font_boutique_bitmap_7x7_tr; // Font for display text

// Function prototypes
void clearScreen();
void drawScreen(const char* line1, const char* line2);
void drawScreen(const char* line1);
void printDisplayBuffer();
void scrollLines(int linesToScroll = 1);
void clearDisplayLines();


//  Initialize the display  
// Set contrast, power save mode, clear screen, and set font
// Call this function in setup()
// to initialize the display before use
void initScreen() {
u8g2.begin();
  u8g2.setContrast(30);
  u8g2.setPowerSave(0);
 clearScreen(); 
 u8g2.setFont(fontName);
 clearDisplayLines();
 
}

void clearDisplayLines() {
  for (int i = 0; i < maxRows; i++) {
    displayLines[i] = "";
  }
  currentRow = 0;
}

// Clear the display buffer and reset the current row
void clearScreen() {
  u8g2.clearBuffer();
 clearDisplayLines();
}

/// @brief Scrolls the display lines up by the specified number of lines
/// @param linesToScroll Number of lines to scroll up (default is 1)
void scrollLines(int linesToScroll ) {
   for (int i =1; i < maxRows; i++) {
    displayLines[i-1] = displayLines[i];
  }
  // Clear the last line(s)
  for (int i = maxRows - linesToScroll; i < maxRows; i++) {
    displayLines[i] = "";
  }
  currentRow = maxRows - linesToScroll;
}

void printDisplayBuffer() {
  u8g2.clearBuffer();
  for (int i = 0; i < maxRows; i++) {
    if(displayLines[i].length() == 0) {
      break;// Stop if no more lines to display
    }
    u8g2.drawStr(startColumn, startRow + rowHeight * i, displayLines[i].c_str());
  }
  u8g2.sendBuffer();
}

// Draw two lines of text on the display
// and send the buffer to the display
// Increments the current row after each line
void drawScreen(const char* line1, const char* line2) {
  if (currentRow + 2 > maxRows) {
    // Not enough space for two lines, clear screen
   scrollLines(2);
  }  
    displayLines[currentRow] = String(line1);
    currentRow++;
    displayLines[currentRow] = String(line2);
  currentRow++;
  printDisplayBuffer();
}

/// Draw a single line of text on the display
/// and send the buffer to the display
/// Increments the current row after the line
void drawScreen(const char* line1) {
    if(currentRow + 1 > maxRows) {
    // Not enough space for one line, clear screen  
      scrollLines();
    }   
  displayLines[currentRow] = String(line1);
  currentRow++;
  printDisplayBuffer();
}

#endif
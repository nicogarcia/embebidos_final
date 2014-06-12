#include "Arduino.h"
#include "SoftwareSerial.h"
#include "LiquidCrystal.h"
#include "LCDUI.h"

bool LCDUI::messages_disabled = false;
char LCDUI::first_line[LINE_LENGHT + 1];
char LCDUI::second_line[LINE_LENGHT + 1];

byte LCDUI::UP_ARROW_FILLED_DATA[8] = {
    B00000,
    B00000,
    B00100,
    B01110,
    B11111,
    B11111,
    B00000,
    B00000,
};

byte LCDUI::DOWN_ARROW_FILLED_DATA[8] = {
    B00000,
    B00000,
    B11111,
    B11111,
    B01110,
    B00100,
    B00000,
    B00000,
};

byte LCDUI::UP_ARROW_BORDERS_DATA[8] = {
    B00000,
    B00000,
    B00100,
    B01010,
    B10001,
    B11111,
    B00000,
    B00000,
};

byte LCDUI::DOWN_ARROW_BORDERS_DATA[8] = {
    B00000,
    B00000,
    B11111,
    B10001,
    B01010,
    B00100,
    B00000,
    B00000,
};

byte LCDUI::DEGREES_DATA[8] = {
    B00100,
    B01010,
    B00100,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
};

// initialize the library with the numbers of the interface pins
LiquidCrystal LCDUI::screen = LiquidCrystal(8, 9, 4, 5, 6, 7);

LCDUI::LCDUI() {
    first_line[LINE_LENGHT] = 0;
    second_line[LINE_LENGHT] = 0;

    serial_enabled = true;
    lcd_enabled = true;
}

void LCDUI::updateUI() {
    printFirstLine();
    printSecondLine();

    printKeyState();

    printMessage();

    if(lcd_enabled)
        LCDPrint();
    if(serial_enabled)
        SerialPrint();
}

void LCDUI::LCDPrint() {
    // Actually print first line
    screen.setCursor(0, 0);
    screen.print(first_line);

    // Actually print second line
    screen.setCursor(0, 1);
    screen.print(second_line);
}

void LCDUI::SerialPrint() {
    // Print first line through Serial
    Serial.println(first_line);

    // Print second line through Serial
    Serial.println(second_line);
}

LCDUI::UI_Time LCDUI::ms_to_time(unsigned long time_ms) {
    UI_Time time;
    time.hundreths = (time_ms / 10) % 100;
    time.seconds = (time_ms / 1000) % 60;
    time.minutes = (time_ms / 60000 % 100); // Modulo 100 to avoid overflow
    return time;
}

void LCDUI::my_strcpy(const char* source, char* destiny) {
    while((*destiny++ = *source++));
}

void LCDUI::clear_line(char* source) {
    for(int i = 0; i < LINE_LENGHT; i++)
        *(source + i) = ' ';
}

void LCDUI::printFirstLine() {
    clear_line(first_line);
    buildFirstLine();
}

void LCDUI::printSecondLine() {
    clear_line(second_line);
    buildSecondLine();
}

char LCDUI::int_to_char_num(int num) {
    return num + '0';
}

// Single decimal precision (Lenght = 4 chars)
void LCDUI::double_to_str(double num, char* destiny) {

    char second_dec = int_to_char_num((int)(num * 100) % 10);
    char first_dec = int_to_char_num((int)(num * 10) % 10);
    char first_int = int_to_char_num((int) num % 10);
    char second_int = int_to_char_num(((int) num / 10) % 10);
    char third_int = int_to_char_num(((int)num / 100) % 10);

    second_int = second_int == '0' ? ' ' : second_int;
    third_int = third_int == '0' ? ' ' : third_int;

    destiny[0] = third_int;
    destiny[1] = second_int;
    destiny[2] = first_int;
    destiny[3] = '.';
    destiny[4] = first_dec;
    destiny[5] = second_dec;
}

// Prints time in a string with the format MM:SS.CC in the specified position
void LCDUI::printTime(UI_Time time, char* destiny, int position) {
    int pos = position;

    // Write minutes
    destiny[pos++] = int_to_char_num(time.minutes / 10);
    destiny[pos++] = int_to_char_num(time.minutes % 10);

    // Write min sec separator
    destiny[pos++] = ':';

    // Write seconds
    destiny[pos++] = int_to_char_num(time.seconds / 10);
    destiny[pos++] = int_to_char_num(time.seconds % 10);

    // Write sec hund separator
    destiny[pos++] = '.';

    // Write hundreths
    destiny[pos++] = int_to_char_num(time.hundreths / 10);
    destiny[pos++] = int_to_char_num(time.hundreths % 10);
}


void LCDUI::initScreen() {
    const int numRows = 2;
    const int numCols = 16;

    pinMode(10, OUTPUT);

    // Create custom characters for arrows
    LCDUI::screen.createChar(UP_ARROW_FILLED_CHAR, UP_ARROW_FILLED_DATA);
    LCDUI::screen.createChar(UP_ARROW_BORDERS_CHAR, UP_ARROW_BORDERS_DATA);
    LCDUI::screen.createChar(DOWN_ARROW_FILLED_CHAR, DOWN_ARROW_FILLED_DATA);
    LCDUI::screen.createChar(DOWN_ARROW_BORDERS_CHAR, DOWN_ARROW_BORDERS_DATA);
    LCDUI::screen.createChar(DEGREES_CHAR, DEGREES_DATA);

    // set up the LCD's number of columns and rows:
    LCDUI::screen.begin(numCols, numRows);

    // Set LCD bright, initially to 80%
    analogWrite(10, 80);
}

void LCDUI::disable_message_print() {
    messages_disabled = true;
}

void LCDUI::enable_message_print() {
    messages_disabled = false;
}


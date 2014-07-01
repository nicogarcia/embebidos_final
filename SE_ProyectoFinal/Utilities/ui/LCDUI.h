#ifndef LCDUI_H_
#define LCDUI_H_
#include "LiquidCrystal.h"
#include "Dispatcher.h"
#include "Task.h"

class LCDUI {
public:
    void updateUI();

    static LiquidCrystal screen;

    static void initScreen();

    bool serial_enabled;
    bool lcd_enabled;

    //To stop printing message
    static void enable_message_print();

    //To stop printing message
    static void disable_message_print();
protected:
    LCDUI();
    // Time structure and function
    typedef struct {
        long minutes;
        int seconds;
        int hundreths;
    } UI_Time;
    static UI_Time ms_to_time(unsigned long time_ms);

    static void double_to_str(double num, char* destiny);

    // LCD 16x2 display will be divided in two lines of 14x1
    // and a 2x2 square for key states
    static const int LINE_LENGHT = 16;

    // LCD Lines, define with space for null terminating char
    static char first_line[LINE_LENGHT + 1];
    static char second_line[LINE_LENGHT + 1];

    // LCD Key states variables
    enum KeyStatePosition {
        UI_KEY_POSITION_UP = 14,
        UI_KEY_POSITION_SELECT = 15,
        UI_KEY_POSITION_DOWN = 14,
        UI_KEY_POSITION_LONG = 15
    };

    static bool messages_disabled;

    // Printing methods
    void printFirstLine();
    void printSecondLine();
    virtual void printMessage() = 0;
    virtual void printKeyState() = 0;
    void LCDPrint();
    void SerialPrint();

    // UI Building Functions
    virtual void buildFirstLine() = 0;
    virtual void buildSecondLine() = 0;

    // Utilities
    static void my_strcpy(const char* source, char* destiny);
    static void clear_line(char* source);
    static void printTime(UI_Time time, char* destiny, int position);
    virtual void empty_function() {};
    static char int_to_char_num(int num);

    // Special characters
    // Warning! Take care with value 0, may not work
    static const byte UP_ARROW_FILLED_CHAR = 5;
    static const byte UP_ARROW_BORDERS_CHAR = 1;
    static const byte DOWN_ARROW_FILLED_CHAR = 2;
    static const byte DOWN_ARROW_BORDERS_CHAR = 3;
    static const byte DEGREES_CHAR = 4;

    // Special characters data
    static byte UP_ARROW_FILLED_DATA[8];
    static byte UP_ARROW_BORDERS_DATA[8];
    static byte DOWN_ARROW_FILLED_DATA[8];
    static byte DOWN_ARROW_BORDERS_DATA[8];
    static byte DEGREES_DATA[8];
};
#endif /* LCDUI_H_ */
//--------------------- REAL TIME CLOCK IN A LCD MONITOR - By - Adarsh Verma - KIKfuc-17----------------------//
//Task: write a program code for any type of microcontroller or field programmable gate array (FPGA) which implements the following functions:
#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <millisDelay.h>
    millisDelay starttime;

    #define I2C_ADDR    0x27  // Define I2C Address for the PCF8574T 
    
    #define Rs_pin  0
    #define Rw_pin  1
    #define En_pin  2
    #define BACKLIGHT_PIN  3
    #define D4_pin  4
    #define D5_pin  5
    #define D6_pin  6
    #define D7_pin  7
    
    #define  LED_OFF  1
    #define  LED_ON  0
    
    /*-----( Declare objects )-----*/  
    LiquidCrystal_I2C  lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);


    //************Button*****************//
    int P1 = 6; // Button SET MENU'
    int P2 = 7; // Button +
    int P3 = 8; // Button -
    //************Variables**************//
    int hourupg = 0;
    int check = 0;
    int menu = 0;
    int input = 0;

    //---------------------setup--------------------------------//
    void setup() {

        lcd.begin(16, 2);
        lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE);
        lcd.setBacklight(LED_ON);

        pinMode(P1, INPUT);
        pinMode(P2, INPUT);
        pinMode(P3, INPUT);

        Serial.begin(9600);
        Wire.begin();

        int menu = 0;
    }

    //--------------------------options-------------------------------//
    void Option0() {
        tmElements_t tm;
        lcd.backlight();
        (RTC.read(tm));

        lcd.setCursor(0, 0); //Start at character 0 on line 0
        lcd.print("DATE :");
        lcd.print(tm.Day);
        lcd.print('/');
        lcd.print(tm.Month);
        lcd.print('/');
        lcd.print(tmYearToCalendar(tm.Year));

        lcd.setCursor(0, 1); //Start at character 0 on line 1
        lcd.print("T :");
        print2digits(tm.Hour);
        lcd.print(':');
        print2digits(tm.Minute);
        lcd.print(':');
        print2digits(tm.Second);
        lcd.print(": DMY");
    }

    void Option1() {
        tmElements_t tm;
        lcd.backlight();
        (RTC.read(tm));

        lcd.setCursor(0, 0); //Start at character 0 on line 0
        lcd.print("DATE :");
        lcd.print(tmYearToCalendar(tm.Year));
        lcd.print('/');
        lcd.print(tm.Month);
        lcd.print('/');
        lcd.print(tm.Day);

        lcd.setCursor(0, 1); //Start at character 0 on line 1
        lcd.print("T :");
        print2digits(tm.Hour);
        lcd.print(':');
        print2digits(tm.Minute);
        lcd.print(':');
        print2digits(tm.Second);
        lcd.print(": YMD");
    }

    void Option2() {
        tmElements_t tm;
        lcd.backlight();
        (RTC.read(tm));

        lcd.setCursor(0, 0); //Start at character 0 on line 0
        lcd.print("DATE :");
        lcd.print(tm.Month);
        lcd.print('/');
        lcd.print(tm.Day);
        lcd.print('/');
        lcd.print(tmYearToCalendar(tm.Year));

        lcd.setCursor(0, 1); //Start at character 0 on line 1
        lcd.print("T :");
        print2digits(tm.Hour);
        lcd.print(':');
        print2digits(tm.Minute);
        lcd.print(':');
        print2digits(tm.Second);
        lcd.print(": MDY");
    }


    //------------------------Start-----------------------------//
    void loop() {

        if (digitalRead(P1)) {
            check = 0;
            starttime.start(4400);
            if (menu == 3) {
                menu = 0;
            } else {
                menu = menu + 1;
            }

        }
        // in which subroutine should we go?
        if (menu == 0) {
            Option0();
        }
        if (menu == 1) {
            Display1();
        }
        if (menu == 2) {
            StoreOption();
        }

        delay(100);
    }

    void print2digits(int number) {
        if (number >= 0 && number < 10) {
            lcd.print('0');
        }
        lcd.print(number);
    }

    //---------------------------------Select-----------------------------//
    void Display1() {

        if (digitalRead(P2) == HIGH) {
            check = 0;
            starttime.start(4400);
            if (hourupg == 2) {
                hourupg = 0;
            } else {
                hourupg = hourupg + 1;
            }
        }

        if (digitalRead(P3) == HIGH) {
            check = 0;
            starttime.start(4400);
            if (hourupg == 0) {
                hourupg = 2;
            } else {
                hourupg = hourupg - 1;
            }
        }
        if (!digitalRead(P2) == HIGH) {

            if (hourupg == 0) {

                Option0();
                input = 0;

                if (starttime.justFinished()) {
                    check++;
                }
                if (check < 1) {
                    delay(100);
                    lcd.setCursor(13, 1);
                    lcd.print("   ");
                    lcd.setCursor(6, 0);
                    lcd.print("          ");
                }
            }
            
            if (hourupg == 1) {

                Option1();
                input = 1;
                if (starttime.justFinished()) {
                    check++;
                }
                if (check < 1) {
                    delay(100);
                    lcd.setCursor(13, 1);
                    lcd.print("   ");
                    lcd.setCursor(6, 0);
                    lcd.print("          ");
                }
            }
            
            if (hourupg == 2) {

                Option2();
                input = 2;
                if (starttime.justFinished()) {
                    check++;
                }
                if (check < 1) {
                    delay(100);
                    lcd.setCursor(13, 1);
                    lcd.print("   ");
                    lcd.setCursor(6, 0);
                    lcd.print("          ");
                }
            }
            
        }
    }


    void StoreOption() {
    // Variable saving

        if (input == 0) {
            Option0();

        } else if (input == 1) {
            Option1();

        } else {
            Option2();

        }
    }

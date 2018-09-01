#define __AVR_ATtiny85__
#define F_CPU 16500000

// Using modified IRremote from https://github.com/z3t0/Arduino-IRremote
#include "IRremote.h"
#include "DigiKeyboard.h"

//Button codes
#define RIGHTBTN 2011258888
#define LEFTBTN 2011271176
#define UPBTN 2011254792
#define DOWNBTN 2011246600
#define MIDDLEBTN 2011249160 //Sends two commands, but we don't care, since it's unique
#define MENUBTN 2011283464
#define PLAYBTN 2011298312 // Also sends two commands

//More keys
#define KEY_ARROW_DOWN 0x51
#define KEY_ARROW_UP 0x52
#define KEY_ARROW_RIGHT 0x4f

//Receive pin for TSOP4838
#define RECV_PIN 0 //P0

IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
    irrecv.enableIRIn();
    pinMode(1, OUTPUT); //LED on Model A
}

void loop()
{
    DigiKeyboard.update();

    if (!irrecv.decode(&results))
    {
        return;
    }

    digitalWrite(1, HIGH);

    storeCode(&results);

    digitalWrite(1, LOW);

    irrecv.resume(); // resume receiver
}

void storeCode(decode_results *results)
{
    if (results->decode_type != NEC || results->value == REPEAT)
    {
        return;
    }

    if (results->value == RIGHTBTN)
    {
        //DigiKeyboard.println("Right");
        DigiKeyboard.sendKeyStroke(KEY_ARROW_RIGHT);
    }
    else if (results->value == LEFTBTN)
    {
        DigiKeyboard.sendKeyStroke(KEY_ARROW_LEFT);
    }
    else if (results->value == UPBTN)
    {
        DigiKeyboard.sendKeyStroke(KEY_ARROW_UP);
    }
    else if (results->value == DOWNBTN)
    {
        DigiKeyboard.sendKeyStroke(KEY_ARROW_DOWN);
    }
    else if (results->value == MIDDLEBTN)
    {
        DigiKeyboard.sendKeyStroke(KEY_ENTER);
    }
    // else if (results->value == MENUBTN)
    // {
    //     DigiKeyboard.sendKeyStroke(KEY_ENTER);
    // }
    // else if (results->value == PLAYBTN)
    // {
    //     DigiKeyboard.sendKeyStroke(KEY_ENTER);
    // }
}
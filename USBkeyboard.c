/**
 * Project: USB Keyboard from PS/2 Keyboard
 * Author: Jasvinder Marwaha, jsm1g11@soton.ac.uk
 * Based on AVR ATtiny USB Tutorial at http://codeandlife.com/ by Joonas Pihlajamaa
 * V-USB
 * Copyright: (c) 2008 by OBJECTIVE DEVELOPMENT Software GmbH
 * License: GNU GPL v3 (see License.txt)
 */
//ISR (PCINT0_Vect,ISR_NOBLOCK)
//{
//	/*interrupt code here TODO */
//}

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include "usbdrv/usbdrv.h"

#define MSG_BUFFER_SIZE 1
#define STATE_SEND 1
#define STATE_DONE 0
#define MOD_SHIFT_LEFT (1<<1)
#define abs(x) ((x) > 0 ? (x) : (-x))

// ************************
// *** USB HID ROUTINES ***
// ************************

// From Frank Zhao's USB Business Card project
// http://www.frank-zhao.com/cache/usbbusinesscard_details.php
PROGMEM char usbHidReportDescriptor[USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH] = {
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
    0x09, 0x06,                    // USAGE (Keyboard)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x75, 0x01,                    //   REPORT_SIZE (1)
    0x95, 0x08,                    //   REPORT_COUNT (8)
    0x05, 0x07,                    //   USAGE_PAGE (Keyboard)(Key Codes)
    0x19, 0xe0,                    //   USAGE_MINIMUM (Keyboard LeftControl)(224)
    0x29, 0xe7,                    //   USAGE_MAXIMUM (Keyboard Right GUI)(231)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
    0x81, 0x02,                    //   INPUT (Data,Var,Abs) ; Modifier byte
    0x95, 0x01,                    //   REPORT_COUNT (1)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x81, 0x03,                    //   INPUT (Cnst,Var,Abs) ; Reserved byte
    0x95, 0x05,                    //   REPORT_COUNT (5)
    0x75, 0x01,                    //   REPORT_SIZE (1)
    0x05, 0x08,                    //   USAGE_PAGE (LEDs)
    0x19, 0x01,                    //   USAGE_MINIMUM (Num Lock)
    0x29, 0x05,                    //   USAGE_MAXIMUM (Kana)
    0x91, 0x02,                    //   OUTPUT (Data,Var,Abs) ; LED report
    0x95, 0x01,                    //   REPORT_COUNT (1)
    0x75, 0x03,                    //   REPORT_SIZE (3)
    0x91, 0x03,                    //   OUTPUT (Cnst,Var,Abs) ; LED report padding
    0x95, 0x06,                    //   REPORT_COUNT (6)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0x65,                    //   LOGICAL_MAXIMUM (101)
    0x05, 0x07,                    //   USAGE_PAGE (Keyboard)(Key Codes)
    0x19, 0x00,                    //   USAGE_MINIMUM (Reserved (no event indicated))(0)
    0x29, 0x65,                    //   USAGE_MAXIMUM (Keyboard Application)(101)
    0x81, 0x00,                    //   INPUT (Data,Ary,Abs)
    0xc0                           // END_COLLECTION
};

typedef struct {
	uint8_t modifier;
	uint8_t reserved;
	uint8_t keycode[6];
} keyboard_report_t;

/* Variables Declared for buffer transfer*/

static keyboard_report_t keyboard_report; // sent to PC
volatile static uchar LED_state = 0xff; // received from PC
static uchar idleRate; // repeat rate for keyboards
static uchar messageState = STATE_DONE;
static uchar messageBuffer[MSG_BUFFER_SIZE] = "";
static uchar messagePtr = 0;
static uchar messageCharNext = 1;

// The buildReport is called by main loop and it starts transmitting
// characters when messageState == STATE_SEND. The message is stored
// in messageBuffer and messagePtr tells the next character to send.
// Remember to reset messagePtr to 0 after populating the buffer!
uchar buildReport() {
    uchar ch;

    if(messageState == STATE_DONE || messagePtr >= sizeof(messageBuffer) || messageBuffer[messagePtr] == 0) {
        keyboard_report.modifier = 0;
        keyboard_report.keycode[0] = 0;
        return STATE_DONE;
    }

    if(messageCharNext) { // send a keypress
        ch = messageBuffer[messagePtr++];

        // convert character to modifier + keycode
        if(ch >= '0' && ch <= '9') {
            keyboard_report.modifier = 0;
            keyboard_report.keycode[0] = (ch == '0') ? 39 : 30+(ch-'1');
        } else if(ch >= 'a' && ch <= 'z') {
            keyboard_report.modifier = (LED_state & 2) ? MOD_SHIFT_LEFT : 0;
            keyboard_report.keycode[0] = 4+(ch-'a');
        } else if(ch >= 'A' && ch <= 'Z') {
            keyboard_report.modifier = (LED_state & 2) ? 0 : MOD_SHIFT_LEFT;
            keyboard_report.keycode[0] = 4+(ch-'A');
        } else {
            keyboard_report.modifier = 0;
            keyboard_report.keycode[0] = 0;
            switch(ch) {
			case '.':
				keyboard_report.keycode[0] = 0x37;
				break;
			case '_':
				keyboard_report.modifier = MOD_SHIFT_LEFT;
				break;
			case '-':
				keyboard_report.keycode[0] = 0x2D;
				break;
            case ' ':
                keyboard_report.keycode[0] = 0x2C;
                break;
            case '\t':
                keyboard_report.keycode[0] = 0x2B;
                break;
            case '\n':
                keyboard_report.keycode[0] = 0x28;
                break;
            case 8:
            	keyboard_report.keycode[0] = 0x2A;
            	break;

            }

        }
    } else { // key release before the next keypress!
        keyboard_report.modifier = 0;
        keyboard_report.keycode[0] = 0;
    }

    messageCharNext = !messageCharNext; // invert

    return STATE_SEND;
}

usbMsgLen_t usbFunctionSetup(uchar data[8]) {
    usbRequest_t *rq = (void *)data;

    if((rq->bmRequestType & USBRQ_TYPE_MASK) == USBRQ_TYPE_CLASS) {
        switch(rq->bRequest) {
        case USBRQ_HID_GET_REPORT: // send "no keys pressed" if asked here
            // wValue: ReportType (highbyte), ReportID (lowbyte)
            usbMsgPtr = (void *)&keyboard_report; // we only have this one
            keyboard_report.modifier = 0;
            keyboard_report.keycode[0] = 0;
            return sizeof(keyboard_report);
		case USBRQ_HID_SET_REPORT: // if wLength == 1, should be LED state
            return (rq->wLength.word == 1) ? USB_NO_MSG : 0;
        case USBRQ_HID_GET_IDLE: // send idle rate to PC as required by spec
            usbMsgPtr = &idleRate;
            return 1;
        case USBRQ_HID_SET_IDLE: // save idle rate as required by spec
            idleRate = rq->wValue.bytes[1];
            return 0;
        }
    }

    return 0; // by default don't return any data
}

void caps_toggle(); // defined later in program logic

usbMsgLen_t usbFunctionWrite(uint8_t * data, uchar len) {
	if (data[0] == LED_state)
        return 1;
    else
        LED_state = data[0];

    caps_toggle();

	return 1; // Data read, not expecting more
}

/* Called by V-USB after device reset - Leave this function alone*/
void hadUsbReset() {
    int frameLength, targetLength = (unsigned)(1499 * (double)F_CPU / 10.5e6 + 0.5);
    int bestDeviation = 9999;
    uchar trialCal, bestCal = 0, step, region;

    // do a binary search in regions 0-127 and 128-255 to get optimum OSCCAL
    for(region = 0; region <= 1; region++) {
        frameLength = 0;
        trialCal = (region == 0) ? 0 : 128;

        for(step = 64; step > 0; step >>= 1) {
            if(frameLength < targetLength) // true for initial iteration
                trialCal += step; // frequency too low
            else
                trialCal -= step; // frequency too high

            OSCCAL = trialCal;
            frameLength = usbMeasureFrameLength();

            if(abs(frameLength-targetLength) < bestDeviation) {
                bestCal = trialCal; // new optimum found
                bestDeviation = abs(frameLength -targetLength);
            }
        }
    }

    OSCCAL = bestCal;
}

/* Variables for Logic part of the program */
static int initCaps = 0;
static int position = 0;
int dataIn[11], dataOut[8]; // 'a' is data in
int release = 0, shift = 0;

void clear_buffer()
{
	int i;
	for (i=0;i<sizeof(messageBuffer);i++)
	{
		messageBuffer[i] = '\0';
	}
}
/* This routine is called by usbFunctionWrite every time the keyboard LEDs */
void caps_toggle()
{
	if (initCaps == 0)// Nullifies the effect of the host turning on the lights when the keyboard is connected
	{
		initCaps = 1;
	}
	else
	{
		//TODO code to toggle Caps light/react to Capslock
	}
    // Type a message to the PC that we're regenerating the password
 }
#include "binaryTree.h" //Contains large hex_to_char function (keeps code here neat)
int parity_check() // Checks that the data is correct against the parity bit
{
	int total = 0;
	int i;
	for (i = 1; i < 10; i++) // Checks data bits 0-8 and adds up 1's
	{
		if(dataIn[i])
		{
			total++;
		}
	}
	if (total%2) //If total is odd
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


void poll_data()
{
	dataIn[position] = (PINA & _BV(1)) ? 1 : 0 ; //Reads data from PORTA and sets as a 1 or 0 according to pin 1 value
	position++;
}

void send_char(char output)
{
	clear_buffer();
	if(shift & (('a' <= output) &( output <= 'z')))
	{
		messageBuffer[0] = (output - 32); // Changes letters to capitals
	}
	else if (shift & (('0'<=output) & (output<='9'))) // Changes numbers to symbols
	{
		messageBuffer[0] = (output - 15);
	}
	messagePtr = 0;
	messageState = STATE_SEND;
}

int main() {
	uchar i;
	int j = 0;
	DDRA = 0x00; // Setup PORTA as inputs
	DDRB |= _BV(PINB7); // set LED pin as output
    for(i=0; i<sizeof(keyboard_report); i++) // clear report initially
    {
        ((uchar *)&keyboard_report)[i] = 0;
    }

    wdt_enable(WDTO_1S); // enable 1s watchdog timer
    usbInit();
    usbDeviceDisconnect(); // enforce re-enumeration

    for(i = 0; i<250; i++) // wait 500 ms
    {
        wdt_reset(); // keep the watchdog happy
        _delay_ms(2);
    }
    usbDeviceConnect();
    sei(); // Enable interrupts after re-enumeration

    while(1) //Main program for receiving and sending key presses
    {
        wdt_reset(); // keep the watchdog happy
        usbPoll();
        /*if (parity_check())
        {
        send_char(hex_to_char());
        }*/
        // characters are sent when messageState == STATE_SEND and after receiving
        // the initial LED state from PC (good way to wait until device is recognized)
        //send_char('b');
		if(usbInterruptIsReady() && messageState == STATE_SEND && LED_state != 0xff)
		{
			cli();//disable global interrupts
			messageState = buildReport();
			usbSetInterrupt((void *)&keyboard_report, sizeof(keyboard_report));
			sei(); //enable global interrupts
		}
		else if ((PINA & _BV(0)) == 0) // Clock Checker (is active low)
		{
			while((PINA & _BV(0)) == 0)
			{
				/*Keep the watchdog happy*/
				wdt_reset();
			}
			poll_data(); //get the data bit and add to array
			if ((position > 0) & (position < 10))
			{
				cli();
			}
			else
			{
				sei();
			}
			if (position >= 10)
			{
				if(parity_check()) // Checks parity, if it fails next bit is received
				{
				send_char(hex_to_char()); // converts data into recognised key and sends
				}
				position = 0; // Sets the position to 0 ready for the next input
				//TODO may need to clear the data buffer here
			}
		}
    }
    return 0;
}

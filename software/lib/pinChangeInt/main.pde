
 #define NO_PORTB_PINCHANGES
 #define NO_PORTC_PINCHANGES

#define PINMODE
#define FLASH

#include <ByteBuffer.h>
#include <PinChangeInt.h>

int state;
int val;
int val2;

void myHandler()
{
	val = digitalRead(7);
    delay(10);
    val2 = digitalRead(7);
	if ((val == val2) && (val == 1))
	{
		digitalWrite(0, HIGH);
	}
}

void myHandlerr()
{
	val = digitalRead(7);
    delay(10);
    val2 = digitalRead(7);
	if ((val == val2) && (val == 0))
	{
		digitalWrite(0, LOW);
	}

}

void setup() {

	pinMode(0, OUTPUT);

	state = 0;
	digitalWrite(0, LOW);


    pinMode(7, INPUT);
    digitalWrite(7, HIGH);
	PCintPort::attachInterrupt(7, &myHandler, RISING);
	PCintPort::attachInterrupt(7, &myHandlerr, FALLING);

}

void loop()
{

}


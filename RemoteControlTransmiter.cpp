// Do not remove the include below
#include "RemoteControlTransmiter.h"
#include <Signal.h>
#include <Button.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

Signal a = Signal(A0);
Signal b = Signal(A1);

Signal c = Signal(A2);
Signal d = Signal(A3);

Button button1 = Button(9, PULLUP);
Button button2 = Button(7, PULLUP);
Button button3 = Button(5, PULLUP);

#include <VirtualWire.h>
const int led_pin = 11;
const int transmit_pin = 10;
const int receive_pin = 2;
const int transmit_en_pin = 3;


void setup() {
	Serial.begin(9600);
	lcd.init();
	lcd.backlight();

	vw_set_tx_pin(transmit_pin);
	    vw_set_rx_pin(receive_pin);
	    vw_set_ptt_pin(transmit_en_pin);
	    vw_set_ptt_inverted(true); // Required for DR3100
	    vw_setup(2000);       // Bits per sec
}

void disply() {
	lcd.clear();

	lcd.setCursor(0, 0);
	lcd.print(a.getTiltRod());

	lcd.setCursor(4, 0);
	lcd.print(":");
	lcd.print(b.getTiltRod());

	lcd.setCursor(10, 0);
	lcd.print("A:");
	lcd.print(button1.isPressed());

	lcd.setCursor(0, 1);
	lcd.print(c.getTiltRod());

	lcd.setCursor(4, 1);
	lcd.print(":");
	lcd.print(d.getTiltRod());

	lcd.setCursor(10, 1);
	lcd.print("B:");
	lcd.print(!button2.isPressed());

	lcd.print("C:");
	lcd.print(button3.isPressed());
}

void send() {

	  char buffer [5];
	  itoa(a.getTiltRod(), buffer,10);
		vw_send((uint8_t *) "I01", 3);
		vw_send((uint8_t *) "S", 2);

	vw_send((uint8_t *) buffer, 4);
	vw_send((uint8_t *) "G", 1);

	vw_wait_tx();
}

void loop() {

	if (button1.isPressed()) {
		Signal::setCalibrationOn();
	} else {
		Signal::setCalibrationOff();
	}

	a.read();
	b.read();
	c.read();
	d.read();
	disply();

	send();
//	delay(75);

}

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

void setup() {
	Serial.begin(9600);
	lcd.init();
	lcd.backlight();
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
	delay(75);

}

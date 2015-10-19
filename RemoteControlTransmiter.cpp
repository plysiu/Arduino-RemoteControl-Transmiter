// Do not remove the include below
#include "RemoteControlTransmiter.h"
#include <Signal.h>
#include <Button.h>

Signal a = Signal(A0);
Signal b = Signal(A1);
Signal c = Signal(A2);
Signal d = Signal(A3);

Button calibrate = Button(7, PULLUP);

void setup() {
	Serial.begin(9600);
}

void loop() {

	if (calibrate.isPressed()) {
		Signal::setCalibrationOn();
	} else {
		Signal::setCalibrationOff();
	}

	a.read();
	b.read();
	c.read();
	d.read();

	Serial.print(a.getMinValue());
	Serial.print("-");
	Serial.print(a.getCenterValue());
	Serial.print("-");
	Serial.print(a.getMaxValue());
	Serial.print("-");
	Serial.print(a.getTiltRod());
	Serial.print("-");
	Serial.println(a.getValue());

	Serial.print(b.getMinValue());
	Serial.print("-");
	Serial.print(b.getCenterValue());
	Serial.print("-");
	Serial.print(b.getMaxValue());
	Serial.print("-");
	Serial.print(b.getTiltRod());
	Serial.print("-");
	Serial.println(b.getValue());

	Serial.print(c.getMinValue());
	Serial.print("-");
	Serial.print(c.getCenterValue());
	Serial.print("-");
	Serial.print(c.getMaxValue());
	Serial.print("-");
	Serial.print(c.getTiltRod());
	Serial.print("-");
	Serial.println(c.getValue());

	Serial.print(d.getMinValue());
	Serial.print("-");
	Serial.print(d.getCenterValue());
	Serial.print("-");
	Serial.print(d.getMaxValue());
	Serial.print("-");
	Serial.print(d.getTiltRod());
	Serial.print("-");
	Serial.println(d.getValue());
	delay(2000);
}
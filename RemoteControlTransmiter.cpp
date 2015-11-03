// Do not remove the include below
#include "RemoteControlTransmiter.h"
#include <VirtualWire.h>
#include <Button.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "Signal.h"
#include "StandardCplusplus.h"

#include <string>

LiquidCrystal_I2C lcd(0x27, 16, 2);
Signal a = Signal(A0);
Signal b = Signal(A1);
Signal c = Signal(A2);
Signal d = Signal(A3);
Button button1 = Button(9, PULLUP);
Button button2 = Button(7, PULLUP);
Button button3 = Button(5, PULLUP);

const int led_pin = 11;
const int transmit_pin = 10;
const int receive_pin = 2;
const int transmit_en_pin = 3;

void setup() {
	lcd.init();
	lcd.backlight();
	Serial.begin(9600);

	vw_set_tx_pin(transmit_pin);
	vw_set_rx_pin(receive_pin);
	vw_set_ptt_pin(transmit_en_pin);
	vw_set_ptt_inverted(true); // Required for DR3100
	vw_setup(8000);       // Bits per sec

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
void send(std::vector<RemoteControl::Signal> signals) {
	std::string str;
	for (unsigned int i = 0; i < signals.size(); i++) {
		str += RemoteControl::transformSignalToString(signals[i]).c_str();
	}
	vw_send((uint8_t*) str.c_str(), str.length());
	vw_wait_tx();
}

unsigned long previousMillis = 0;

const long interval = 125;

unsigned long int timestamp = 0;
int8_t lastValues[4];
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

	std::vector<RemoteControl::Signal> signals;

		signals.push_back( { 0, a.getTiltRod() });

		signals.push_back( { 1, b.getTiltRod() });

		signals.push_back( { 2, c.getTiltRod() });

		signals.push_back( { 3, d.getTiltRod() });

	send(signals);

	unsigned long currentMillis = millis();

	if (currentMillis - previousMillis >= interval) {
		previousMillis = currentMillis;
		disply();
		timestamp = micros();
	}

}

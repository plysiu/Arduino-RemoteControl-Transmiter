/*
 * Signal.cpp
 *
 *  Created on: 18 paź 2015
 *      Author: plysiu
 *      @TODO create Kalman library
 */

#include "Signal.h"

bool Signal::calibration = false;

bool Signal::getCalibrationStatus() {
	return Signal::calibration;
}

void Signal::setCalibrationOn() {
	Signal::calibration = true;
}

void Signal::setCalibrationOff() {
	Signal::calibration = false;
}
//http://forum.arduino.cc/index.php?topic=333493.0
Signal::Signal(int pin) {
	this->pin = pin;
	this->minValue = 1023;
	this->maxValue = 0;
	this->centerValue = 1023;
	pinMode(this->pin, INPUT);
}

void Signal::read() {
	this->setValue(analogRead(this->pin));
	if (this->getValue() > this->getMaxValue()) {
		this->setMaxValue(this->getValue());
	}

	if (this->getValue() < this->getMinValue()) {
		this->setMinValue(this->getValue());
	}

	if (Signal::getCalibrationStatus() == true) {
		this->setCenterValue(this->getValue());
	}
}

int Signal::getValue() {
	return this->value;
}
void Signal::setValue(int _value) {
	this->value = _value;
}

int Signal::getMaxValue() {
	return this->maxValue;
}
void Signal::setMaxValue(int _value) {
	this->maxValue = _value;
}

int Signal::getMinValue() {
	return this->minValue;
}
void Signal::setMinValue(int _value) {
	this->minValue = _value;
}

int Signal::getCenterValue() {
	return this->centerValue;
}

void Signal::setCenterValue(int _value) {
	this->centerValue = _value;
}

int8_t Signal::getTiltRod() {
	return RemoteControl::convertAnalogValue(this->getValue(),
			this->getMinValue(), this->getCenterValue(), this->getMaxValue());
}

Signal::~Signal() {
}


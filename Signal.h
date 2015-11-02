/*
 * Signal.h
 *
 *  Created on: 18 paź 2015
 *      Author: plysiu
 */

#ifndef SIGNAL_H_
#define SIGNAL_H_

#include <Arduino.h>
#include <RemoteControl.h>


class Signal {
	int pin;
	int value;
	int centerValue;
	int maxValue;
	int minValue;
protected:
	static bool calibration;
public:

	static void setCalibrationOn();
	static void setCalibrationOff();
	static bool getCalibrationStatus();

	Signal(int pin);
	void read();

	int getValue();
	void setValue(int _value);

	int getMaxValue();
	void setMaxValue(int _value);

	int getMinValue();
	void setMinValue(int _value);

	int getCenterValue();
	void setCenterValue(int _value);

	int8_t getTiltRod();
	virtual ~Signal();
};

#endif /* SIGNAL_H_ */

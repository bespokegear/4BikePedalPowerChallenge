#include <Arduino.h>
#include "Heartbeat.h"
#include "Config.h"
#include "CorrectedMillis.h"

_Heartbeat Heartbeat(HEARTBEAT_LED_PIN);

_Heartbeat::_Heartbeat(int pin) :
    _mode(_Heartbeat::Normal),
	_pin(pin),
    _pinState(true),
    _lastStateFlip(0),
    _onTime(0),
    _offTime(0)
{
	setMode(_mode);
}

_Heartbeat::~_Heartbeat()
{
}

void _Heartbeat::begin()
{
    pinMode(_pin, OUTPUT);
}

_Heartbeat::Mode _Heartbeat::mode()
{
    return _mode;
}

void _Heartbeat::setMode(Mode mode)
{
	_mode = mode;
	switch (_mode) {
	case Normal:
        _onTime = ON_MS_NORMAL;
        _offTime = OFF_MS_NORMAL;
		break;
	case Quick:
        _onTime = ON_MS_QUICK;
        _offTime = OFF_MS_QUICK;
		break;
	case Slow:
        _onTime = ON_MS_SLOW;
        _offTime = OFF_MS_SLOW;
		break;
	case Slower:
        _onTime = ON_MS_SLOWER;
        _offTime = OFF_MS_SLOWER;
		break;
	}
}

void _Heartbeat::update()
{
    unsigned long wait = _pinState ? _onTime : _offTime;
    if (millis() - _lastStateFlip >= wait) {
        updatePin(!_pinState);
    }
}

void _Heartbeat::updatePin(bool state)
{
    _pinState = state;
    digitalWrite(_pin, _pinState);
    _lastStateFlip = millis();
}



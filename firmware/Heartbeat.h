#pragma once

#define ON_MS_NORMAL		50
#define OFF_MS_NORMAL		500
#define ON_MS_QUICK	    	25
#define OFF_MS_QUICK	    25
#define ON_MS_SLOW		    1000
#define OFF_MS_SLOW	    	150
#define ON_MS_SLOWER		1000
#define OFF_MS_SLOWER		1000

class _Heartbeat {
public:
	enum Mode {
		Normal=0,
		Quick,
		Slow,
		Slower
	};

    // Call from setup()
	_Heartbeat(int pin);
	~_Heartbeat();

    void begin();

    Mode mode();
	void setMode(Mode mode);
	void update();

private:
    void updatePin(bool state);

	Mode _mode;
	int _pin;
	bool _pinState;
	unsigned long _lastStateFlip;
	unsigned int _onTime;
	unsigned int _offTime;

};

extern _Heartbeat Heartbeat;


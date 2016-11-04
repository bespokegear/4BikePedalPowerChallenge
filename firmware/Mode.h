#pragma once

class Mode {
public:
    Mode();
    virtual ~Mode() {;}

    // If you want to do anythin in setup() (e.g. set pins), implement this
    virtual void begin() {;}

    // All Modes must also implement a start() function
    virtual void start() = 0;

    // All Modes must also implement a stop() function
    virtual void stop() = 0;

    // Optionally over-ride reset
    virtual void reset() { start(); }

    // This is what should be called from the main program every cycle
    // this will call modeUpdate, which is where derived classed should
    // put their user udate code.  The update() function monitors input
    // voltage and calls enterBrownout() and exitBrownout()
    virtual void update();
    virtual void modeUpdate() = 0;

    // called when vIn drops below BROWNOUT_LOW
    virtual void enterBrownout() {;}
    // called when vIn rises above BROWNOUT_HIGH
    virtual void exitBrownout() {;}

    // over-ride if you want the mode to indicate that it is finished
    virtual bool isFinished() { return false; }

    bool isBrownedOut() { return _brownedOut; }

private:
    bool _brownedOut;
    void _enterBrownout();
    void _exitBrownout();

};


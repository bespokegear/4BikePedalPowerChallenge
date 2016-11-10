#pragma once

#include "LatchedButton.h"

class DualButton {
public:
    DualButton(LatchedButton* b1, LatchedButton* b2) { _b1 = b1 ; _b2 = b2; }
    void begin() { _b1->begin(); _b2->begin(); }
    void update() { _b1->update(); _b2->update(); }
    bool wasPressed() { return _b1->wasPressed() || _b2->wasPressed(); }
    bool isPressed() { return _b1->isPressed() || _b2->isPressed(); }

private:
    LatchedButton* _b1;
    LatchedButton* _b2;
};


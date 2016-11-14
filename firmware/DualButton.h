#pragma once

#include "DebouncedButton.h"

class DualButton {
public:
    DualButton(DebouncedButton* b1, DebouncedButton* b2) { _b1 = b1 ; _b2 = b2; }
    void begin() { _b1->begin(); _b2->begin(); }
    void update() { _b1->update(); _b2->update(); }
    bool wasPressed() { return _b1->wasPressed() || _b2->wasPressed(); }
    bool isPressed() { return _b1->isPressed() || _b2->isPressed(); }

private:
    DebouncedButton* _b1;
    DebouncedButton* _b2;
};


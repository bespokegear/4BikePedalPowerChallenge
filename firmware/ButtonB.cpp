#include "LatchedButton.h"
#include "DualButton.h"
#include "Config.h"

LatchedButton ButtonB1(RESET_BUTTON_PIN);
LatchedButton ButtonB2(REMOTE_RESET_BUTTON_PIN, false);

DualButton ButtonB(&ButtonB1, &ButtonB2);


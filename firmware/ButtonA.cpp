#include "LatchedButton.h"
#include "DualButton.h"
#include "Config.h"

LatchedButton ButtonA1(MODE_BUTTON_PIN);
LatchedButton ButtonA2(REMOTE_MODE_BUTTON_PIN, false);

DualButton ButtonA(&ButtonA1, &ButtonA2);


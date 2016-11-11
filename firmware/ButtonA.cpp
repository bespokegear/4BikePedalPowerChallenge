#include "LatchedButton.h"
#include "DualButton.h"
#include "Config.h"

LatchedButton ButtonA1(WIRED_A_BUTTON_PIN);
LatchedButton ButtonA2(REMOTE_A_BUTTON_PIN, false);

DualButton ButtonA(&ButtonA1, &ButtonA2);


#include "DebouncedButton.h"
#include "DualButton.h"
#include "Config.h"

DebouncedButton ButtonA1(WIRED_A_BUTTON_PIN);
DebouncedButton ButtonA2(REMOTE_A_BUTTON_PIN, false);

DualButton ButtonA(&ButtonA1, &ButtonA2);


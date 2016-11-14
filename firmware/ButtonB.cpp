#include "DebouncedButton.h"
#include "DualButton.h"
#include "Config.h"

DebouncedButton ButtonB1(WIRED_B_BUTTON_PIN);
DebouncedButton ButtonB2(REMOTE_B_BUTTON_PIN, false);

DualButton ButtonB(&ButtonB1, &ButtonB2);


#include "LatchedButton.h"
#include "DualButton.h"
#include "Config.h"

LatchedButton ResetButton1(RESET_BUTTON_PIN);
LatchedButton ResetButton2(REMOTE_RESET_BUTTON_PIN, false);

DualButton ResetButton(&ResetButton1, &ResetButton2);


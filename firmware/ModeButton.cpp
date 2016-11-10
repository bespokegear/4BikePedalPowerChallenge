#include "LatchedButton.h"
#include "DualButton.h"
#include "Config.h"

LatchedButton ModeButton1(MODE_BUTTON_PIN);
LatchedButton ModeButton2(REMOTE_MODE_BUTTON_PIN, false);

DualButton ModeButton(&ModeButton1, &ModeButton2);


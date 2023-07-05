#include "PadInput.h"

char PadInput::NowKey[BUTTONS];
char PadInput::OldKey[BUTTONS];
XINPUT_STATE PadInput::Input;
Stick PadInput::Rstick;
Stick PadInput::Lstick;
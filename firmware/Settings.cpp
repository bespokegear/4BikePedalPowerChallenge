#include "Settings.h"
#include "Config.h"

//                                 EEROM,   Min,    Max,                Default,    Scale
ScaledIntSetting MaximumPowerWatts(0,       100,    1000,               500,        100);
ScaledIntSetting GameDurationSeconds(4,     10,     120,                30,         10);
ScaledIntSetting NumberOfLedSegments(8,     1,      PLAYER_SEGMENT_MAX, 1,          1 );



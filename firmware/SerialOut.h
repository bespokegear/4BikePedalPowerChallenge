#pragma once

#define SerialOut(x) ({ Serial.print(x); Serial1.print(x); })
#define SerialOutln(x) ({ Serial.println(x); Serial1.println(x); })


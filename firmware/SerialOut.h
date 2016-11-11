#pragma once

#define SerialOut(x) ({ Serial.print(x); Serial2.print(x); })
#define SerialOutln(x) ({ Serial.println(x); Serial2.println(x); })


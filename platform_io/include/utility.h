#ifndef UTILITY
#define UTILITY
#include <Arduino.h>
static int debugLevel{0};

#define sdprintflnx(debugLvl, fmt,...)								    \
do {              												        \
if (debugLvl >= debugLevel) Serial.printf(fmt "\r\n", ##__VA_ARGS__);	\
} while (0)
				
#define sdprintfx(debugLvl, fmt,...)								        \
do {              												        \
if (debugLvl >= debugLevel) Serial.printf(fmt, ##__VA_ARGS__);	        \
} while (0)											

#define sdprintfln(fmt, ...) sdprintflnx(0, fmt, ##__VA_ARGS__) 
#define sdprintf(fmt, ...) sdprintfx(0, fmt, ##__VA_ARGS__) 

template <typename T>
void sdprint(T info, int debugLvl = 0)
{
	sdprintfx(debugLvl, "%s", (String(info)).c_str());
}
template <typename T>
void sdprintln(T info, int debugLvl = 0)
{
	sdprintflnx(debugLvl, "%s", (String(info)).c_str());
}

#endif // UTILITY
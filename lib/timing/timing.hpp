#ifndef TIMING_HPP
#define TIMING_HPP

#include <stdint.h>
#include <Arduino.h>
#include "Debug.hpp"

namespace Timing {

    // Constants
    const uint32_t PULSE_DURATION = 1500;  // Pulse duration of control signals in milliseconds

    // Variables
    extern uint32_t beginReleaseDrogueChute;
    extern uint32_t beginControlDrogueChute;
    extern uint32_t endReleaseDrogueChute;
    extern uint32_t beginReleaseMainChute;
    extern uint32_t beginControlMainChute;
    extern uint32_t endReleaseMainChute;

    // Function declarations
    void startTimer();
    uint32_t combineBytesToTime(uint8_t msb, uint8_t lsb); // NACH UNIT TESTS LÖSCHEN
    void setTimes(const uint8_t dataPackage[]);
    bool checkReleaseDrogue();
    bool checkReleaseMain();
    bool checkControlDrogue();
    bool checkControlMain();
    bool isWithinRange(uint32_t beginTime, uint32_t endTime, const __FlashStringHelper* debugMessage);
    uint32_t calculateTimeSinceStart(); // NACH UNIT TESTS LÖSCHEN

    // Debugging helper functions (optional, depending on your debug strategy)
    #ifdef DEBUG
    void printTimeWindows();
    #endif
}

#endif // TIMING_HPP

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
    extern uint32_t endReleaseDrogueChute;
    extern uint32_t beginReleaseMainChute;
    extern uint32_t endReleaseMainChute;

    extern uint32_t beginControlDrogueChute;
    extern uint32_t endControlDrogueChute;
    extern uint32_t beginControlMainChute;
    extern uint32_t endControlMainChute;

    // Function declarations
    void initialize();
    void calculateControlTimes();
    void setTimes(const uint8_t dataPackage[]);
    bool isWithinReleaseDrogue(uint32_t timeSinceStart);
    bool isWithinReleaseMain(uint32_t timeSinceStart);
    bool isWithinControlDrogue(uint32_t timeSinceStart);
    bool isWithinControlMain(uint32_t timeSinceStart);

    // Debugging helper functions (optional, depending on your debug strategy)
    #ifdef DEBUG
    void printTimeWindows();
    #endif
}

#endif // TIMING_HPP

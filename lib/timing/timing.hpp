#ifndef TIMING_HPP
#define TIMING_HPP

#include <stdint.h>

namespace Timing {

    // Constants
    const uint32_t PULSE_DURATION = 1500;  // Pulse duration of control signals in milliseconds

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

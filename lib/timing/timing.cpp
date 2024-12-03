#include "timing.hpp"
#include <Arduino.h>
#include <main.hpp> // For DEBUG_PRINT macros, if required

namespace Timing {

    // Timing variables
    uint32_t beginReleaseDrogueChute = 0;
    uint32_t endReleaseDrogueChute = 0;
    uint32_t beginReleaseMainChute = 0;
    uint32_t endReleaseMainChute = 0;

    uint32_t beginControlDrogueChute = 0;
    uint32_t endControlDrogueChute = 0;
    uint32_t beginControlMainChute = 0;
    uint32_t endControlMainChute = 0;

    void initialize() {
        calculateControlTimes();
    }

    void calculateControlTimes() {
        beginControlDrogueChute = endReleaseDrogueChute - PULSE_DURATION;
        endControlDrogueChute = endReleaseDrogueChute;
        beginControlMainChute = endReleaseMainChute - PULSE_DURATION;
        endControlMainChute = endReleaseMainChute;
    }

    void setTimes(const uint8_t dataPackage[]) {
        beginReleaseDrogueChute = (dataPackage[0] << 8 | dataPackage[1]) * 100;
        endReleaseDrogueChute = (dataPackage[2] << 8 | dataPackage[3]) * 100;
        beginReleaseMainChute = (dataPackage[4] << 8 | dataPackage[5]) * 100;
        endReleaseMainChute = (dataPackage[6] << 8 | dataPackage[7]) * 100;
        calculateControlTimes();
    }

    bool isWithinReleaseDrogue(uint32_t timeSinceStart) {
        return timeSinceStart >= beginReleaseDrogueChute && timeSinceStart <= endReleaseDrogueChute;
    }

    bool isWithinReleaseMain(uint32_t timeSinceStart) {
        return timeSinceStart >= beginReleaseMainChute && timeSinceStart <= endReleaseMainChute;
    }

    bool isWithinControlDrogue(uint32_t timeSinceStart) {
        return timeSinceStart >= beginControlDrogueChute && timeSinceStart <= endControlDrogueChute;
    }

    bool isWithinControlMain(uint32_t timeSinceStart) {
        return timeSinceStart >= beginControlMainChute && timeSinceStart <= endControlMainChute;
    }

    #ifdef DEBUG
    void printTimeWindows() {
        DEBUG_PRINT("Drogue Release Window: ");
        DEBUG_PRINT(beginReleaseDrogueChute);
        DEBUG_PRINT(" - ");
        DEBUG_PRINTLN(endReleaseDrogueChute);

        DEBUG_PRINT("Main Release Window: ");
        DEBUG_PRINT(beginReleaseMainChute);
        DEBUG_PRINT(" - ");
        DEBUG_PRINTLN(endReleaseMainChute);
    }
    #endif
}

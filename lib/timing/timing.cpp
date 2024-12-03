#include "timing.hpp"

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
        bool newState = timeSinceStart >= beginReleaseDrogueChute && timeSinceStart <= endReleaseDrogueChute;
        #ifdef DEBUG
            static bool oldState = false;
            if(oldState != newState) {
                oldState = newState;
                DEBUG_PRINT(F("Drogue chute release state changed. New State: "));
                DEBUG_PRINTLN(newState);
            }
        #endif
        return newState;
    }

    bool isWithinReleaseMain(uint32_t timeSinceStart) {
        bool newState = timeSinceStart >= beginReleaseMainChute && timeSinceStart <= endReleaseMainChute;
        #ifdef DEBUG
            static bool oldState = false;
            if(oldState != newState) {
                oldState = newState;
                DEBUG_PRINT(F("Main chute release state changed. New State: "));
                DEBUG_PRINTLN(newState);
            }
        #endif
        return newState;
    }

    bool isWithinControlDrogue(uint32_t timeSinceStart) {
        bool newState = timeSinceStart >= beginControlDrogueChute && timeSinceStart <= endControlDrogueChute;
        #ifdef DEBUG
            static bool oldState = false;
            if(oldState != newState) {
                oldState = newState;
                DEBUG_PRINT(F("Drogue chute control state changed. New State: "));
                DEBUG_PRINTLN(newState);
            }
        #endif
        return newState;
    }

    bool isWithinControlMain(uint32_t timeSinceStart) {
        bool newState = timeSinceStart >= beginControlMainChute && timeSinceStart <= endControlMainChute;
        #ifdef DEBUG
            static bool oldState = false;
            if(oldState != newState) {
                oldState = newState;
                DEBUG_PRINT(F("Main chute control state changed. New State: "));
                DEBUG_PRINTLN(newState);
            }
        #endif
        return newState;
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

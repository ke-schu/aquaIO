#include "Timing.hpp"

namespace Timing {

    // Timing variables
    uint32_t beginReleaseDrogueChute = 0;
    uint32_t endReleaseDrogueChute = 0;
    uint32_t beginReleaseMainChute = 0;
    uint32_t endReleaseMainChute = 0;
    uint32_t beginControlDrogueChute = 0;
    uint32_t beginControlMainChute = 0;

    uint32_t millisOnStart = 0;

    void startTimer() {
        millisOnStart = millis();
    }

    uint32_t calculateTimeSinceStart() {
        if (millisOnStart == 0) {
            return 0;
        } else {
            return millis() - millisOnStart;
        }
    }

    // Combines two bytes (MSB and LSB) into a time value (in milliseconds) by scaling the result by 100
    uint32_t combineBytesToTime(uint8_t msb, uint8_t lsb) {
        uint16_t tempInteger = ((msb << 8) | lsb);          // combine two bytes
        return static_cast<uint32_t>(tempInteger) * 100;    // cast to uint32_t and multiply by 100
    }

    void setTimes(const uint8_t dataPackage[]) {
        beginReleaseDrogueChute = combineBytesToTime(dataPackage[0], dataPackage[1]);
        endReleaseDrogueChute = combineBytesToTime(dataPackage[2], dataPackage[3]);
        beginReleaseMainChute = combineBytesToTime(dataPackage[4], dataPackage[5]);
        endReleaseMainChute = combineBytesToTime(dataPackage[6], dataPackage[7]);
        beginControlDrogueChute = endReleaseDrogueChute - PULSE_DURATION;
        beginControlMainChute = endReleaseMainChute - PULSE_DURATION;
        #ifdef DEBUG
             printTimeWindows();
        #endif
    }

    bool isWithinRange(uint32_t beginTime, uint32_t endTime, const __FlashStringHelper* debugMessage) {
        uint32_t timeSinceStart = calculateTimeSinceStart();
        if (timeSinceStart == 0) {
            return false;
        }

        bool newState = timeSinceStart >= beginTime && timeSinceStart <= endTime;

        #ifdef DEBUG
            static bool oldState = false;
            if (oldState != newState) {
                oldState = newState;
                DEBUG_PRINT(debugMessage);
                DEBUG_PRINT(F(" state changed to "));
                DEBUG_PRINTLN(newState);
            }
        #endif

        return newState;
    }

    bool checkReleaseDrogue() {
        return isWithinRange(beginReleaseDrogueChute, endReleaseDrogueChute, F("Drogue chute release"));
    }

    bool checkReleaseMain() {
        return isWithinRange(beginReleaseMainChute, endReleaseMainChute, F("Main chute release"));
    }

    bool checkControlDrogue() {
        return isWithinRange(beginControlDrogueChute, endReleaseDrogueChute, F("Drogue chute control"));
    }

    bool checkControlMain() {
        return isWithinRange(beginControlMainChute, endReleaseMainChute, F("Main chute control"));
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

        DEBUG_PRINT("Drogue Control Window: ");
        DEBUG_PRINT(beginControlDrogueChute);
        DEBUG_PRINT(" - ");
        DEBUG_PRINTLN(endReleaseDrogueChute);

        DEBUG_PRINT("Main Control Window: ");
        DEBUG_PRINT(beginControlMainChute);
        DEBUG_PRINT(" - ");
        DEBUG_PRINTLN(endReleaseMainChute);
    }
    #endif
}

#include "Timing.hpp"

namespace Timing {

    // Timing variables in milliseconds (1000ms = 1s)
    uint32_t beginReleaseDrogueChute = 10000;
    uint32_t endReleaseDrogueChute = 20000;
    uint32_t beginReleaseMainChute = 10000; 
    uint32_t endReleaseMainChute = 20000;
    uint32_t beginControlDrogueChute = 19000;
    uint32_t beginControlMainChute = 19000;

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

    bool isWithinRange(uint32_t beginTime, uint32_t endTime) {
        uint32_t timeSinceStart = calculateTimeSinceStart();
        if (timeSinceStart == 0) {
            return false;
        }
        return timeSinceStart >= beginTime && timeSinceStart <= endTime;
    }

    bool checkReleaseDrogue() {
        bool newState = isWithinRange(beginReleaseDrogueChute, endReleaseDrogueChute);
        #ifdef DEBUG
            static bool oldState = false;
            if (oldState != newState) {
                oldState = newState;
                DEBUG_PRINT(F("Drogue chute release state changed to "));
                DEBUG_PRINTLN(newState);
            }
        #endif
        return newState;
    }

    bool checkReleaseMain() {
        bool newState = isWithinRange(beginReleaseMainChute, endReleaseMainChute);
        #ifdef DEBUG
            static bool oldState = false;
            if (oldState != newState) {
                oldState = newState;
                DEBUG_PRINT(F("Main chute release state changed to "));
                DEBUG_PRINTLN(newState);
            }
        #endif
        return newState;
    }

    bool checkControlDrogue() {
        bool newState = isWithinRange(beginControlDrogueChute, endReleaseDrogueChute);
        #ifdef DEBUG
            static bool oldState = false;
            if (oldState != newState) {
                oldState = newState;
                DEBUG_PRINT(F("Drogue chute control state changed to "));
                DEBUG_PRINTLN(newState);
            }
        #endif
        return newState;
    }

    bool checkControlMain() {
        bool newState = isWithinRange(beginControlMainChute, endReleaseMainChute);
        #ifdef DEBUG
            static bool oldState = false;
            if (oldState != newState) {
                oldState = newState;
                DEBUG_PRINT(F("Main chute control state changed to "));
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

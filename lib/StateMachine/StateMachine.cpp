#include "StateMachine.hpp"

namespace StateMachine {
    // State variables
    bool rocketLaunched = false;
    uint32_t millisOnStart = 0;
    bool timeAdjustMode = false;

    // Constants for commands
    constexpr uint8_t startData = 0b100000;    // Start message for data packet
    constexpr uint8_t launchedState = 0b0110; // State-machine message for rocket launch

    void handleIncomingData() {
        if (Bus::isDataReady()) {
            int len = Bus::getDataLength();
            uint8_t* data = Bus::getDataBuffer();
            
            DEBUG_PRINT("Bytes ready: ");
            DEBUG_PRINTLN(len);

            if (timeAdjustMode) {
                if (len == 20) {
                    Timing::setTimes(data);
                }
                timeAdjustMode = false;
            } else {
                if (len == 1) {
                    checkCommand(data[0]);
                }
            }
            Bus::resetBuffer();
        }
    }

    void checkCommand(uint8_t incomingMsg) {
        switch (incomingMsg) {
            case startData:
                timeAdjustMode = true;
                DEBUG_PRINT("Start-Signal für Daten-Paket empfangen: ");
                break;

            case launchedState:
                if (!rocketLaunched) {
                    rocketLaunched = true;
                    millisOnStart = millis();
                }
                DEBUG_PRINT("Status-Signal Raketenstart empfangen: ");
                break;

            default:
                DEBUG_PRINT("Ungültige Nachricht: ");
                break;
        }
        DEBUG_PRINTLN(incomingMsg);
    }
}

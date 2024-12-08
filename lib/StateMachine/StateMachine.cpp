#include "StateMachine.hpp"

namespace StateMachine {
    // State variables
    bool rocketLaunched = false;
    bool timeAdjustMode = false;

    // Constants for commands
    constexpr uint8_t startData = 0b100000;    // Start message for data packet
    constexpr uint8_t launchedState = 0b0110; // State-machine message for rocket launch

    void handleIncomingData() {
        if (Bus::isDataReady()) {
            int len = Bus::getDataLength();
            uint8_t* data = Bus::getDataBuffer();
            
            DEBUG_PRINT(len);
            DEBUG_PRINTLN(" Byte ready.");

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
                DEBUG_PRINT("Start für Datenpaket empf: ");
                break;

            case launchedState:
                if (!rocketLaunched) {
                    rocketLaunched = true;
                    Timing::startTimer();
                }
                DEBUG_PRINT("Status Raketenstart empf: ");
                break;

            default:
                DEBUG_PRINT("Ungültige Nachricht: ");
                break;
        }
        DEBUG_PRINTLN(incomingMsg);
    }
}

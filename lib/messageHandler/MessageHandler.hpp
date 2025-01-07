#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

#include "Bus.hpp"
#include "Timing.hpp"
#include "Debug.hpp"
#include <Arduino.h>

namespace MessageHandler {
    // State variables
    extern bool rocketLaunched;
    extern uint32_t millisOnStart;
    extern bool timeAdjustMode;

    // Function declarations
    void handleIncomingData();
    void checkCommand(uint8_t incomingMsg);
}

#endif // STATE_MACHINE_HPP

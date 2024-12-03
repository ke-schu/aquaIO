#ifndef PINS_HPP
#define PINS_HPP

#include <stdint.h>
#include <timing.hpp>
#include <Arduino.h>

// Pin definitions
#define RELEASE_DROGUE_PIN PIN_PB0
#define RELEASE_MAIN_PIN PIN_PB1
#define CONTROL_DROGUE_PIN PIN_PA2
#define CONTROL_MAIN_PIN PIN_PA3

namespace Pins {

    // Function declarations
    void setupPins();
    void checkTimers(uint32_t timeSinceStart);
}

#endif // PINS_HPP

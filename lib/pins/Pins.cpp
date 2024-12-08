#include "Pins.hpp"

namespace Pins {
    void setupPins() {
        pinMode(RELEASE_DROGUE_PIN, OUTPUT);
        pinMode(RELEASE_MAIN_PIN, OUTPUT);
        pinMode(CONTROL_DROGUE_PIN, OUTPUT);
        pinMode(CONTROL_MAIN_PIN, OUTPUT);

        digitalWrite(RELEASE_DROGUE_PIN, LOW);
        digitalWrite(RELEASE_MAIN_PIN, LOW);
        digitalWrite(CONTROL_DROGUE_PIN, LOW);
        digitalWrite(CONTROL_MAIN_PIN, LOW);
    }

    void togglePinsByTime() {
        // Check whether the outputs need to be activated now
        bool releaseDrogue = Timing::isWithinReleaseDrogue();
        bool releaseMain = Timing::isWithinReleaseMain();
        bool controlDrogue = Timing::isWithinControlDrogue();
        bool controlMain = Timing::isWithinControlMain();

        // Set outputs
        digitalWrite(RELEASE_DROGUE_PIN, releaseDrogue ? HIGH : LOW);
        digitalWrite(RELEASE_MAIN_PIN, releaseMain ? HIGH : LOW);
        digitalWrite(CONTROL_DROGUE_PIN, controlDrogue ? HIGH : LOW);
        digitalWrite(CONTROL_MAIN_PIN, controlMain ? HIGH : LOW);
    }
}
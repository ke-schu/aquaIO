#include "main.hpp"

// ATTiny84a Software for AquaIO

void setup() {
    #ifdef DEBUG
        Serial.begin(4800);  // Initialize serial communication for debugging
    #endif

    DEBUG_PRINTLN(F("ATtiny84a Program started."));

    // Initialize the modules
    Bus::initialize();
    Pins::setupPins();  // Setup all the pins required by the system
}

void loop() {
    // Handle incoming data and state transitions
    StateMachine::handleIncomingData();

    // If rocket is launched, handle the timers for pin control
    if (StateMachine::rocketLaunched) {
        Pins::togglePinsByTime();  // Handle the state of control pins
    }
}

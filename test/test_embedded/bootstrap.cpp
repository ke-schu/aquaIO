#include <Arduino.h>
#include <unity.h>
#include <test_timing.hpp>
#include <Pins.hpp>
//#include "unity_config.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void setup() {
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);

    UNITY_BEGIN();

    // TIMING
    //RUN_TEST(test_calculateTimeSinceStart);
    //RUN_TEST(test_combineBytesToTime);
    RUN_TEST(test_isWithinRange);

    UNITY_END();

    Pins::setupPins();
}

void loop() {
    digitalWrite(RELEASE_DROGUE_PIN, HIGH);
    digitalWrite(RELEASE_MAIN_PIN, HIGH);
    digitalWrite(CONTROL_DROGUE_PIN, HIGH);
    digitalWrite(CONTROL_MAIN_PIN, HIGH);
    delay(100);
    digitalWrite(RELEASE_DROGUE_PIN, LOW);
    digitalWrite(RELEASE_MAIN_PIN, LOW);
    digitalWrite(CONTROL_DROGUE_PIN, LOW);
    digitalWrite(CONTROL_MAIN_PIN, LOW);
    delay(500);
}
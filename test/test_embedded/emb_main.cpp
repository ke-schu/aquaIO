#include <Arduino.h>
#include <unity.h>
#include <Timing.hpp>
#include <Pins.hpp>
//#include "unity_config.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_calculateControlTimes() {
    // Test für berechnete Kontrollzeiten
    Timing::beginReleaseDrogueChute = 13000;
    Timing::endReleaseDrogueChute = 18000;
    Timing::beginReleaseMainChute = 23000;
    Timing::endReleaseMainChute = 28000;
    
    Timing::calculateControlTimes();
    
    TEST_ASSERT_EQUAL_UINT32(16500, Timing::beginControlDrogueChute);
    TEST_ASSERT_EQUAL_UINT32(18000, Timing::endControlDrogueChute);
    TEST_ASSERT_EQUAL_UINT32(26500, Timing::beginControlMainChute);
    TEST_ASSERT_EQUAL_UINT32(28000, Timing::endControlMainChute);
}

void setup() {
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);

    UNITY_BEGIN();
    RUN_TEST(test_calculateControlTimes);
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
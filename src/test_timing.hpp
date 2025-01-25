#ifndef TEST_EMB_TIMING_HPP
#define TEST_EMB_TIMING_HPP

#include "unity.h"
#include <Timing.hpp>

void test_combineBytesToTime(void) {
    // Return Zero For Zero Inputs
    // 0x00 = 0, 0x00 = 0 -> 0 * 100 = 0
    TEST_ASSERT_EQUAL_UINT32(0, Timing::combineBytesToTime(0, 0));

    // MSB = 1 (0x01), LSB = 0 (0x00) => Kombiniert: 256 * 100 = 25600
    TEST_ASSERT_EQUAL_UINT32(25600, Timing::combineBytesToTime(1, 0));
    
    // MSB = 255 (0xFF), LSB = 255 (0xFF) => Kombiniert: 65535 * 100 = 6553500
    TEST_ASSERT_EQUAL_UINT32(6553500, Timing::combineBytesToTime(255, 255)); //4294967196
    
    // MSB = 0, LSB = 76 (0x4C) => Kombiniert: 76 * 100 = 7600
    TEST_ASSERT_EQUAL_UINT32(7600, Timing::combineBytesToTime(0, 76));

    // MSB = 51 (0x33), LSB = 51 (0x33) => Kombiniert: 13107 * 100 = 1310700
    TEST_ASSERT_EQUAL_UINT32(1310700, Timing::combineBytesToTime(51, 51)); // 4294967276

    // MSB = 128 (0x80), LSB = 128 (0x80) => Kombiniert: 32896 * 100 = 3289600
    TEST_ASSERT_EQUAL_UINT32(3289600, Timing::combineBytesToTime(128, 128)); // 12800

    // MSB = 20 (0x14), LSB = 32 (0x20) => Kombiniert: 5152 * 100 = 515200
    TEST_ASSERT_EQUAL_UINT32(515200, Timing::combineBytesToTime(20, 32)); // 4294958208

    // MSB = 1, LSB = 1 => Kombiniert: 257 * 100 = 25700
    TEST_ASSERT_EQUAL_UINT32(25700, Timing::combineBytesToTime(1, 1));

    // MSB = 128 (0x80), LSB = 0 => Kombiniert: 3276800 * 100 = 3276800
    TEST_ASSERT_EQUAL_UINT32(3276800, Timing::combineBytesToTime(128, 0)); // 0

    // MSB = 254 (0xFE), LSB = 255 (0xFF) => Kombiniert: 65279 * 100 = 6527900
    TEST_ASSERT_EQUAL_UINT32(6527900, Timing::combineBytesToTime(254, 255)); // 4294941596
}

void test_calculateTimeSinceStart(void) {
    uint8_t timeTolerance = 5; // Toleranz von ±5 ms
    
    // Array mit verschiedenen Delays (in ms)
    uint16_t delays[] = {0, 400, 1500, 3000, 4500, 6000}; // Beispiel-Delays
    uint32_t expectedTimes[] = {0, 400, 1900, 4900, 9400, 15400}; // Erwartete Zeit nach jedem Delay (delays aufsummiert)
    uint32_t actualTimes[sizeof(delays)/sizeof(delays[0])];

    // Rakete noch nicht gestartet
    uint32_t beforeStartTime = Timing::calculateTimeSinceStart();

    // Rakete wird gestartet
    Timing::startTimer();
    actualTimes[0] = Timing::calculateTimeSinceStart();

    // Rakete fliegt und berechnet die Zeiten nach jedem Delay
    delay(delays[1]);
    actualTimes[1] = Timing::calculateTimeSinceStart();

    delay(delays[2]);
    actualTimes[2] = Timing::calculateTimeSinceStart();

    delay(delays[3]);
    actualTimes[3] = Timing::calculateTimeSinceStart();

    delay(delays[4]);
    actualTimes[4] = Timing::calculateTimeSinceStart();

    delay(delays[5]);
    actualTimes[5] = Timing::calculateTimeSinceStart();

    // Messungen prüfen
    TEST_ASSERT_EQUAL_UINT32(0, beforeStartTime);                       // timeSinceStart muss vor Start genau 0 betragen
    for (size_t i = 0; i < sizeof(delays)/sizeof(delays[0]); ++i) {     // Tests nach den Delays
        TEST_ASSERT_UINT32_WITHIN(timeTolerance, expectedTimes[i], actualTimes[i]);
    }
}

void test_isWithinRange(void) {
    bool testFalse0 = Timing::isWithinRange(0, 500, F("Test"));
    Timing::startTimer();
    delay(500);

    bool testFalse1 = Timing::isWithinRange(0, 499, F("Test"));
    bool testTrue = Timing::isWithinRange(499, 505, F("Test"));    
    bool testFalse2 = Timing::isWithinRange(506, 5000, F("Test"));

    // Keine Methodenaufrufe im TEST_ASSERT!
    TEST_ASSERT_FALSE(testFalse0);
    TEST_ASSERT_TRUE(testTrue);
    TEST_ASSERT_FALSE(testFalse1);
    TEST_ASSERT_FALSE(testFalse2);
}


void test_setTimes() {
    const uint8_t dataPackage[] = { // Example dataPackage
        0x01, 0x02, // 0x0102 = 258 * 100 = 25800 ms
        0x03, 0x04, // 0x0304 = 772 * 100 = 77200 ms
        0x05, 0x06, // 0x0506 = 1286 * 100 = 128600 ms
        0x07, 0x08  // 0x0708 = 1800 * 100 = 180000 ms
    };

    Timing::setTimes(dataPackage);  // Function Call

    TEST_ASSERT_EQUAL_UINT32(25800, Timing::beginReleaseDrogueChute);
    TEST_ASSERT_EQUAL_UINT32(77200, Timing::endReleaseDrogueChute);
    TEST_ASSERT_EQUAL_UINT32(128600, Timing::beginReleaseMainChute);
    TEST_ASSERT_EQUAL_UINT32(180000, Timing::endReleaseMainChute);
    TEST_ASSERT_EQUAL_UINT32(76200, Timing::beginControlDrogueChute);
    TEST_ASSERT_EQUAL_UINT32(179000, Timing::beginControlMainChute);
}


#endif // TEST_EMB_TIMING_HPP

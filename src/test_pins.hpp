#ifndef TEST_EMB_PINS_HPP
#define TEST_EMB_PINS_HPP

#include "unity.h"
#include <Pins.hpp>
#include <Arduino.h>

void test_setupPins_sets_all_pins_low() {
    // Act: Rufe die Funktion auf
    Pins::setupPins();

    // Assert: Prüfe, ob alle Pins auf LOW gesetzt wurden
    TEST_ASSERT_EQUAL(LOW, digitalRead(RELEASE_DROGUE_PIN));
    TEST_ASSERT_EQUAL(LOW, digitalRead(RELEASE_MAIN_PIN));
    TEST_ASSERT_EQUAL(LOW, digitalRead(CONTROL_DROGUE_PIN));
    TEST_ASSERT_EQUAL(LOW, digitalRead(CONTROL_MAIN_PIN));
}

#endif // TEST_EMB_PINS_HPP
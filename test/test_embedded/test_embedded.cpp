#include <Arduino.h>
#include <unity.h>
//#include "main.hpp"  // Zugriff auf Funktionen und Variablen aus main.cpp
//#include "unity_config.h"

const uint32_t PULSE_DURATION = 1500;  // Pulse duration of control signals in Millis

// Drogue chute time window settings for release (time in milliseconds)
// Enter the default values here!
uint32_t beginReleaseDrogueChute = 0; //13000
uint32_t endReleaseDrogueChute = 0;   //18000

// Main chute time windows settings for release (time in milliseconds)
// Enter the default values here!
uint32_t beginReleaseMainChute = 0; //23000
uint32_t endReleaseMainChute = 0;   //28000

// Control signals for drogue chute in last instance (time in milliseconds)
// Calculated from the release window and the PULSE_DURATION, a change here has no effect!
uint32_t beginControlDrogueChute = 0;
uint32_t endControlDrogueChute = 0;

// Control signals for main chute in last instance (time in milliseconds)
// Calculated from the release window and the PULSE_DURATION, a change here has no effect!
uint32_t beginControlMainChute = 0;
uint32_t endControlMainChute = 0;

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void calculateControlTimes() {
    beginControlDrogueChute = endReleaseDrogueChute - PULSE_DURATION;
    endControlDrogueChute = endReleaseDrogueChute;
    beginControlMainChute = endReleaseMainChute - PULSE_DURATION;
    endControlMainChute = endReleaseMainChute;
}

void test_calculateControlTimes() {
    // Test für berechnete Kontrollzeiten
    beginReleaseDrogueChute = 13000;
    endReleaseDrogueChute = 18000;
    beginReleaseMainChute = 23000;
    endReleaseMainChute = 28000;
    
    calculateControlTimes();
    
    TEST_ASSERT_EQUAL_UINT32(16500, beginControlDrogueChute);
    TEST_ASSERT_EQUAL_UINT32(18000, endControlDrogueChute);
    TEST_ASSERT_EQUAL_UINT32(26500, beginControlMainChute);
    TEST_ASSERT_EQUAL_UINT32(28000, endControlMainChute);
}

void setup() {
    //softSerialTest.begin(2400);       // Start der seriellen Verbindung
    //Serial.begin(2400);       // Start der seriellen Verbindung
    Serial.setTxBit(PIN_PA1);
    delay(3000);
    //softSerialTest.println("Starting Tests...");  // Debug-Ausgabe
    //delay(1000);  // Kleine Verzögerung vor Unity-Initialisierung
    UNITY_BEGIN();
    
    //Testfälle registrieren
    RUN_TEST(test_calculateControlTimes);
    
    UNITY_END();
    //softSerialTest.println("Tests Completed.");  // Debug-Ausgabe
}

void loop() {
    // Für Unity-Tests leer lassen
}

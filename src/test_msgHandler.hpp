#ifndef TEST_EMB_MSG_HANDLER_HPP
#define TEST_EMB_MSG_HANDLER_HPP

#include <Arduino.h>
#include <unity.h>
#include <MessageHandler.hpp>
#include <Timing.hpp>


// Konstanten
constexpr uint8_t startData = 0b100000;    // Start message for data packet
constexpr uint8_t launchedState = 0b0110; // State-machine message for rocket launch

// Tests
void test_checkCommand_startData() {
    TEST_ASSERT_FALSE(MessageHandler::timeAdjustMode); // timeAdjustMode sollte false sein
    
    // Act
    MessageHandler::checkCommand(startData);
    
    // Assert
    TEST_ASSERT_TRUE(MessageHandler::timeAdjustMode); // timeAdjustMode sollte true sein
}

void test_checkCommand_launchedState() {
    uint32_t time1 = Timing::calculateTimeSinceStart();

    // Assert
    TEST_ASSERT_FALSE(MessageHandler::rocketLaunched);       // rocketLaunched sollte false sein

    // Act
    MessageHandler::checkCommand(launchedState);
    delay(200);
    uint32_t time2 = Timing::calculateTimeSinceStart();
    TEST_ASSERT_TRUE(MessageHandler::rocketLaunched);       // rocketLaunched sollte true sein
    
    // Act
    MessageHandler::checkCommand(launchedState);
    delay(200);
    uint32_t time3 = Timing::calculateTimeSinceStart();
    
    // Assert
    TEST_ASSERT_TRUE(MessageHandler::rocketLaunched);       // rocketLaunched sollte true sein
    TEST_ASSERT_EQUAL_UINT32(0, time1); // Timer sollte gestartet sein
    TEST_ASSERT_GREATER_THAN_UINT32(1, time2); // Timer sollte gestartet sein
    TEST_ASSERT_GREATER_THAN_UINT32(time2, time3); // Timer sollte gestartet sein
}

void test_checkCommand_invalidMessage() {
    // Act
    MessageHandler::checkCommand(0xFF); // Ungültige Nachricht
    
    // Assert
    TEST_ASSERT_FALSE(MessageHandler::rocketLaunched);       // rocketLaunched sollte false sein
    TEST_ASSERT_FALSE(MessageHandler::timeAdjustMode); // timeAdjustMode sollte false sein
}

void test_handleIncomingData_noTimeAdjust() {
    
}

#endif // TEST_EMB_MSG_HANDLER_HPP
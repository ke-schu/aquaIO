// main.h

#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>
#include <stdbool.h>

// Deklarationen der globalen Variablen
extern uint32_t beginReleaseDrogueChute;
extern uint32_t endReleaseDrogueChute;
extern uint32_t beginReleaseMainChute;
extern uint32_t endReleaseMainChute;
extern uint32_t beginControlDrogueChute;
extern uint32_t endControlDrogueChute;
extern uint32_t beginControlMainChute;
extern uint32_t endControlMainChute;
extern bool rocketLaunched;
extern uint32_t millisOnStart;
extern bool timeAdjustMode;
extern bool bytes_ready;
extern int bytes_read;
extern uint8_t* recieve_buffer;

// Deklaration der Funktionen
void setPinHighOrLow(volatile uint8_t *port, uint8_t pin, bool value);
void calculateControlTimes();
void checkTimers(uint32_t timeSinceStart);
int concat_bytes(uint8_t byteA, uint8_t byteB);
void checkCmd(uint8_t incomingMsg);
void setTimes(uint8_t dataPackage[]);
void on_recieve(int len);
void initBus();

#endif // MAIN_H

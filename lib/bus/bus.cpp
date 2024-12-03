#include "Bus.hpp"

namespace Bus {
    constexpr int BUFFER_SIZE = 32;
    uint8_t receiveBuffer[BUFFER_SIZE] = {0};
    bool dataReady = false;
    int dataLength = 0;

    void initialize() {
        Wire.begin(AQUA_IO_ADDRESS);
        Wire.onReceive(&onReceive);
        DEBUG_PRINTLN("Bus initialisiert.");
    }

    void onReceive(int len) {
        if (dataReady) return;

        memset(receiveBuffer, 0, BUFFER_SIZE);
        int i = 0;
        while (Wire.available() && i < BUFFER_SIZE) {
            receiveBuffer[i] = Wire.read();
            i++;
        }
        dataReady = true;
        dataLength = len;
    }

    bool isDataReady() {
        return dataReady;
    }

    int getDataLength() {
        return dataLength;
    }

    uint8_t* getDataBuffer() {
        return receiveBuffer;
    }

    void resetBuffer() {
        dataReady = false;
        dataLength = 0;
    }
}

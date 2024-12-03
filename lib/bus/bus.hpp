#ifndef BUS_HPP
#define BUS_HPP

#include "Debug.hpp"
#include <Arduino.h>
#include <stdint.h>
#include <Wire.h>
#include <string.h>

namespace Bus {

    // Constants
    const uint8_t AQUA_IO_ADDRESS = 42;    // I2C address for broadcast communication with AquaBrain (This uC is I2C-Slave)

    // Function declarations
    void initialize();
    void onReceive(int len);
    bool isDataReady();
    int getDataLength();
    uint8_t* getDataBuffer();
    void resetBuffer();
}

#endif // BUS_HPP

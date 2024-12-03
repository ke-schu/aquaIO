#ifndef BUS_HPP
#define BUS_HPP

#include <stdint.h>

namespace Bus {
    void initialize(uint8_t address);
    void onReceive(int len);
    bool isDataReady();
    int getDataLength();
    uint8_t* getDataBuffer();
    void resetBuffer();
}

#endif // BUS_HPP

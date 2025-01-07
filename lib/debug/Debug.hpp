/*
    ATTENTION: Activate debug only for test purposes; deactivate for actual use
    -> A lot of computing time is wasted on serial output
*/
//#define DEBUG

#ifdef DEBUG
    #warning "DEBUG is defined!"
    #define DEBUG_PRINT(x) Serial.print(x)
    #define DEBUG_PRINTLN(x) Serial.println(x)
#else
    #define DEBUG_PRINT(x)
    #define DEBUG_PRINTLN(x)
#endif
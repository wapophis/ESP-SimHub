#pragma once
#include "I2CTransportMaster.h"
#include "I2CTransportSlave.h"

/***
 * "This Manager is responsible for configuring the behavior based on the master-slave role for I2C communication."
*/
class I2CTransportManager  {
    public:
       static I2CTransportMaster tm;
       static I2CTransportSlave ts;

    static void setup(FullLoopbackStream *outgoingStream){
        #if I2C_MASTER
            #if I2C_SERIAL_BYPASS_DEBUG
                Serial.begin(115200);
                Serial.print("\nSetup as Master\n");
                Serial.flush();
            #endif
        tm.setup(outgoingStream);
        #endif

        #if I2C_BYPASS_SLAVE
        Serial.print("Setup as Slave");
        Serial.flush();
        ts.setup(outgoingStream);
        #endif
    }
    static void loop(){
        #ifdef I2C_MASTER
        tm.loop();
        #endif

        #ifdef I2C_BYPASS_SLAVE
        ts.loop();
        #endif
    }

    static void flush(){
        #ifdef I2C_MASTER
            tm.flush();
        #endif

        #ifdef I2C_BYPASS_SLAVE
            ts.flush();
        #endif
    }
};

#if I2C_MASTER
#define StreamAvailable WIRE.available
#define FlowSerialFlush WIRE.flush
#define StreamFlush WIRE.flush
#define StreamWrite outgoingStream.write
#define StreamPrint WIRE.print
/** SETUP SERIAL BYPASS I2C SLAVE, USE WHEN THIS DEVICE IS CONNECTED TO SIMHUB*/
#define FlowSerialBegin [](unsigned long baud) { Serial.printf("Hola mundo");}
#endif
// #if IC_SLAVE
// #define StreamRead Serial.read
// #define StreamFlush Serial.flush
// #define StreamWrite Serial.write
// #define StreamPrint Serial.print
// #define StreamAvailable Serial.available
// #define FlowSerialBegin [](unsigned long baud) { Serial.begin(baud);}
// #endif
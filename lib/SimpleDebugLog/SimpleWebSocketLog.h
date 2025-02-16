#ifndef SIMPLEWEBSOCKETLOG_H
#define SIMPLEWEBSOCKETLOG_H

#include <Arduino.h>

// #define DEBUGLOG_DISABLE_WEBSOCKET_LOG // uncomment this line to disable all debug logs

#if not defined(DEBUGLOG_DISABLE_WEBSOCKET_LOG)

// You can configure output Serial here
#define PRINT_WS(fmt, ...) ws.printfAll("{\"type\":\"log\",\"message\":\"" fmt "\"}", __VA_ARGS__)

#define LOG_WEBSOCKET(fmt, ...) PRINT_WS(fmt, __VA_ARGS__)

#endif

#endif
#ifndef SIMPLE_DEBUG_LOG
  #define SIMPLE_DEBUG_LOG
#endif

#include <Arduino.h>

//#define DEBUGLOG_DISABLE_LOG // uncomment this line to disable all debug logs

#if not defined(DEBUG_LOG_DISBALE)

  // You can configure output Serial here
  #define PRINT(x) Serial.print(x)
  #define PRINT_LN(x) Serial.println(x)

  // You can configure output style here
  #define LOG_ERROR_HANDLER(x) {PRINT("[ERROR] "); PRINT_LN(x);}
  #define LOG_ERROR_WITH_VALUE_HANDLER(x, y) {PRINT("[ERROR] "); PRINT(x); PRINT_LN(y);}
  #define LOG_WARN_HANDLER(x) {PRINT("[WARNING] "); PRINT_LN(x);}
  #define LOGWARN_WITH_VALUE_HANDLER(x, y) {PRINT("[WARNING] "); PRINT(x); PRINT_LN(y);}
  #define LOG_INFO_HANDLER(x) {PRINT("[INFO] "); PRINT_LN(x);}
  #define LOG_INFO_WITH_VALUE_HANDLER(x, y) {PRINT("[INFO] "); PRINT(x); PRINT_LN(y);}
  #define LOG_DEBUG_HANDLER(x) {PRINT("[DEBUG] "); PRINT_LN(x);}
  #define LOG_DEBUG_WITH_VALUE_HANDLER(x, y) {PRINT("[DEBUG] "); PRINT(x); PRINT_LN(y);}
  #define LOG_TRACE_HANDLER(x) {PRINT("[TRACE] "); PRINT_LN(x);}
  #define LOG_TRACE_WITH_VALUE_HANDLER(x, y) {PRINT("[TRACE] "); PRINT(x); PRINT_LN(y);}
  
#endif

#if defined(DEBUGLOG_DISABLE_LOG)
  #define LOG_ERROR(x)
  #define LOG_ERROR_WITH_VALUE(x, y)
  #define LOG_WARN(x)
  #define LOG_WARN_WITH_VALUE(x, y)
  #define LOG_INFO(x)
  #define LOG_INFO_WITH_VALUE(x, y)
  #define LOG_DEBUG(x)
  #define LOG_DEBUG_WITH_VALUE(x, y)
  #define LOG_TRACE(x)
  #define LOG_TRACE_WITH_VALUE(x, y)
#elif defined(DEBUGLOG_DEFAULT_LOG_LEVEL_ERROR)
  #define LOG_ERROR(x) LOG_ERROR_HANDLER(x)
  #define LOG_ERROR_WITH_VALUE(x, y) LOG_ERROR_WITH_VALUE_HANDLER(x, y)
  #define LOG_WARN(x)
  #define LOG_WARN_WITH_VALUE(x, y)
  #define LOG_INFO(x)
  #define LOG_INFO_WITH_VALUE(x, y)
  #define LOG_DEBUG(x)
  #define LOG_DEBUG_WITH_VALUE(x, y)
  #define LOG_TRACE(x)
  #define LOG_TRACE_WITH_VALUE(x, y)
#elif defined(DEBUGLOG_DEFAULT_LOG_LEVEL_WARN)
  #define LOG_ERROR(x) LOG_ERROR_HANDLER(x)
  #define LOG_ERROR_WITH_VALUE(x, y) LOG_ERROR_WITH_VALUE_HANDLER(x, y)
  #define LOG_WARN(x) LOG_WARN_HANDLER(x)
  #define LOGWARN_WITH_VALUE(x, y) LOGWARN_WITH_VALUE_HANDLER(x, y)
  #define LOG_INFO(...)
  #define LOG_DEBUG(x)
  #define LOG_DEBUG_WITH_VALUE(x, y)
  #define LOG_TRACE(x)
  #define LOG_TRACE_WITH_VALUE(x, y)
#elif defined(DEBUGLOG_DEFAULT_LOG_LEVEL_INFO)
  #define LOG_ERROR(x) LOG_ERROR_HANDLER(x)
  #define LOG_ERROR_WITH_VALUE(x, y) LOG_ERROR_WITH_VALUE_HANDLER(x, y)
  #define LOG_WARN(x) LOG_WARN_HANDLER(x)
  #define LOGWARN_WITH_VALUE(x, y) LOGWARN_WITH_VALUE_HANDLER(x, y)
  #define LOG_INFO(x) LOG_INFO_HANDLER(x)
  #define LOG_INFO_WITH_VALUE(x, y) LOG_INFO_WITH_VALUE_HANDLER(x, y)
  #define LOG_DEBUG(x)
  #define LOG_DEBUG_WITH_VALUE(x, y)
  #define LOG_TRACE(x)
  #define LOG_TRACE_WITH_VALUE(x, y)
#elif defined(DEBUGLOG_DEFAULT_LOG_LEVEL_DEBUG)
  #define LOG_ERROR(x) LOG_ERROR_HANDLER(x)
  #define LOG_ERROR_WITH_VALUE(x, y) LOG_ERROR_WITH_VALUE_HANDLER(x, y)
  #define LOG_WARN(x) LOG_WARN_HANDLER(x)
  #define LOGWARN_WITH_VALUE(x, y) LOGWARN_WITH_VALUE_HANDLER(x, y)
  #define LOG_INFO(x) LOG_INFO_HANDLER(x)
  #define LOG_INFO_WITH_VALUE(x, y) LOG_INFO_WITH_VALUE_HANDLER(x, y)
  #define LOG_DEBUG(x) LOG_DEBUG_HANDLER(x)
  #define LOG_DEBUG_WITH_VALUE(x, y) LOG_DEBUG_WITH_VALUE_HANDLER(x, y)
  #define LOG_TRACE(x) LOG_TRACE_HANDLER(x)
  #define LOG_TRACE(x)
  #define LOG_TRACE_WITH_VALUE(x, y)
#elif defined(DEBUGLOG_DEFAULT_LOG_LEVEL_TRACE)
  #define LOG_ERROR(x) LOG_ERROR_HANDLER(x)
  #define LOG_ERROR_WITH_VALUE(x, y) LOG_ERROR_WITH_VALUE_HANDLER(x, y)
  #define LOG_WARN(x) LOG_WARN_HANDLER(x)
  #define LOGWARN_WITH_VALUE(x, y) LOGWARN_WITH_VALUE_HANDLER(x, y)
  #define LOG_INFO(x) LOG_INFO_HANDLER(x)
  #define LOG_INFO_WITH_VALUE(x, y) LOG_INFO_WITH_VALUE_HANDLER(x, y)
  #define LOG_DEBUG(x) LOG_DEBUG_HANDLER(x)
  #define LOG_DEBUG_WITH_VALUE(x, y) LOG_DEBUG_WITH_VALUE_HANDLER(x, y)
  #define LOG_TRACE(x) LOG_TRACE_HANDLER(x)
  #define LOG_TRACE_WITH_VALUE(x, y) LOG_TRACE_WITH_VALUE_HANDLER(x, y)
#else
  #warning "Defaulting to a log level of: DEBUGLOG_DEFAULT_LOG_LEVEL_TRACE"
  #define LOG_ERROR(x) LOG_ERROR_HANDLER(x)
  #define LOG_ERROR_WITH_VALUE(x, y) LOG_ERROR_WITH_VALUE_HANDLER(x, y)
  #define LOG_WARN(x) LOG_WARN_HANDLER(x)
  #define LOGWARN_WITH_VALUE(x, y) LOGWARN_WITH_VALUE_HANDLER(x, y)
  #define LOG_INFO(x) LOG_INFO_HANDLER(x)
  #define LOG_INFO_WITH_VALUE(x, y) LOG_INFO_WITH_VALUE_HANDLER(x, y)
  #define LOG_DEBUG(x) LOG_DEBUG_HANDLER(x)
  #define LOG_DEBUG_WITH_VALUE(x, y) LOG_DEBUG_WITH_VALUE_HANDLER(x, y)
  #define LOG_TRACE(x) LOG_TRACE_HANDLER(x)
  #define LOG_TRACE_WITH_VALUE(x, y) LOG_TRACE_WITH_VALUE_HANDLER(x, y)
#endif
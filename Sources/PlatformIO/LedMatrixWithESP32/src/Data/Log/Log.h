#ifndef LOG_H
#define LOG_H

#include <Arduino.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include "LogType.h"
#include "Data/Utils/EnumHelpers.h"

class Log {
public:
    static Log& Instance() {
        static Log instance;
        return instance;
    }

    void write(const std::string& message, LogType logType = LogType::INFO) {
        switch (logType) {
            case LogType::INFO:
                std::cout << EnumHelpers::logTypeHelper.ToString(logType) << ": " << message << std::endl;
                break;
            case LogType::DEBUG:
                std::cout << EnumHelpers::logTypeHelper.ToString(logType) << ": " << message << std::endl;
                break;
            case LogType::ERROR:
                std::cerr << EnumHelpers::logTypeHelper.ToString(logType) << ": " << message << std::endl;
                break;
        }
    }

    void writeBufferInHexFormat(const uint8_t* buffer, size_t size, LogType logType = LogType::INFO) {
        std::ostringstream oss;
        for (size_t i = 0; i < size; ++i) {
            oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(buffer[i]);
        }
        write(oss.str(), logType);
    }

    Log(const Log&) = delete;
    Log& operator=(const Log&) = delete;

private:
    Log() = default;
    ~Log() = default;
};

inline void log(const char* message, LogType logType = LogType::INFO) {
    Log::Instance().write(std::string(message), logType);
}

inline void log(const std::string& message, LogType logType = LogType::INFO) {
    Log::Instance().write(message, logType);
}

inline void log(const String& message, LogType logType = LogType::INFO) {
    Log::Instance().write(std::string(message.c_str()), logType);
}

inline void logBufferHex(const uint8_t* buffer, size_t size, LogType logType = LogType::INFO) {
    Log::Instance().writeBufferInHexFormat(buffer, size, logType);
}

#endif // LOG_H

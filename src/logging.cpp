#include "raylib.h"
#include <fstream>
#include <cstdarg>
#include "logging.hpp"
#include <cstring>
#include <ctime>

static std::ofstream logFile;
static std::ofstream errorFile;

static const char* LogLevelToString(int level)
{
    switch (level)
    {
        case LOG_TRACE: return "TRACE";
        case LOG_DEBUG: return "DEBUG";
        case LOG_INFO:  return "INFO";
        case LOG_WARNING: return "WARNING";
        case LOG_ERROR: return "ERROR";
        case LOG_FATAL: return "FATAL";
        default: return "UNKNOWN";
    }
}

void LogToFile(int logLevel, const char* message)
{
    std::ofstream file;

    if (logLevel >= LOG_ERROR)
        file.open("logs/build_errors.log", std::ios::app);
    else
        file.open("logs/build.log", std::ios::app);

    if (!file.is_open()) return;

    std::time_t now = std::time(nullptr);
    char timeBuf[32];
    std::strftime(timeBuf, sizeof(timeBuf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));

    file << "[" << timeBuf << "] "
         << LogLevelToString(logLevel) << ": "
         << message << "\n";
}

void RaylibLogCallback(int logLevel, const char* text, va_list args)
{
    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), text, args);

    LogToFile(logLevel, buffer);
}

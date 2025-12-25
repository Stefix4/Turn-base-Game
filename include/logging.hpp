#pragma once

void RaylibLogCallback(int logLevel, const char* text, va_list args);
void LogToFile(int logLevel, const char* message);

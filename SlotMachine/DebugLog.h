#pragma once
#include <windows.h>
#include <string>

static void DebugLog(const std::string& message)
{
    OutputDebugStringA((message + "\n").c_str());
}

static void DebugLog(int message) 
{
    DebugLog(std::to_string(message)); 
}

static void DebugLog(float message)
{
    DebugLog(std::to_string(message));
}

static void DebugLog(bool message)
{
    DebugLog(message ? std::string("true") : std::string("false"));
}

static void DebugLog(const char* message)
{
    DebugLog(std::string(message));
}
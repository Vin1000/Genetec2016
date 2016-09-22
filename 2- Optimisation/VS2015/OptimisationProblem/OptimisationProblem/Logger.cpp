#include "stdafx.h"
#include "Logger.h"

#include "FileWriter.h"

#include <iostream>
#include <mutex>

namespace
{
    const std::string LogFile  = LOGFILEPATH;
    std::mutex sMutex;

    void Log(const std::string s)
    {
        sMutex.lock();

        {FileWriter f;
        if (f.Open(LogFile))
        {
            f.Write(s);
        }
        else
        {
            Logger::Error("Failed to write to log file.");
        }}

        sMutex.unlock();
    }
}

Logger::Logger()
{
}


Logger::~Logger()
{
}

void Logger::Info(const std::string s)
{
    Log("INFO: " + s);
}

void Logger::Warning(const std::string s)
{
    Log("WARN: " + s);
}

void Logger::Error(const std::string s)
{
    Log(" ERR: " + s);
}

void Logger::LineJump()
{
    Log("");
}

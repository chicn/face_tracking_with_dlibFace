#pragma once

#include <string>
#include <chrono>

class ElapsedTimer {
public:
    ElapsedTimer(const std::string& name);
    ~ElapsedTimer();
    void end();
private:
    std::string m_name;
    std::chrono::steady_clock::time_point m_startTime;
    bool m_ended = false;
};

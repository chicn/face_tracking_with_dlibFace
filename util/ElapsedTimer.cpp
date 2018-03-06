#include "ElapsedTimer.hpp"
#include <iostream>

ElapsedTimer::ElapsedTimer(const std::string &name) : m_name(name) {
    m_startTime = std::chrono::steady_clock::now();
}

ElapsedTimer::~ElapsedTimer() {
    end();
}

void ElapsedTimer::end() {
    if (m_ended) {
        return;
    }
    auto endTime = std::chrono::steady_clock::now();
    auto elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - m_startTime);
    std::cout << m_name << ": " << elapsedMs.count() << "ms" << std::endl;
    m_ended = true;
}

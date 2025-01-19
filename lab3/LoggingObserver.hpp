#pragma once

#include <fstream>
#include "IObserver.hpp"

template <typename T>
class LoggingObserver : public IObserver<T> {
private:
    std::string logFile;
public:
    explicit LoggingObserver(const std::string& fileName) : logFile(fileName) {}

    void onEvent(const T& eventData) override {
        std::ofstream out(logFile, std::ios::app);
        if (out.is_open()) {
            out << "LoggingObserver: " << eventData << std::endl;
        }
    }
};
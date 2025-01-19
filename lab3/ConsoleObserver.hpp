#pragma once

#include <iostream>
#include "IObserver.hpp"

template <typename T>
class ConsoleObserver : public IObserver<T> {
public:
    void onEvent(const T& eventData) override {
        std::cout << "ConsoleObserver: " << eventData << std::endl;
    }
};
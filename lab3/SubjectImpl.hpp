#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include "IObserver.hpp"

template <typename T>
class Subject<T>::SubjectImpl {
public:
    void attach(std::shared_ptr<IObserver<T>> observer) {
        observers.push_back(observer);
    }

    void detach(std::shared_ptr<IObserver<T>> observer) {
        observers.erase(
            std::remove(observers.begin(), observers.end(), observer),
            observers.end());
    }

    void notify(const T& eventData) {
        for (const auto& observer : observers) {
            if (observer) {
                observer->onEvent(eventData);
            }
        }
    }

private:
    std::vector<std::shared_ptr<IObserver<T>>> observers;
};

template <typename T>
Subject<T>::Subject() : impl(std::make_unique<SubjectImpl>()) {}

template <typename T>
Subject<T>::~Subject() = default;

template <typename T>
void Subject<T>::attach(std::shared_ptr<IObserver<T>> observer) {
    impl->attach(observer);
}

template <typename T>
void Subject<T>::detach(std::shared_ptr<IObserver<T>> observer) {
    impl->detach(observer);
}

template <typename T>
void Subject<T>::notify(const T& eventData) {
    impl->notify(eventData);
}
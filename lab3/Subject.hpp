#pragma once
#include <memory>


template <typename T>
class IObserver;

template <typename T>
class Subject {
public:
    Subject();
    ~Subject();

    void attach(std::shared_ptr<IObserver<T>> observer);
    void detach(std::shared_ptr<IObserver<T>> observer);
    void notify(const T& eventData);

private:
    class SubjectImpl;
    std::unique_ptr<SubjectImpl> impl;
};

#include "SubjectImpl.hpp"


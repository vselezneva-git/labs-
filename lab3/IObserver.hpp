#pragma once
template <typename T>
class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void onEvent(const T& eventData) = 0;
};
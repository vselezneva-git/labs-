#pragma once
#include "ICell.hpp"

class DeadCell : public ICell
{
public:
    bool isAlive() const override { return false; }
    void setAlive(bool alive) override {
        (void)alive;
    }
};

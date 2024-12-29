#pragma once
#include "ICell.hpp"

class LiveCell : public ICell
{
public:
    bool isAlive() const override { return true; }
    void setAlive(bool alive) override {
        (void)alive; 
    }
};

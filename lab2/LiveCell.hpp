#pragma once
#include "ICell.hpp"

class LiveCell : public ICell
{
public:
    bool isAlive() const override;
    void setAlive(bool alive) override;
};

#pragma once
#include "ICell.hpp"

class DeadCell : public ICell
{
public:
    bool isAlive() const override;
    void setAlive(bool alive) override;
};

#pragma once

class ICell
{
public:
    virtual ~ICell() = default;
    virtual bool isAlive() const = 0;
    virtual void setAlive(bool alive) = 0;
};

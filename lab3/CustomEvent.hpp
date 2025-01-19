#pragma once

#include <string>
#include <iostream>

class CustomEvent {
public:
    std::string id;
    std::string type;

    friend std::ostream& operator<<(std::ostream& os, const CustomEvent& event) {
        os << "ID: " << event.id << ", Type: " << event.type;
        return os;
    }
};
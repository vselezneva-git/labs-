#pragma once

#include <SFML/Graphics.hpp>
#include "Model.hpp"
#include "View.hpp"

class Controller
{
public:
    Controller(Model& model, View& view);

    void run();

private:
    Model& m_model;
    View&  m_view;

    bool   m_isPlaying;
    int    m_delay;

    void processEvents(sf::RenderWindow& window);
};

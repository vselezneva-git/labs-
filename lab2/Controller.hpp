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
    void processEvents(sf::RenderWindow& window);
    void handleKeyPress(const sf::Event::KeyEvent& keyEvent);
    void handleMousePress(const sf::Event::MouseButtonEvent& mouseEvent);

    Model& m_model;
    View&  m_view;

    bool m_isPlaying;
    int  m_delay;

};

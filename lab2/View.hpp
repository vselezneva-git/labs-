#pragma once

#include <SFML/Graphics.hpp>
#include "Model.hpp"


class View
{
public:
    View(Model& model, int cellSize);

    void draw(sf::RenderWindow& window);
    void drawUI(sf::RenderWindow& window, bool isPlaying, int delay);

private:
    void setText(sf::Text& text, const std::string& str);

    Model& m_model;
    int m_cellSize;

    sf::Font m_font;
    sf::Text m_textPause;
    sf::Text m_textPlay;
    sf::Text m_textToggle;
    sf::Text m_textSpeed;
};

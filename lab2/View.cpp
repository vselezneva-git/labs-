#include "View.hpp"
#include <iostream>

static const sf::Color WHITE = sf::Color::White;
static const sf::Color BLACK = sf::Color::Black;
static const sf::Color GRAY  = sf::Color(153, 153, 153);

View::View(Model& model, int cellSize)
    : m_model(model)
    , m_cellSize(cellSize)
{
    if (!m_font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load font arial.ttf\n";
    }

    m_textPause.setFont(m_font);
    m_textPause.setCharacterSize(15);
    m_textPause.setFillColor(BLACK);
    m_textPause.setString("Press 'p' to pause.");

    m_textPlay.setFont(m_font);
    m_textPlay.setCharacterSize(15);
    m_textPlay.setFillColor(BLACK);
    m_textPlay.setString("Press 'p' to play.");

    m_textToggle.setFont(m_font);
    m_textToggle.setCharacterSize(15);
    m_textToggle.setFillColor(BLACK);
    m_textToggle.setString("Click on cell to toggle live/dead.");

    m_textSpeed.setFont(m_font);
    m_textSpeed.setCharacterSize(15);
    m_textSpeed.setFillColor(BLACK);
    m_textSpeed.setString("Use left/right arrow keys to change speed.");
}

void View::draw(sf::RenderWindow& window)
{
    
    window.clear(WHITE);

    for (int x = 0; x < m_model.getWidth(); x++) {
        for (int y = 0; y < m_model.getHeight(); y++) {
            sf::RectangleShape cell(sf::Vector2f((float)m_cellSize, (float)m_cellSize));
            cell.setPosition((float)(x * m_cellSize), (float)(y * m_cellSize));
            cell.setOutlineThickness(1);
            cell.setOutlineColor(GRAY);

            if (m_model.isAlive(x, y)) {
                cell.setFillColor(BLACK);
            } else {
                cell.setFillColor(WHITE);
            }
            window.draw(cell);
        }
    }
}

void View::drawUI(sf::RenderWindow& window, bool isPlaying, int delay)
{

    float yPos = (float)(m_model.getHeight() * m_cellSize) + 5;

    if (isPlaying) {
        m_textPause.setPosition(10.f, yPos);
        window.draw(m_textPause);
    } else {
        m_textPlay.setPosition(10.f, yPos);
        window.draw(m_textPlay);

        m_textToggle.setPosition(10.f, yPos + 20.f);
        window.draw(m_textToggle);
    }

    m_textSpeed.setPosition(300.f, yPos);
    window.draw(m_textSpeed);

    sf::Text delayText;
    delayText.setFont(m_font);
    delayText.setCharacterSize(15);
    delayText.setFillColor(BLACK);
    delayText.setString("speed: " + std::to_string(delay) + " ms");
    delayText.setPosition(300.f, yPos + 20.f);
    window.draw(delayText);
}

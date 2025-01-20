#include "Controller.hpp"
#include <algorithm>

Controller::Controller(Model& model, View& view)
    : m_model(model)
    , m_view(view)
    , m_isPlaying(true)
    , m_delay(100)
{
}

void Controller::run()
{
    int windowWidth  = m_model.getWidth()  * 30;
    int windowHeight = m_model.getHeight() * 30 + 70;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Game of Life");

    while (window.isOpen()) {
        processEvents(window);

        if (m_isPlaying) {
            m_model.update();
        }

        m_view.draw(window);
        m_view.drawUI(window, m_isPlaying, m_delay);
        window.display();

        sf::sleep(sf::milliseconds(m_delay));
    }
}

void Controller::processEvents(sf::RenderWindow& window)
{
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type)
        {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::KeyPressed:
                handleKeyPress(event.key);
                break;

            case sf::Event::MouseButtonPressed:
                handleMousePress(event.mouseButton);
                break;

            default:
                break;
        }
    }
}

void Controller::handleKeyPress(const sf::Event::KeyEvent& keyEvent)
{
    switch (keyEvent.code)
    {
        case sf::Keyboard::P:
            m_isPlaying = !m_isPlaying;
            break;

        case sf::Keyboard::Right:
            m_delay = std::max(m_delay - 50, 0);
            break;

        case sf::Keyboard::Left:
            m_delay += 50;
            break;

        default:
            break;
    }
}

void Controller::handleMousePress(const sf::Event::MouseButtonEvent& mouseEvent)
{
    if (!m_isPlaying && mouseEvent.button == sf::Mouse::Left) {
        int x = mouseEvent.x / 30;
        int y = mouseEvent.y / 30;
        m_model.toggleCell(x, y);
    }
}

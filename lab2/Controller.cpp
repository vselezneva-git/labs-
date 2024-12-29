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
        if (event.type == sf::Event::Closed) {
            window.close();
        } 
        else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::P) {
                m_isPlaying = !m_isPlaying;
            }
            else if (event.key.code == sf::Keyboard::Right) {
                m_delay = std::max(m_delay - 50, 0);
            }
            else if (event.key.code == sf::Keyboard::Left) {
                m_delay += 50;
            }
        }
        else if (event.type == sf::Event::MouseButtonPressed) {
            if (!m_isPlaying && event.mouseButton.button == sf::Mouse::Left) {
                int x = event.mouseButton.x / 30;
                int y = event.mouseButton.y / 30;
                m_model.toggleCell(x, y);
            }
        }
    }
}

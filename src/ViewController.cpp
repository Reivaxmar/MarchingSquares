#include "ViewController.h"

ViewController::ViewController(sf::View& _view) : m_view(_view), lastPos(sf::Mouse::getPosition()) {

}

void ViewController::Update(sf::RenderWindow& window, std::vector<sf::Event> events) {
    // Initialize a tracker for the mouse wheel
    int wheelFactor = 0;
    // And iterate through the events to check if there's a mouse wheel movement
    for(sf::Event ev : events)
        if(ev.type == sf::Event::MouseWheelScrolled)
            if(ev.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
                wheelFactor = -ev.mouseWheelScroll.delta;

    // If it has moved
    if(wheelFactor != 0) {
        if(wheelFactor > 0) {   // Zoom smaller
            zoomViewAt(m_view, sf::Mouse::getPosition(window), window, zoomFactor);
        } else {                // Zoom bigger
            zoomViewAt(m_view, sf::Mouse::getPosition(window), window, 1.0 / zoomFactor);
        }
    }
    
    // Need fixing
    // if(Keyboard::isKeyPressed(Keyboard::Up)) {
    //     m_view.view.move(0, -0.1);
    // }
    // if(Keyboard::isKeyPressed(Keyboard::Down)) {
    //     m_view.view.move(0, 0.1);
    // }

    // if(Keyboard::isKeyPressed(Keyboard::Left)) {
    //     m_view.view.move(-0.1, 0);
    // }
    // if(Keyboard::isKeyPressed(Keyboard::Right)) {
    //     m_view.view.move(0.1, 0);
    // }

    // Draw around the scene when the mouse is pressed
    sf::Vector2i curPos = sf::Mouse::getPosition(window);
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        // Check if the mouse is on the window
        if(curPos.x >= 0 && curPos.x < static_cast<int>(window.getSize().x) &&
           curPos.y >= 0 && curPos.y < static_cast<int>(window.getSize().y) && lastPos != sf::Vector2i(-1, -1))
            m_view.move(sf::Vector2f(lastPos-curPos)*getZoom(m_view, window));
    }

    // Update the last mouse position
    if(curPos.x >= 0 && curPos.x < static_cast<int>(window.getSize().x) &&
       curPos.y >= 0 && curPos.y < static_cast<int>(window.getSize().y))
        lastPos = curPos;
    else lastPos = sf::Vector2i(-1, -1);
}
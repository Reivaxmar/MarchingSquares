#include "ViewController.h"

ViewController::ViewController(View& _view) : m_view(_view), lastPos(Mouse::getPosition()) {

}

void ViewController::Update(RenderWindow& window, vector<Event> events) {
    // Initialize a tracker for the mouse wheel
    int wheelFactor = 0;
    // And iterate through the events to check if there's a mouse wheel movement
    for(Event ev : events)
        if(ev.type == Event::MouseWheelScrolled)
            if(ev.mouseWheelScroll.wheel == Mouse::VerticalWheel)
                wheelFactor = -ev.mouseWheelScroll.delta;

    // If it has moved
    if(wheelFactor != 0) {
        if(wheelFactor > 0) {   // Zoom smaller
            zoomViewAt(m_view, Mouse::getPosition(window), window, 1.25);
        } else {                // Zoom bigger
            zoomViewAt(m_view, Mouse::getPosition(window), window, 0.8);
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
    if(Mouse::isButtonPressed(Mouse::Left)) {
        Vector2i curPos = Mouse::getPosition(window);
        // Check if the mouse is on the window
        if(curPos.x >= 0 && curPos.x < static_cast<int>(window.getSize().x) &&
           curPos.y >= 0 && curPos.y < static_cast<int>(window.getSize().y))
            m_view.move(Vector2f(lastPos-curPos)*getZoom(m_view, window));
    }

    // Update the last mouse position
    lastPos = Mouse::getPosition(window);
}
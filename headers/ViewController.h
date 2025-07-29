#ifndef VIEWCONTROLLER_CLASS_H
#define VIEWCONTROLLER_CLASS_H

#include "Utils.h"

#include <vector>
#include <iostream>

#include <SFML/Graphics.hpp>

// View Controller class
class ViewController {
public:
    ViewController(sf::View& _view);
    void Update(sf::RenderWindow& window, std::vector<sf::Event> events);
private:
    sf::View& m_view;

    sf::Vector2i lastPos;

    const double zoomFactor = 1.1;
};

#endif // VIEWCONTROLLER_CLASS_H
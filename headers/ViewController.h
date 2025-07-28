#ifndef VIEWCONTROLLER_CLASS_H
#define VIEWCONTROLLER_CLASS_H

#include "Utils.h"

#include <vector>
#include <iostream>
using namespace std;

#include <SFML/Graphics.hpp>
using namespace sf;

// View Controller class
class ViewController {
public:
    ViewController(View& _view);
    void Update(RenderWindow& window, vector<Event> events);
private:
    View& m_view;

    Vector2i lastPos;
};

#endif // VIEWCONTROLLER_CLASS_H
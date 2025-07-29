#ifndef GRID_CLASS_H
#define GRID_CLASS_H

#include "Utils.h"
#include "SceneObject.h"
#include <iostream>
#include <vector>
#include <cmath>

#ifndef ASSETS_PATH
#error "ASSETS_PATH not defined"
#endif

class Grid : public SceneObject {
public:
    Grid(sf::View& _v) : m_curView(_v) {
        m_font.loadFromFile(std::string(ASSETS_PATH)+"/CascadiaCode.ttf");
        m_text.setFont(m_font);
        m_text.setString("asd");
        m_text.setFillColor(sf::Color::Black);
        m_text.setCharacterSize(30);
    }
private:

    float findBestStep(float width) const;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    

    void drawPosNum(sf::RenderTarget& target, sf::RenderStates states, sf::Vector2<double> pos) const;

    sf::View& m_curView;
    sf::Font m_font;
    mutable sf::Text m_text;
    const float m_txtSize = 15/30.f;
    const sf::Color MainAxisColor = sf::Color(0, 0, 0);
    const sf::Color GridLineColor = sf::Color(140, 140, 140);
    const sf::Color SubGridLineColor = sf::Color(190, 190, 190);

};

#endif // GRID_CLASS_H
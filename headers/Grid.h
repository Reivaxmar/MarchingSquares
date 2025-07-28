#ifndef GRID_CLASS_H
#define GRID_CLASS_H

#include "Utils.h"
#include "SceneObject.h"
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#ifndef ASSETS_PATH
#error "ASSETS_PATH not defined"
#endif

class Grid : public SceneObject {
public:
    Grid(View& _v) : m_curView(_v) {
        m_font.loadFromFile(string(ASSETS_PATH)+"/CascadiaCode.ttf");
        m_text.setFont(m_font);
        m_text.setString("asd");
        m_text.setFillColor(Color::Black);
        m_text.setCharacterSize(30);
    }
private:

    float findBestStep(float width) const;

    virtual void draw(RenderTarget& target, RenderStates states) const;
    

    void drawPosNum(RenderTarget& target, RenderStates states, Vector2<double> pos) const;

    View& m_curView;
    Font m_font;
    mutable Text m_text;
    const float m_txtSize = 15/30.f;
    const Color MainAxisColor = Color(0, 0, 0);
    const Color GridLineColor = Color(140, 140, 140);
    const Color SubGridLineColor = Color(190, 190, 190);

};

#endif // GRID_CLASS_H
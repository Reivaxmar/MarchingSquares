#ifndef OBJECTUTILS_H
#define OBJECTUTILS_H

#include "SceneObject.h"
#include <iostream>
using namespace std;

// Point scene object for drawing
class Point : public SceneObject {
public:
    Point(Vector2f pos = Vector2f(0, 0), Color _color = Color::Black)
        : m_color(_color), shape(3.f)
    {
        setPosition(pos);
        setFillColor(_color);
        shape.setOutlineColor(Color::Black);
        shape.setOutlineThickness(1.f);
        shape.setOrigin(Vector2f(2.5f, 2.5f));
    }

    void setFillColor(const Color color) {
        m_color = color;
        shape.setFillColor(m_color);
    }

private:
    Color m_color;
    mutable CircleShape shape;
    virtual void draw(RenderTarget& target, RenderStates states) const {
        float scale = target.getView().getSize().x/target.getSize().x;
        shape.setScale(Vector2f(scale, scale));
        shape.setPosition(getPosition());
        target.draw(shape, states);
    }
};

// Line scene object for drawing (more like segment)
class Line : public SceneObject {
public:
    Line(Vector2f _begin = Vector2f(0, 0), Vector2f _end = Vector2f(0, 0), Color _color = Color::Black)
        : m_color(_color), m_begin(_begin), m_end(_end), line(PrimitiveType::Lines, 2)
    {
        setFillColor(_color);
        setBegin(_begin);
        setEnd(_end);
    }

    void setFillColor(const Color _color) {
        m_color = _color;
        line[0].color = _color;
        line[1].color = _color;
    }

    void setBegin(Vector2f _begin) {
        m_begin = _begin;
        line[0].position = m_begin;
    }
    void setEnd(Vector2f _end) {
        m_end = _end;
        line[1].position = m_end;
    }

    Vector2f getBegin() {
        return m_begin;
    }
    Vector2f getEnd() {
        return m_end;
    }

private:
    Color m_color;
    Vector2f m_begin, m_end;
    VertexArray line;

    virtual void draw(RenderTarget& target, RenderStates states) const {
        target.draw(line, states);
    }
};

#endif // OBJECTUTILS_H
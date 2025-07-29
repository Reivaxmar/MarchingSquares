#ifndef OBJECTUTILS_H
#define OBJECTUTILS_H

#include "SceneObject.h"
#include <iostream>

namespace ObjUtils
{
    
    // Point scene object for drawing
    class Point : public SceneObject {
    public:
        Point(sf::Vector2f pos = sf::Vector2f(0, 0), sf::Color _color = sf::Color::Black)
            : m_color(_color), shape(3.f)
        {
            setPosition(pos);
            setFillColor(_color);
            shape.setOutlineColor(sf::Color::Black);
            shape.setOutlineThickness(1.f);
            shape.setOrigin(sf::Vector2f(2.5f, 2.5f));
        }
    
        void setFillColor(const sf::Color color) {
            m_color = color;
            shape.setFillColor(m_color);
        }
    
    private:
        sf::Color m_color;
        mutable sf::CircleShape shape;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
            float scale = target.getView().getSize().x/target.getSize().x;
            shape.setScale(sf::Vector2f(scale, scale));
            shape.setPosition(getPosition());
            target.draw(shape, states);
        }
    };
    
    // Line scene object for drawing (more like segment)
    class Line : public SceneObject {
    public:
        Line(sf::Vector2f _begin = sf::Vector2f(0, 0), sf::Vector2f _end = sf::Vector2f(0, 0), sf::Color _color = sf::Color::Black)
            : m_color(_color), m_begin(_begin), m_end(_end), line(sf::PrimitiveType::Lines, 2)
        {
            setFillColor(_color);
            setBegin(_begin);
            setEnd(_end);
        }
    
        void setFillColor(const sf::Color _color) {
            m_color = _color;
            line[0].color = _color;
            line[1].color = _color;
        }
    
        void setBegin(sf::Vector2f _begin) {
            m_begin = _begin;
            line[0].position = m_begin;
        }
        void setEnd(sf::Vector2f _end) {
            m_end = _end;
            line[1].position = m_end;
        }
    
        sf::Vector2f getBegin() {
            return m_begin;
        }
        sf::Vector2f getEnd() {
            return m_end;
        }
    
    private:
        sf::Color m_color;
        sf::Vector2f m_begin, m_end;
        sf::VertexArray line;
    
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
            target.draw(line, states);
        }
    };
} // namespace ObjUtils



#endif // OBJECTUTILS_H
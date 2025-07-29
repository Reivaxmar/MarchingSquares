#ifndef SCENEOBJECT_CLASS_H
#define SCENEOBJECT_CLASS_H

#include <SFML/Graphics.hpp>

// Base class for Scene objects
class SceneObject : public sf::Drawable, public sf::Transformable {
public:
    SceneObject() = default;
    virtual void update(const sf::RenderWindow& window, const float& deltaTime) {}

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;

};

#endif // SCENEOBJECT_CLASS_H
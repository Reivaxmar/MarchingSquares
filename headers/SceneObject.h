#ifndef SCENEOBJECT_CLASS_H
#define SCENEOBJECT_CLASS_H

#include <SFML/Graphics.hpp>
using namespace sf;

// Base class for Scene objects
class SceneObject : public Drawable, public Transformable {
public:
    SceneObject() {}
private:
    virtual void draw(RenderTarget& target, RenderStates states) const {
        // Doesn't do anything
        return;
    }
};

#endif // SCENEOBJECT_CLASS_H
#ifndef SCENE_CLASS_H
#define SCENE_CLASS_H

#include "SceneObject.h"

#include <vector>
#include <memory>

// Scene class
class Scene {
public:
    Scene();
    void draw(sf::RenderWindow& window);
    void update(const sf::RenderWindow& window, float deltaTime);
    void addObject(std::shared_ptr<SceneObject> obj);
    std::vector<std::shared_ptr<SceneObject>>& getObjects();
private:
    std::vector<std::shared_ptr<SceneObject>> objs;
};

#endif // SCENE_CLASS_H
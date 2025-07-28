#ifndef SCENE_CLASS_H
#define SCENE_CLASS_H

#include "SceneObject.h"

#include <vector>
#include <memory>
using namespace std;

// Scene class
class Scene {
public:
    Scene();
    void draw(RenderWindow& window);
    void addObject(shared_ptr<SceneObject> obj);
    vector<shared_ptr<SceneObject>>& getObjects();
private:
    vector<shared_ptr<SceneObject>> objs;
};

#endif // SCENE_CLASS_H
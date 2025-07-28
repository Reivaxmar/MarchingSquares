#include "Scene.h"

Scene::Scene() {

}
// Draws every object to the window
void Scene::draw(RenderWindow& window) {
    for(auto& obj : objs) {
        window.draw(*obj);
    }
}
// Adds object obj to the objs vector
void Scene::addObject(shared_ptr<SceneObject> obj) {
    objs.push_back(move(obj));
}
// Returns the objs vector
vector<shared_ptr<SceneObject>>& Scene::getObjects() {
    return objs;
}
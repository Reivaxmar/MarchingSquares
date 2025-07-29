#include "Scene.h"

Scene::Scene() {

}
// Draws every object to the window
void Scene::draw(sf::RenderWindow& window) {
    for(auto& obj : objs) {
        window.draw(*obj);
    }
}
// Updates every object
void Scene::update(const sf::RenderWindow& window, float deltaTime) {
    for(auto& obj : objs) {
        obj->update(window, deltaTime);
    }
}
// Adds object obj to the objs vector
void Scene::addObject(std::shared_ptr<SceneObject> obj) {
    objs.push_back(std::move(obj));
}
// Returns the objs vector
std::vector<std::shared_ptr<SceneObject>>& Scene::getObjects() {
    return objs;
}
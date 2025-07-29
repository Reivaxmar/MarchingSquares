#ifndef FUNCTIONHANDLER_CLASS_H
#define FUNCTIONHANDLER_CLASS_H

#include "SceneObject.h"
#include <functional>

// Function Handler class
class FunctionHandler {
public:
    FunctionHandler();
    FunctionHandler(std::function<double(double, double)> _func, double _equalTo = 1.0);
    void setFunction(std::function<double(double, double)> _func);
    void setEqual(double _equalTo);
    std::function<double(double, double)>& getFunction();
    double getEqual();
    double evalAt(sf::Vector2f pos);
    double evalAt(double x, double y);
private:
    std::function<double(double, double)> m_func;
    double m_equalTo = 1.0;

};

#endif // FUNCTIONHANDLER_CLASS_H
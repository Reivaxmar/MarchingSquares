#include "FunctionHandler.h"

// Default constructor has a circle of radius 6
FunctionHandler::FunctionHandler()
    : m_func([](double x, double y) -> double {
        return x*x+y*y;
    })
    , m_equalTo(36.0) // 6^2
{

}

// Constructor that gets a function and an optional equal
FunctionHandler::FunctionHandler(std::function<double(double, double)> _func, double _equalTo)
    : m_func(_func)
    , m_equalTo(_equalTo)
{

}

// Set the function
void FunctionHandler::setFunction(std::function<double(double, double)> _func) {
    m_func = _func;
}

// Set the equal
void FunctionHandler::setEqual(double _equalTo) {
    m_equalTo = _equalTo;
}

// Get the function
std::function<double(double, double)>& FunctionHandler::getFunction() {
    return m_func;
}

// Get the equal
double FunctionHandler::getEqual() {
    return m_equalTo;
}
// Return the evaluation at position pos
double FunctionHandler::evalAt(sf::Vector2f pos) {
    return m_func(pos.x, pos.y);
}
// Return the evaluation at position (x, y)
double FunctionHandler::evalAt(double x, double y) {
    return m_func(x, y);
}

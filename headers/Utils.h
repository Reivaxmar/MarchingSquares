#ifndef UTILS_H
#define UTILS_H

#include <SFML/Graphics.hpp>
using namespace sf;

#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

template <typename U>
// A comparator for hashing ordered Vector2
struct Vector2Comparator {
    bool operator()(const sf::Vector2<U>& lhs, const sf::Vector2<U>& rhs) const {
        // First compare the x components
        if (lhs.x < rhs.x) return true;
        if (lhs.x > rhs.x) return false;
        
        // If x components are equal, compare the y components
        return lhs.y < rhs.y;
    }
};

float lerp(float a, float b, float t);
Vector2f lerp(const Vector2f& a, const Vector2f& b, float t);

float getZoom(View view, RenderTarget& target);

void updateWindowSize(RenderTarget& target, View& view, Vector2f newSize);

std::string floatToString(double value);

void zoomViewAt(View& view, sf::Vector2i pixel, sf::RenderWindow& window, float zoom);

#endif // UTILS_H
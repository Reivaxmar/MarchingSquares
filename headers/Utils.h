#ifndef UTILS_H
#define UTILS_H

#include <SFML/Graphics.hpp>

#include <iostream>
#include <sstream>
#include <iomanip>

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
sf::Vector2f lerp(const sf::Vector2f& a, const sf::Vector2f& b, float t);

float getZoom(const sf::View& view, sf::RenderTarget& target);

void updateWindowSize(sf::RenderTarget& target, sf::View& view, sf::Vector2f newSize);

std::string floatToString(double value);

void zoomViewAt(sf::View& view, sf::Vector2i pixel, sf::RenderWindow& window, float zoom);

template<typename T>
inline T distanceSquared(const sf::Vector2<T>& a, const sf::Vector2<T>& b);

#endif // UTILS_H
#include "Utils.h"

// Util function for lerping between a and b by t
float lerp(float a, float b, float t) {
    return a + (b - a) * t;
}

// Util function for lerping between pos a and b by t
sf::Vector2f lerp(const sf::Vector2f& a, const sf::Vector2f& b, float t) {
    return sf::Vector2f(lerp(a.x, b.x, t), lerp(a.y, b.y, t));
}

// Utils function that returns the zoom of a view
float getZoom(const sf::View& view, sf::RenderTarget& target) {
    return view.getSize().x/target.getSize().x;
}

// Util function that updates the view by the window size
void updateWindowSize(sf::RenderTarget& target, sf::View& view, sf::Vector2f newSize) {
    float z = getZoom(view, target);
    view.setSize(newSize);
    view.zoom(z);
}

// Util function that converts a double to string
std::string floatToString(double value) {
    std::ostringstream out;
    out << std::setprecision(6) << value; // Set precision high enough to retain accuracy
    std::string result = out.str();

    // Remove trailing zeros and possibly the decimal point if it's no longer needed
    if (result.find('.') != std::string::npos) {
        result.erase(result.find_last_not_of('0') + 1);
        if (result.back() == '.') {
            result.pop_back(); // Remove the trailing dot if present
        }
    }

    return result;
}

// Util function that zooms at a position
void zoomViewAt(sf::View& view, sf::Vector2i pixel, sf::RenderWindow& window, float zoom)
{
	const sf::Vector2f beforeCoord{ window.mapPixelToCoords(pixel) };
	view.zoom(zoom);
	window.setView(view);
	const sf::Vector2f afterCoord{ window.mapPixelToCoords(pixel) };
	const sf::Vector2f offsetCoords{ beforeCoord - afterCoord };
	view.move(offsetCoords);
}

// Util function to get the distance squared between two points
template<typename T>
inline T distanceSquared(const sf::Vector2<T>& a, const sf::Vector2<T>& b) {
    T dx = a.x - b.x;
    T dy = a.y - b.y;
    return dx*dx + dy*dy;
}
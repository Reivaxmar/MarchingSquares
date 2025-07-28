#include "Utils.h"

// Util function for lerping between a and b by t
float lerp(float a, float b, float t) {
    return a + (b - a) * t;
}
// Util function for lerping between pos a and b by t
Vector2f lerp(const Vector2f& a, const Vector2f& b, float t) {
    return Vector2f(lerp(a.x, b.x, t), lerp(a.y, b.y, t));
}
// Utils function that returns the zoom of a view
float getZoom(View view, RenderTarget& target) {
    return view.getSize().x/target.getSize().x;
}
// Util function that updates the view by the window size
void updateWindowSize(RenderTarget& target, View& view, Vector2f newSize) {
    float z = getZoom(view, target);
    view.setSize(newSize);
    view.zoom(z);
}
// Util function that converts a double to string
std::string floatToString(double value) {
    ostringstream out;
    out << std::setprecision(6) << value; // Set precision high enough to retain accuracy
    string result = out.str();

    // Remove trailing zeros and possibly the decimal point if it's no longer needed
    if (result.find('.') != string::npos) {
        result.erase(result.find_last_not_of('0') + 1);
        if (result.back() == '.') {
            result.pop_back(); // Remove the trailing dot if present
        }
    }

    return result;
}
// Util function that zooms at a position
void zoomViewAt(View& view, sf::Vector2i pixel, sf::RenderWindow& window, float zoom)
{
	const sf::Vector2f beforeCoord{ window.mapPixelToCoords(pixel) };
	view.zoom(zoom);
	window.setView(view);
	const sf::Vector2f afterCoord{ window.mapPixelToCoords(pixel) };
	const sf::Vector2f offsetCoords{ beforeCoord - afterCoord };
	view.move(offsetCoords);
}
#include "MarchingSquares.h"
#include <future>
#include <mutex>
// Main constructor
MarchingSquares::MarchingSquares(FunctionHandler _funcHandler, float _stepSize) 
    : m_funcHandler(_funcHandler), m_stepSize(_stepSize)
{

}
// Set function for step size
void MarchingSquares::setStepSize(float _stepSize) {
    m_stepSize = _stepSize;
}
// Set function for the MS function
void MarchingSquares::setFunction(FunctionHandler _funcHandler) {
    m_funcHandler = _funcHandler;
}
// Function that calculates the MS point with interpolation
sf::Vector2f MarchingSquares::calculatePoint(int edgeNum, float vals[4]) const {
    sf::Vector2f ret = sf::Vector2f(0, 0);
    float a, b, t;
    int c = 0;
    switch (edgeNum)
    {
    case 1:         // Case 1: edge 1-2
        a = vals[0],
        b = vals[1];
        t = -a / (b - a);
        ret = lerp(sf::Vector2f(0, 0), sf::Vector2f(1, 0), t);
        c = 1;
        break;

    case 2:         // Case 2: edge 2-3
        a = vals[1],
        b = vals[2];
        t = -a / (b - a);
        ret = lerp(sf::Vector2f(1, 0), sf::Vector2f(1, 1), t);
        c = 2;
        break;

    case 3:         // Case 3: edge 3-4
        a = vals[2],
        b = vals[3];
        t = -a / (b - a);
        ret = lerp(sf::Vector2f(1, 1), sf::Vector2f(0, 1), t);
        c = 3;
        break;

    case 4:         // Case 4: edge 4-1
        a = vals[3],
        b = vals[0];
        t = -a / (b - a);
        ret = lerp(sf::Vector2f(0, 1), sf::Vector2f(0, 0), t);
        c = 4;
        break;
    
    default:        // Should never happen
        // throw std::invalid_argument("default case in MarchingSquares::caculatePoint is invalid");
        break;
    }

    return ret;
}

// Helper function for multithreaded marching squares row processing
void MarchingSquares::processRow(float x, float up, float down, std::vector<SquareData>& squareData) const {
    for(float y = up - m_stepSize; y <= down + m_stepSize; y += m_stepSize) {
        // Get the values at each vertex
        float vals[4] = { float(m_funcHandler.evalAt(sf::Vector2f(x, y)) - m_funcHandler.getEqual()),
                          float(m_funcHandler.evalAt(sf::Vector2f(x + m_stepSize, y)) - m_funcHandler.getEqual()),
                          float(m_funcHandler.evalAt(sf::Vector2f(x + m_stepSize, y + m_stepSize)) - m_funcHandler.getEqual()),
                          float(m_funcHandler.evalAt(sf::Vector2f(x, y + m_stepSize)) - m_funcHandler.getEqual()) };
        // Get the 4-bit mask for the hardcoded cases
        unsigned int mask = 0b0000;
        mask = ((vals[0] <= 0) << 0)
             + ((vals[1] <= 0) << 1)
             + ((vals[2] <= 0) << 2)
             + ((vals[3] <= 0) << 3);
        sf::Vector2i joins = MScases[mask];

        // Cases where there are two lines
        if(joins == sf::Vector2i(-1, -1)) {
            // (-1, -1) is when there's an edge covering top-right and bottom-left

            // So first top-right
            sf::Vector2f p1 = calculatePoint(1, vals);
            sf::Vector2f p2 = calculatePoint(2, vals);
            // squareData.push_back({sf::Vector2f(x, y) + p1 * m_stepSize, sf::Vector2f(x, y) + p2 * m_stepSize});

            // And then bottom-left
            sf::Vector2f p3 = calculatePoint(3, vals);
            sf::Vector2f p4 = calculatePoint(4, vals);
            // squareData.push_back({sf::Vector2f(x, y) + p3 * m_stepSize, sf::Vector2f(x, y) + p4 * m_stepSize});

        } else if(joins == sf::Vector2i(-2, -2)) {
            // (-2, -2) is when there's an edge covering top-left and bottom-right

            // So first top-left
            sf::Vector2f p1 = calculatePoint(4, vals);
            sf::Vector2f p2 = calculatePoint(1, vals);
            // squareData.push_back({sf::Vector2f(x, y) + p1 * m_stepSize, sf::Vector2f(x, y) + p2 * m_stepSize});

            // And then bottom-right
            sf::Vector2f p3 = calculatePoint(2, vals);
            sf::Vector2f p4 = calculatePoint(3, vals);
            // squareData.push_back({sf::Vector2f(x, y) + p3 * m_stepSize, sf::Vector2f(x, y) + p4 * m_stepSize});

        } else if(joins != sf::Vector2i(0-1, 0)) { // Only one line
            // Calculate the midpoints given the edge join position
            sf::Vector2f midpoints[2] = {
                calculatePoint(joins.x, vals),
                calculatePoint(joins.y, vals)
            };
            // Resulting shape
            SquareData shape_points;
            // std::vector<sf::Vector2f> shape_points;
            // For tracking the join idx
            int point_idx = 0;
            for(int i = 0; i < 4; i++) {
                // If the vertex is outside
                if(vals[i] > 0) {
                    // And the next is inside
                    if(vals[(i+1) % 4] <= 0) {
                        // std::cout << "idx: " << point_idx << std::endl;
                        // Add a point to the shape
                        shape_points.verts.push_back(m_stepSize*midpoints[point_idx]  + sf::Vector2f(x, y));
                        // shape.setPoint(shape_idx, midpoints[point_idx]);
                        point_idx++;
                    }
                } else {
                    // Add the square vertex
                    shape_points.verts.push_back(m_stepSize*SquaresVerts[i] + sf::Vector2f(x, y));
                    // std::cout << (SquaresVerts[i] + sf::Vector2f(x, y)).x << ", " << (SquaresVerts[i] + sf::Vector2f(x, y)).y << std::endl;
                }
            }
            squareData.push_back(shape_points);
            // std::cout << std::endl;
            // lines.push_back({sf::Vector2f(x, y) + p1 * m_stepSize, sf::Vector2f(x, y) + p2 * m_stepSize});
        }
    }
}

void MarchingSquares::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Adjust for camera scale
    sf::Vector2f screenMid(target.getView().getCenter());
    float scale = target.getView().getSize().x / target.getSize().x;
    sf::Vector2f screenSize(target.getSize().x*scale, target.getSize().y*scale);

    // Get the screen positions
    float left  = screenMid.x - (screenSize.x / 2),
          right = screenMid.x + (screenSize.x / 2);
    float up    = screenMid.y - (screenSize.y / 2),
          down  = screenMid.y + (screenSize.y / 2);

    // And scale them with the step size
    left = int(left / m_stepSize) * m_stepSize;
    right = int(right / m_stepSize) * m_stepSize;
    up = int(up / m_stepSize) * m_stepSize;
    down = int(down / m_stepSize) * m_stepSize;

    std::vector<SquareData> squares;
    std::mutex lines_mutex;

    // Launch threads for each column
    // std::vector<std::future<void>> futures;
    for(float x = left - m_stepSize; x <= right + m_stepSize; x += m_stepSize) {
        // futures.push_back(std::async(std::launch::async, [this, x, up, down, &squares, &lines_mutex]() {
            std::vector<SquareData> local_lines;
            processRow(x, up, down, local_lines);
            std::lock_guard<std::mutex> lock(lines_mutex);
            squares.insert(squares.end(), local_lines.begin(), local_lines.end());
        // }));
    }
    // for(auto& f : futures) f.get();

    // Draw all collected lines in the main thread
    sf::ConvexShape sqShape;
    sqShape.setFillColor(sf::Color::Black);
    for(const auto& sq : squares) {
        sqShape.setFillColor(sf::Color(sqShape.getFillColor().r+1, 0, 0));
        sqShape.setPointCount(sq.verts.size());
        for(int i = 0; i < sq.verts.size(); i++) {
            sqShape.setPoint(i, sq.verts[i]);
        }
        target.draw(sqShape, states);
        // ObjUtils::Line line;
        // line.setBegin(sq.begin);
        // line.setEnd(sq.end);
        // target.draw(line);
    }
}

void MarchingSquares::update(const sf::RenderWindow& window, const float& deltaTime) {
    // Move up or down the layer of perlin noise
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)) m_funcHandler.setEqual(m_funcHandler.getEqual() - 0.25*deltaTime);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) m_funcHandler.setEqual(m_funcHandler.getEqual() + 0.25*deltaTime);
        
}
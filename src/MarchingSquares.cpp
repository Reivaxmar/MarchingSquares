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
    checks.clear();
}
// Function that calculates the MS point with interpolation
Vector2f MarchingSquares::calculatePoint(int edgeNum, float vals[4]) const {
    Vector2f ret = Vector2f(0, 0);
    float a, b, t;
    int c = 0;
    switch (edgeNum)
    {
    case 1:         // Case 1: edge 1-2
        a = vals[0],
        b = vals[1];
        t = -a / (b - a);
        ret = lerp(Vector2f(0, 0), Vector2f(1, 0), t);
        c = 1;
        break;

    case 2:         // Case 2: edge 2-4
        a = vals[1],
        b = vals[3];
        t = -a / (b - a);
        ret = lerp(Vector2f(1, 0), Vector2f(1, 1), t);
        c = 2;
        break;

    case 3:         // Case 3: edge 4-3
        a = vals[3],
        b = vals[2];
        t = -a / (b - a);
        ret = lerp(Vector2f(1, 1), Vector2f(0, 1), t);
        c = 3;
        break;

    case 4:         // Case 4: edge 3-1
        a = vals[2],
        b = vals[0];
        t = -a / (b - a);
        ret = lerp(Vector2f(0, 1), Vector2f(0, 0), t);
        c = 4;
        break;
    
    default:        // Should never happen
        throw invalid_argument("default case in MarchingSquares::caculatePoint is invalid");
        break;
    }

    return ret;
}

// 1------2
// |      |
// |      |
// 3------4
void MarchingSquares::handlePosition(Vector2f pos, RenderTarget& target, RenderStates states) const {
    // Get the vals for the calculatePoint function
    float vals[4] = { float(m_funcHandler.evalAt(pos) - m_funcHandler.getEqual()),
                      float(m_funcHandler.evalAt(pos + Vector2f(m_stepSize, 0)) - m_funcHandler.getEqual()),
                      float(m_funcHandler.evalAt(pos + Vector2f(0, m_stepSize)) - m_funcHandler.getEqual()),
                      float(m_funcHandler.evalAt(pos + Vector2f(m_stepSize, m_stepSize)) - m_funcHandler.getEqual()) };
    
    // Get the mask for the cases
    unsigned int mask = 0b0000;
    mask = ((vals[0] <= 0) << 0)
         + ((vals[1] <= 0) << 1)
         + ((vals[2] <= 0) << 2)
         + ((vals[3] <= 0) << 3);
         
    Vector2i joins = MScases[mask];
    
    Line l;
    if(joins == Vector2i(-1, -1)) {
        // Middle case 1
        // Join edges 1-2
        l.setFillColor(Color::Red);
        Vector2f p1 = calculatePoint(1, vals);
        Vector2f p2 = calculatePoint(2, vals);
        l.setBegin(pos + p1 * m_stepSize);
        l.setEnd(pos + p2 * m_stepSize);
        target.draw(l);
        // And edges 3-4
        p1 = calculatePoint(3, vals);
        p2 = calculatePoint(4, vals);
        l.setBegin(pos + p1 * m_stepSize);
        l.setEnd(pos + p2 * m_stepSize);
        target.draw(l);
        l.setFillColor(Color::Black);
    } else if(joins == Vector2i(-2, -2)) {
        // Middle case 2
        // Join edges 2-3
        l.setFillColor(Color::Blue);
        Vector2f p1 = calculatePoint(2, vals);
        Vector2f p2 = calculatePoint(3, vals);
        l.setBegin(pos + p1 * m_stepSize);
        l.setEnd(pos + p2 * m_stepSize);
        target.draw(l);
        // And edges 4-1
        p1 = calculatePoint(4, vals);
        p2 = calculatePoint(1, vals);
        l.setBegin(pos + p1 * m_stepSize);
        l.setEnd(pos + p2 * m_stepSize);
        target.draw(l);
        l.setFillColor(Color::Black);
    } else if(joins != Vector2i(0, 0)) {
        // Non-empty cases
        Vector2f p1 = calculatePoint(joins.x, vals);
        Vector2f p2 = calculatePoint(joins.y, vals);
        l.setBegin(pos + p1 * m_stepSize);
        l.setEnd(pos + p2 * m_stepSize);
        target.draw(l);
    }
    
}

// Helper function for multithreaded marching squares row processing
void MarchingSquares::processRow(float x, float up, float down, std::vector<LineData>& lines) const {
    for(float y = up - m_stepSize; y <= down + m_stepSize; y += m_stepSize) {
        // Get the values at each vertex
        float vals[4] = { float(m_funcHandler.evalAt(Vector2f(x, y)) - m_funcHandler.getEqual()),
                          float(m_funcHandler.evalAt(Vector2f(x + m_stepSize, y)) - m_funcHandler.getEqual()),
                          float(m_funcHandler.evalAt(Vector2f(x, y + m_stepSize)) - m_funcHandler.getEqual()),
                          float(m_funcHandler.evalAt(Vector2f(x + m_stepSize, y + m_stepSize)) - m_funcHandler.getEqual()) };
        // Get the 4-bit mask for the hardcoded cases
        unsigned int mask = 0b0000;
        mask = ((vals[0] <= 0) << 0)
             + ((vals[1] <= 0) << 1)
             + ((vals[2] <= 0) << 2)
             + ((vals[3] <= 0) << 3);
        Vector2i joins = MScases[mask];

        // Cases where there are two lines
        if(joins == Vector2i(-1, -1)) {
            // (-1, -1) is when there's an edge covering top-right and bottom-left

            // So first top-right
            Vector2f p1 = calculatePoint(1, vals);
            Vector2f p2 = calculatePoint(2, vals);
            lines.push_back({Vector2f(x, y) + p1 * m_stepSize, Vector2f(x, y) + p2 * m_stepSize});

            // And then bottom-left
            Vector2f p3 = calculatePoint(3, vals);
            Vector2f p4 = calculatePoint(4, vals);
            lines.push_back({Vector2f(x, y) + p3 * m_stepSize, Vector2f(x, y) + p4 * m_stepSize});

        } else if(joins == Vector2i(-2, -2)) {
            // (-2, -2) is when there's an edge covering top-left and bottom-right

            // So first top-left
            Vector2f p1 = calculatePoint(4, vals);
            Vector2f p2 = calculatePoint(1, vals);
            lines.push_back({Vector2f(x, y) + p1 * m_stepSize, Vector2f(x, y) + p2 * m_stepSize});

            // And then bottom-right
            Vector2f p3 = calculatePoint(2, vals);
            Vector2f p4 = calculatePoint(3, vals);
            lines.push_back({Vector2f(x, y) + p3 * m_stepSize, Vector2f(x, y) + p4 * m_stepSize});

        } else if(joins != Vector2i(0, 0)) { // Only one line
            // Calculate the point given the edge join position
            Vector2f p1 = calculatePoint(joins.x, vals);
            Vector2f p2 = calculatePoint(joins.y, vals);
            lines.push_back({Vector2f(x, y) + p1 * m_stepSize, Vector2f(x, y) + p2 * m_stepSize});
        }
    }
}

void MarchingSquares::draw(RenderTarget& target, RenderStates states) const {
    // Adjust for camera scale
    Vector2f screenMid(target.getView().getCenter());
    float scale = target.getView().getSize().x / target.getSize().x;
    Vector2f screenSize(target.getSize().x*scale, target.getSize().y*scale);

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

    std::vector<LineData> lines;
    std::mutex lines_mutex;

    // Launch threads for each column
    std::vector<std::future<void>> futures;
    for(float x = left - m_stepSize; x <= right + m_stepSize; x += m_stepSize) {
        futures.push_back(std::async(std::launch::async, [this, x, up, down, &lines, &lines_mutex]() {
            std::vector<LineData> local_lines;
            processRow(x, up, down, local_lines);
            std::lock_guard<std::mutex> lock(lines_mutex);
            lines.insert(lines.end(), local_lines.begin(), local_lines.end());
        }));
    }
    for(auto& f : futures) f.get();

    // Draw all collected lines in the main thread
    for(const auto& l : lines) {
        Line line;
        line.setBegin(l.begin);
        line.setEnd(l.end);
        target.draw(line);
    }
}
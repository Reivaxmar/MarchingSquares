#include "Grid.h"

float Grid::findBestStep(float width) const {
    double targetStep = width / 14.0;

    int exponent = floor(log10(targetStep));
    double multiples[] = {1.0, 2.0, 2.5, 5.0, 10.0};

    double bestStep = multiples[0] * pow(10, exponent);
    double minDiff = fabs(bestStep - targetStep);

    for (double m : multiples) {
        for (int e = exponent; e <= exponent + 1; ++e) {
            double candidate = m * pow(10, e);
            double diff = fabs(candidate - targetStep);
            if (diff < minDiff) {
                minDiff = diff;
                bestStep = candidate;
            }
        }
    }

    return bestStep;
}


void Grid::draw(RenderTarget& target, RenderStates states) const {
    
    target.draw(m_text);
    
    // Get the viewport center
    Vector2f screenMid(m_curView.getCenter());
    float scale = m_curView.getSize().x/target.getSize().x;
    Vector2f screenSize(target.getSize().x*scale, target.getSize().y*scale);
    
    
    // Calculate the begginning and the end of the horizontal and vertical lines
    float left  = screenMid.x - (screenSize.x / 2),
          right = screenMid.x + (screenSize.x / 2) + 1;
    
    float up    = screenMid.y - (screenSize.y / 2),
          down  = screenMid.y + (screenSize.y / 2) + 1;
          
    // float step = (right - left) / 14.f; // There should be 14 tiles
    
    // Find best step size
    float step = findBestStep(right - left);
    
    // Round the delimiters to the step size
    left = int(left / step) * step;
    right = int(right / step) * step;
    
    up = int(up / step) * step;
    down = int(down / step) * step;
    
    
    // Vertical lines
    vector<Vertex> line = 
    {
        Vertex(Vector2f(0, screenMid.y - (screenSize.y / 2)), GridLineColor),
        Vertex(Vector2f(0, screenMid.y + (screenSize.y / 2)), GridLineColor),
    };
    
    // Draw the (0, 0)
    drawPosNum(target, states, Vector2<double>(0, 0));
    
    
    // Iterate over all vertical lines and draw them
    for(float i = left-step; i <= right+step; i += step) {
        // Change the color to be less dark
        line[0].color = SubGridLineColor;
        line[1].color = SubGridLineColor;
        // Add 4 lines that divide the step
        for(int j = 1; j < 5; j++) {
            line[0].position.x = i + (step/5.f) * j;
            line[1].position.x = i + (step/5.f) * j;
            target.draw(&line[0], 2, Lines, states);
        }
        // Return the original color
        line[0].color = GridLineColor;
        line[1].color = GridLineColor;
        
        if(abs(i) <= max(0.00001f, step/100.f)) continue;
        
        line[0].position.x = i;
        line[1].position.x = i;
        target.draw(&line[0], 2, Lines, states);
        drawPosNum(target, states, Vector2<double>(i, 0));
    }
    
    
    // Horizontal lines lines
    line = {
        Vertex(Vector2f(screenMid.x - (screenSize.x / 2), 0), GridLineColor),
        Vertex(Vector2f(screenMid.x + (screenSize.x / 2), 0), GridLineColor),
    };
    
    
    // Iterate over all horizontal lines and draw them
    for(float i = up-step; i <= down+step; i += step) {
        // Change the color to be less dark
        line[0].color = SubGridLineColor;
        line[1].color = SubGridLineColor;
        // Add 4 lines that divide the step
        for(int j = 1; j < 5; j++) {
            line[0].position.y = i + (step/5.f) * j;
            line[1].position.y = i + (step/5.f) * j;
            target.draw(&line[0], 2, Lines, states);
        }
        // Return the original color
        line[0].color = GridLineColor;
        line[1].color = GridLineColor;
        
        if(abs(i) <= max(0.00001f, step/100.f)) continue;
        line[0].position.y = i;
        line[1].position.y = i;
        target.draw(&line[0], 2, Lines, states);
        
        drawPosNum(target, states, Vector2<double>(0, i));
    }
    
    
    // X-axis line
    Vertex xline[] = 
    {
        Vertex(Vector2f(screenMid.x - (screenSize.x / 2), 0), MainAxisColor),
        Vertex(Vector2f(screenMid.x + (screenSize.x / 2), 0), MainAxisColor),
    };
    target.draw(xline, 2, Lines, states);
    
    // Y-axis line
    Vertex yline[] = 
    {
        Vertex(Vector2f(0, screenMid.y - (screenSize.y / 2)), MainAxisColor),
        Vertex(Vector2f(0, screenMid.y + (screenSize.y / 2)), MainAxisColor),
    };
    target.draw(yline, 2, Lines, states);
    
}

void Grid::drawPosNum(RenderTarget& target, RenderStates states, Vector2<double> pos) const {
    // Get view scale
    float scale = getZoom(target.getView(), target) * m_txtSize;
    // And apply transformations to the text
    m_text.setScale(scale, scale);
    m_text.setPosition(Vector2f(pos));
    
    IntRect viewport = target.getViewport(target.getView());
    // cout << viewport.left << ", " << viewport.top << endl;
    // cout << viewport.width << ", " << viewport.height << endl;
    if(!viewport.contains(target.mapCoordsToPixel(Vector2f(pos))) && pos.x != pos.y) {
        // cout << "Doesn't contain: " << pos.x << ", " << pos.y << endl;
        if(pos.x == 0)
            m_text.setPosition(Vector2f(clamp(0, viewport.left, viewport.left + viewport.width), pos.y));
        else
            m_text.setPosition(Vector2f(pos.x, clamp(0, viewport.top, viewport.top + viewport.height)));
    }
    
    
    if(pos.x == pos.y)      // Only can happen with (0, 0)
        m_text.setString("0");
    
    else if(pos.x == 0)     // Vertical line
        m_text.setString(floatToString(pos.y));
    
    else                    // Horizontal line
        m_text.setString(floatToString(pos.x));
    
    // And draw the text of the position
    target.draw(m_text, states);
}
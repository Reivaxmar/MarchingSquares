#ifndef MARCHINGSQUARES_CLASS_H
#define MARCHINGSQUARES_CLASS_H

#include "SceneObject.h"
#include "FunctionHandler.h"
#include "ObjectUtils.h"
#include "Utils.h"
#include <bitset>
using namespace std;

// Marching sqares class
class MarchingSquares : public SceneObject {
public:
    MarchingSquares(FunctionHandler _funcHandler = FunctionHandler(), float _stepSize = 1.f);
    void setStepSize(float _stepSize);
    void setFunction(FunctionHandler _funcHandler);
    mutable FunctionHandler m_funcHandler;
private:
    float m_stepSize;
    mutable map<Vector2f, float, Vector2Comparator<float>> checks;
    virtual void draw(RenderTarget& target, RenderStates states) const;
    void handlePosition(Vector2f pos, RenderTarget& target, RenderStates states) const;
    Vector2f calculatePoint(int edgeNum, float vals[4]) const;

    // 1------2
    // |      |
    // |      |
    // 3------4
    // Side 1-2 -> 1, 2-4 -> 2, 4-3 -> 3, 3-1 -> 4
    // Hardcoded cases for Marching Squares
    Vector2i MScases[16] = {
        Vector2i(0, 0),   // 00 -> 0b0000
        Vector2i(1, 4),   // 01 -> 0b0001
        Vector2i(1, 2),   // 02 -> 0b0010
        Vector2i(2, 4),   // 03 -> 0b0011
        Vector2i(3, 4),   // 04 -> 0b0100
        Vector2i(1, 3),   // 05 -> 0b0101
        Vector2i(-1, -1), // 06 -> 0b0110
        Vector2i(2, 3),   // 07 -> 0b0111
        Vector2i(2, 3),   // 08 -> 0b1000
        Vector2i(-2, -2), // 09 -> 0b1001
        Vector2i(1, 3),   // 10 -> 0b1010
        Vector2i(3, 4),   // 11 -> 0b1011
        Vector2i(2, 4),   // 12 -> 0b1100
        Vector2i(1, 2),   // 13 -> 0b1101
        Vector2i(1, 4),   // 14 -> 0b1110
        Vector2i(0, 0)    // 15 -> 0b1111
    };
    struct LineData {
        Vector2f begin, end;
    };
    void processRow(float x, float up, float down, std::vector<LineData>& lines) const;
};

#endif // MARCHINGSQUARES_CLASS_H
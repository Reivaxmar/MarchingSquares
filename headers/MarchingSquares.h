#ifndef MARCHINGSQUARES_CLASS_H
#define MARCHINGSQUARES_CLASS_H

#include "SceneObject.h"
#include "FunctionHandler.h"
#include "ObjectUtils.h"
#include "Utils.h"
#include <bitset>

#include "LookupTables.h"

// Marching sqares class
class MarchingSquares : public SceneObject {
public:
    MarchingSquares(FunctionHandler _funcHandler = FunctionHandler(), float _stepSize = 1.f);

    void setStepSize(float _stepSize);
    void setFunction(FunctionHandler _funcHandler);

    mutable FunctionHandler m_funcHandler;

    void update(const sf::RenderWindow& window, const float& deltaTime) override;
private:
    float m_stepSize;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    // void handlePosition(sf::Vector2f pos, sf::RenderTarget& target, sf::RenderStates states) const;
    sf::Vector2f calculatePoint(int edgeNum, float vals[4]) const;

    
    struct SquareData {
        std::vector<sf::Vector2f> verts;
    };
    void processRow(float x, float up, float down, std::vector<SquareData>& squareData) const;
};

#endif // MARCHINGSQUARES_CLASS_H
#include "LookupTables.h"

// 1------2
// |      |
// |      |
// 3------4
// Side 1-2 -> 1, 2-4 -> 2, 4-3 -> 3, 3-1 -> 4
// Hardcoded cases for Marching Squares
sf::Vector2i MScases[16] = {
    sf::Vector2i(0, 0),   // 00 -> 0b0000
    sf::Vector2i(1, 4),   // 01 -> 0b0001
    sf::Vector2i(1, 2),   // 02 -> 0b0010
    sf::Vector2i(2, 4),   // 03 -> 0b0011
    sf::Vector2i(3, 4),   // 04 -> 0b0100
    sf::Vector2i(1, 3),   // 05 -> 0b0101
    sf::Vector2i(-1, -1), // 06 -> 0b0110
    sf::Vector2i(2, 3),   // 07 -> 0b0111
    sf::Vector2i(2, 3),   // 08 -> 0b1000
    sf::Vector2i(-2, -2), // 09 -> 0b1001
    sf::Vector2i(1, 3),   // 10 -> 0b1010
    sf::Vector2i(3, 4),   // 11 -> 0b1011
    sf::Vector2i(2, 4),   // 12 -> 0b1100
    sf::Vector2i(1, 2),   // 13 -> 0b1101
    sf::Vector2i(1, 4),   // 14 -> 0b1110
    sf::Vector2i(0, 0)    // 15 -> 0b1111
};



// 1------2
// |      |
// |      |
// 4------3
// Side 1-2 -> 1, 2-3 -> 2, 3-4 -> 3, 4-1 -> 4
// Hardcoded cases for Marching Squares
sf::Vector2i MScases2[16] = {
    sf::Vector2i(0, 0),   // 00 -> 0b0000
    sf::Vector2i(1, 4),   // 01 -> 0b0001
    sf::Vector2i(1, 2),   // 02 -> 0b0010
    sf::Vector2i(2, 4),   // 03 -> 0b0011
    sf::Vector2i(2, 3),   // 04 -> 0b0100
    sf::Vector2i(-2, -2), // 05 -> 0b0101
    sf::Vector2i(1, 3),   // 06 -> 0b0110
    sf::Vector2i(3, 4),   // 07 -> 0b0111
    sf::Vector2i(3, 4),   // 08 -> 0b1000
    sf::Vector2i(1, 3),   // 09 -> 0b1001
    sf::Vector2i(-1, -1), // 10 -> 0b1010
    sf::Vector2i(2, 3),   // 11 -> 0b1011
    sf::Vector2i(2, 4),   // 12 -> 0b1100
    sf::Vector2i(1, 2),   // 13 -> 0b1101
    sf::Vector2i(1, 4),   // 14 -> 0b1110
    sf::Vector2i(0, 0)    // 15 -> 0b1111
};

sf::Vector2f SquaresVerts[4] = {
    sf::Vector2f(0, 0),   // Vertex 1
    sf::Vector2f(1, 0),   // Vertex 2
    sf::Vector2f(1, 1),   // Vertex 3
    sf::Vector2f(0, 1)    // Vertex 4
};
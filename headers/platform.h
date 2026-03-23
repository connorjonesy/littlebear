#ifndef PLATFORM_H
#define PLATFORM_H

#include <SFML/Graphics.hpp>

struct Platform {
    sf::RectangleShape shape; // pos, size, colour
    sf::FloatRect getBounds() const { return shape.getGlobalBounds(); }
    //x,y,width,height
};
//floatrect for collision logic, rectangleshape for drawing to screen
//
#endif

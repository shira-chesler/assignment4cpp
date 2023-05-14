#include "Point.hpp"
#include <iostream>

namespace ariel{

//construcs a new point
Point::Point(double x_cor, double y_cor){
    this->x_cor = 0;
    this->y_cor = 0;
}

//compute the distance between two points       
double Point::distance(Point &othr){
    return 1;
}

// prints the point
void Point::print(){
    std::cout << "point" << std::endl;
}

//returns the nearest point to dst from src with at most distance of dist
Point moveTowards(Point src, Point dst, double dist){
    return Point(0,0);
}

bool Point::operator==(Point& othr){
    return false;
}
}
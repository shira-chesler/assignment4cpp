#include "Point.hpp"
#include <iostream>
#include <cmath>

namespace ariel{

//construcs a new point
Point::Point(double x_cor, double y_cor){
    this->x_cor = x_cor;
    this->y_cor = y_cor;
}

//compute the distance between two points       
double Point::distance(Point othr) const{
    double dx = this->x_cor - othr.x_cor;
    double dy = this->y_cor - othr.y_cor;
    return std::sqrt((dx*dx) + (dy*dy));
}

//getter to x coordinate
double Point::getX(){
    return this->x_cor;
}

//getter to y coordinate
double Point::getY(){
    return this->y_cor;
}

// returns a string of the point
std::string Point::print(){
    return "("+std::to_string(this->x_cor)+", "+std::to_string(this->y_cor)+")";
}

//returns the nearest point to dst from src with at most distance of dist
Point Point::moveTowards(Point src, Point dst, double max_dist){
    if (max_dist<0) throw std::invalid_argument("distance cannot be smaller than 0");
    double dx = dst.getX() - src.getX();
    double dy = dst.getY() - src.getY();
    double magnitude = std::sqrt(dx * dx + dy * dy);
    if (magnitude <= max_dist) {
        return dst;
    } else {
        double ratio = max_dist / magnitude;
        return {src.getX() + ratio * dx, src.getY() + ratio * dy};
    }
}

//compare operator
bool Point::operator==(Point& othr){
    return this->x_cor==othr.x_cor && this->y_cor==othr.y_cor;
}
}
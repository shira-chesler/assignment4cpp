#include "Character.hpp"

using namespace ariel;

Character::Character(Point loc, int hit_p, std::string name) : location(loc), hit_points(hit_p), name(name){

}

Character::Character(Character &charac):location(charac.location){

}

Character::Character(Character&& charac) noexcept : location(charac.location){

}

Character::~Character(){

}

bool Character::isAlive(){
    return false;
}

int Character::getHp(){
    return 0;
}

double Character::distance(Character* othr){
    return 0;
}

std::string Character::getName(){
    return "no one";
}

Point Character::getLocation(){
    return this->location;
}

void Character::setLocation(){
    this->location=Point(0,0);
}

std::string Character::print(){
    return "";
}

Character& Character::operator=(const Character& charac){
    return (*this);
}

Character& Character::operator=(Character&& charac) noexcept{
    return (*this);
}
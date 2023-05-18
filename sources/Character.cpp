#include "Character.hpp"

using namespace ariel;

//constructor
Character::Character(Point loc, int hit_p, std::string name) : location(loc), hit_points(hit_p), name(name){

}

//copy constructor
Character::Character(Character &charac) : location(charac.location), hit_points(charac.hit_points), name(charac.name){

}

//move constructor
Character::Character(Character&& charac) noexcept : location(charac.location), hit_points(charac.hit_points), name(charac.name){
    charac.hit_points=0;
    charac.in_team=false;
    charac.location=Point(0,0);
    charac.name="Annonymous";
}

//destructor
Character::~Character(){

}

//returns if the character is alive
bool Character::isAlive(){
    return this->hit_points>0;
}

//changes the hit points of the character
void Character::hit(int hit){
    if (hit<0) throw std::invalid_argument("cannot hit with a negative number");
    this->hit_points = std::max(this->hit_points-hit, 0);
}

//computes the distance between two characters
double Character::distance(Character* othr){
    return this->location.distance(othr->location);
}

//getter to the amount of hit points of the character
int Character::getHp(){
    return this->hit_points;
}

//getter to the name of the character
std::string Character::getName(){
    return this->name;
}

//getter to the location of the character
Point Character::getLocation(){
    return this->location;
}

//setter of the location of the character
void Character::setLocation(Point p){
    this->location=p;
}

//getter if the character is in a team
bool Character::getInTeam(){
    return this->in_team;
}

 //setter of being in a team    
void Character::SetInTeam(){
    this->in_team=true;
}

//assignment operator - for tidy (not nessecary cause we can't create an object)
Character& Character::operator=(const Character& charac){
    return (*this);
}

//move assignment operator - for tidy (not nessecary cause we can't create an object)
Character& Character::operator=(Character&& charac) noexcept{
    return (*this);
}
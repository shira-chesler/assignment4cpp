#include "Ninja.hpp"

using namespace ariel;

//constructor
Ninja::Ninja(std::string name, Point loc, int hit_p, int speed) : Character(loc, hit_p, name), speed(speed){

}

//copy constructor
Ninja::Ninja(Ninja &nin) : Character(nin){

}

//move constructor
Ninja::Ninja(Ninja&& nin) noexcept : Character(nin), speed(nin.speed){
    nin.speed=0;
}

//destructor
Ninja::~Ninja(){
    
}

//moves a ninja to the closest point possible to the enemy
void Ninja::move(Character* enemy){
    this->setLocation(Point::moveTowards(this->getLocation(), enemy->getLocation(),this->speed));
}

//the attack function of a ninja        
void Ninja::slash(Character* enemy){
    if(!enemy->isAlive()) throw std::runtime_error("enemy is dead");
    if(!this->isAlive()) throw std::runtime_error("a dead character can't attack");
    if(this == enemy) throw std::runtime_error("No self harm can be done");
    if(distance(enemy)>1) return;
    enemy->hit(40);
}

//returns string of the character's details
std::string Ninja::print(){
    if(this->isAlive()){
        return "N    "+this->getName()+"    "+std::to_string(this->getHp())+"    "+this->getLocation().print();
    }
    return "N    ("+this->getName()+")    --    "+this->getLocation().print();
}

//assignment operator - for tidy (not nessecary cause we can't create an object)
Ninja& Ninja::operator=(const Ninja& nin){
    return (*this);
}

//move assignment operator - for tidy (not nessecary cause we can't create an object)
Ninja& Ninja::operator=(Ninja&& nin) noexcept{
    return (*this);
}
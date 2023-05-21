#include "Cowboy.hpp"

using namespace ariel;

//constructor
Cowboy::Cowboy(std::string name, Point loc) : Character(loc, 110, name){
}

//decreases 10 hit points from the enemy
void Cowboy::shoot(Character* enemy){
    if(!enemy->isAlive()) throw std::runtime_error("Enemy is dead");
    if(!this->isAlive()) throw std::runtime_error("A dead character can't attack");
    if(this == enemy) throw std::runtime_error("No self harm can be done");
    if(this->num_bullets==0){
        reload();
        return;
    }
    enemy->hit(10);
    this->num_bullets--;
}

//returns if the cowboy has any bullets left
bool Cowboy::hasboolets() const{
    return this->num_bullets>0;
}

//reloads the number of bullets to the cowboy to 6
void Cowboy::reload(){
    if(!this->isAlive()) throw std::runtime_error("a dead cowboy can't reload");
    this->num_bullets = INITIAL_BULLETS_NUM;
}

//returns that this is a cowboy
std::string Cowboy::getType(){
    return "C";
}

//returns string of the character's details
std::string Cowboy::print(){
    if(this->isAlive()){
        return "C    "+this->getName()+"    "+std::to_string(this->getHp())+"    "+this->getLocation().print();
    }
    return "C    ("+this->getName()+")    --    "+this->getLocation().print();
}

int Cowboy::getNumBullets() const {
    return num_bullets;
}

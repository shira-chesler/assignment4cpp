#include "Ninja.hpp"

using namespace ariel;

Ninja::Ninja(std::string name, Point loc, int hit_p, int speed) : Character(loc, hit_p, name), speed(speed){

}

void Ninja::move(Character* enemy){

}

Ninja::Ninja(Ninja &nin) : Character(nin){

}

Ninja::Ninja(Ninja&& nin) noexcept : Character(nin){

}
        
void Ninja::slash(Character* enemy){
    
}

Ninja::~Ninja(){
    
}

Ninja& Ninja::operator=(const Ninja& nin){
    return (*this);
}

Ninja& Ninja::operator=(Ninja&& nin) noexcept{
    return (*this);
}
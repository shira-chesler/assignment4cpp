#include "Cowboy.hpp"

using namespace ariel;

Cowboy::Cowboy(std::string name, Point loc) : Character(loc, 110, name){
}

void Cowboy::shoot(Character* enemy){

}

bool Cowboy::hasboolets() const{
    return false;
}

void Cowboy::reload(){

}

std::string Cowboy::getType(){
    return "c";
}

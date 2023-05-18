#include "OldNinja.hpp"

using namespace ariel;

//constructor
OldNinja::OldNinja(std::string name, Point location) : Ninja(name, location,150,8){
}

//returns that this is a ninja - and its' type = old ninja
std::string OldNinja::getType(){
    return "ON";
}
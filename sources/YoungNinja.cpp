#include "YoungNinja.hpp"

using namespace ariel;

//constructor
YoungNinja::YoungNinja(std::string name, Point location) : Ninja(name, location,100,14){

}

//returns that this is a ninja - and its' type = young ninja
std::string YoungNinja::getType(){
    return "YN";
}
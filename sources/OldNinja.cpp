#include "OldNinja.hpp"

using namespace ariel;

OldNinja::OldNinja(std::string name, Point location) : Ninja(name, location,150,8){
}

std::string OldNinja::getType(){
    return "on";
}
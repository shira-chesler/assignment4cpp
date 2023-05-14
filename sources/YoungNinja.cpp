#include "YoungNinja.hpp"

using namespace ariel;

YoungNinja::YoungNinja(std::string name, Point location) : Ninja(name, location,100,14){

}

std::string YoungNinja::getType(){
    return "yn";
}
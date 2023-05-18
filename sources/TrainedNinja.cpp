#include "TrainedNinja.hpp"

using namespace ariel;

//constructor
TrainedNinja::TrainedNinja(std::string name, Point location) : Ninja(name, location,120,12){

}

//returns that this is a ninja - and its' type = trained ninja
std::string TrainedNinja::getType(){
    return "TN";
}
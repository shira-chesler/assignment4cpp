#include "TrainedNinja.hpp"

using namespace ariel;

TrainedNinja::TrainedNinja(std::string name, Point location) : Ninja(name, location,120,12){

}

std::string TrainedNinja::getType(){
    return "tn";
}
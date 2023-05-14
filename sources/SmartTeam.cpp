#include "SmartTeam.hpp"

using namespace ariel;

SmartTeam::SmartTeam(Character* leader){

}
SmartTeam::SmartTeam(SmartTeam &stem){

}
SmartTeam::SmartTeam(SmartTeam &&stem) noexcept{

}
int SmartTeam::stillAlive(){
    return 0;
}
Character* SmartTeam::getLeader(){
    return this->team.at(static_cast<unsigned long>(0));
}
void SmartTeam::attack(SmartTeam *enemys){

}
void SmartTeam::attack(Team *enemys){

}
void SmartTeam::add(Character* member){

}
std::string SmartTeam::print(){
    return "empy stm";
}
SmartTeam::~SmartTeam(){

}
SmartTeam& SmartTeam::operator=(const SmartTeam& stem){
    return (*this);
}
SmartTeam& SmartTeam::operator=(SmartTeam&& stem) noexcept{
    return (*this);
}
#include "Team2.hpp"

using namespace ariel;

Team2::Team2(Character* leader){
    team.at(static_cast<unsigned long>(0)) = leader;
    this->alive_members++;
    this->last_assigned=1;
}

Team2::Team2(Team2 &tem){

}

Team2::Team2(Team2 &&tem) noexcept{

}

void Team2::add(Character* member){
    this->team.at(static_cast<unsigned long>(last_assigned)) = member;
    last_assigned++;
}

void Team2::print(){

}

Team2::~Team2(){
    for (int i = 0; i < last_assigned; i++)
    {
        delete this->team.at(static_cast<unsigned long>(i));
    }
    
}

int Team2::stillAlive(){
    return 0;
}

Character* Team2::getLeader(){
    return this->team.at(static_cast<unsigned long>(0));
}

Team2& Team2::operator=(const Team2& tem){
    return (*this);
}

Team2& Team2::operator=(Team2&& tem) noexcept{
    return (*this);
}
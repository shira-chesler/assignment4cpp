#include "Team.hpp"
#include <stdexcept>

using namespace ariel;

Team::Team(Character* leader){
    this->alive_members=1;
    this->leader_position=0;
    std::string tp = leader->getType();
    if (tp=="c"){
        this->highest_cowboy_position++;
        this->team.at(static_cast<unsigned long>(this->highest_cowboy_position)) = leader;
    }
    else{
        this->lowest_ninja_position--;
        this->team.at(static_cast<unsigned long>(this->lowest_ninja_position)) = leader;
    }
}

Team::Team(Team &tem){

}

Team::Team(Team &&tem) noexcept{

}

Character* Team::getLeader(){
    return this->team.at(static_cast<unsigned long>(0));
}

void Team::add(Character* member){
    for (int i = 0; i < highest_cowboy_position+1; i++)
    {
        if (team.at(static_cast<unsigned long>(i))==member)
        {
            throw std::invalid_argument("this member already exists");
        }
        
    }
    for (int i = 9; i > lowest_ninja_position-1; i--)
    {
        if (team.at(static_cast<unsigned long>(i))==member)
        {
            throw std::invalid_argument("this member already exists");
        }
    }
    
    std::string tp = member->getType();
    if (tp=="c"){
        this->highest_cowboy_position++;
        this->team.at(static_cast<unsigned long>(this->highest_cowboy_position++)) = member;
    }
    else{
        this->lowest_ninja_position--;
        this->team.at(static_cast<unsigned long>(this->lowest_ninja_position)) = member;
    }
}

int Team::stillAlive(){
    return 0;
}

void Team::attack(Team *enemys){

}

std::string Team::print(){
    return "empty";
}

Team::~Team(){
    for (int i = 0; i < highest_cowboy_position+1; i++)
    {
        delete team.at(static_cast<unsigned long>(i));
    }
    for (int i = 9; i > lowest_ninja_position-1; i--)
    {
        delete team.at(static_cast<unsigned long>(i));
        
    }
    
}

Team& Team::operator=(const Team& tem){
    return (*this);
}

Team& Team::operator=(Team&& tem) noexcept{
    return (*this);
}
#include "Team2.hpp"
#include "limits"
using namespace ariel;

// constructor
Team2::Team2(Character* leader) : Team(){
    this->setLeader(0);
    this->setTeamAt(leader, 0);
    this->last_assigned=0;
}

//attack function for team 2
void Team2::attack(Team *enemys){
    check_change_leader();
    if(!enemys) throw std::invalid_argument("a nullptr has been given as a pointer");
    if(enemys->stillAlive()==0) throw std::runtime_error("cannot attack a dead team");
    if (stillAlive()==0) return;
    if(this == enemys) throw std::runtime_error("group cannot attck itself");
    if(!this->getStartedGame()){
        setStrtedGame(true);
        enemys->setStrtedGame(true);
    }
    Character* victim = find_closest(enemys);
    for (size_t i = 0; i < last_assigned+1; i++)
    {
        Character* cur = nullptr;
        if(getTeamAt(i)->isAlive()) cur = getTeamAt(i);
        if (cur && enemys->stillAlive()>0)
        {
            if (victim->getHp()==0){
                victim=find_closest(enemys);
            }
            if(victim==nullptr) break;
            if(cur->getType()=="C") dynamic_cast<Cowboy*>(cur)->shoot(victim);
            else{
                if(cur->distance(victim)<=1) dynamic_cast<Ninja*>(cur)->slash(victim);
                else{
                    dynamic_cast<Ninja*>(cur)->move(victim);
                }
            }
        }

    }
    if (enemys->stillAlive()==0)
    {
        this->setStrtedGame(false);
        enemys->setStrtedGame(false);
    }
}

//adding to team function for team 2
void Team2::add(Character* member){
    setTeamAt(member, last_assigned+1);
    last_assigned++;
}

//printing function for team 2
void Team2::print(){
    for (size_t i = 0; i < last_assigned+1; i++)
    {
        std::cout << getTeamAt(i)->print() << std::endl;
    }

}

//checks if need to change the leader (leader is dead), changes if there's a need
void Team2::check_change_leader(){
    if(this->getLeaderStraight()->isAlive()) return;
    if(this->stillAlive()==0) return;
    double tmp = std::numeric_limits<double>::max();
    size_t newlpos = 11;
    for (size_t i = 0; i < last_assigned+1; i++)
    {
        if(getTeamAt(i)!=nullptr && getTeamAt(i)->isAlive()){
            double dist = getLeaderStraight()->distance(getTeamAt(i));
            if(dist<tmp){
                tmp = dist;
                newlpos = i;
            }
        }
    }
    if (newlpos==11)
    {
        throw std::runtime_error("error with finding new leader");
    }
    setLeader(newlpos);
}


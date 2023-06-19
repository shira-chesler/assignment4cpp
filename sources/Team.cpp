#include "Team.hpp"
#include <stdexcept>
#include <iostream>
#include "limits"

using namespace ariel;

//team can't add a dead character/ nullptr

//default constructor
Team::Team() {
    this->team.fill(nullptr);
}

//constructor
Team::Team(Character *leader) {
    //if(this->stillAlive()==10) throw std::runtime_error("there are enough members in team");
    if (leader == nullptr) throw std::runtime_error("A nullptr cannot be a member");
    if (leader->getInTeam()) throw std::runtime_error("this ch is already in a team");
    if (!leader->isAlive()) throw std::runtime_error("can't add a dead character to team");
    this->team.fill(nullptr);
    std::string tp = leader->getType();
    if (tp == "C") {
        this->highest_cowboy_position++;
        setTeamAt(leader, static_cast<size_t>(highest_cowboy_position));
        this->leader_position = static_cast<size_t>(highest_cowboy_position);
    } else {
        this->lowest_ninja_position--;
        setTeamAt(leader, lowest_ninja_position);
        this->leader_position = lowest_ninja_position;
    }
    this->started_game = false;
}

//copy constructor
Team::Team(Team &tem) {
    this->highest_cowboy_position = tem.highest_cowboy_position;
    this->leader_position = tem.leader_position;
    this->lowest_ninja_position = tem.lowest_ninja_position;
    this->started_game = tem.started_game;
    this->team = tem.team;
}

//move constructor
Team::Team(Team &&tem) noexcept {
    this->highest_cowboy_position = tem.highest_cowboy_position;
    this->leader_position = tem.leader_position;
    this->lowest_ninja_position = tem.lowest_ninja_position;
    this->started_game = tem.started_game;
    this->team = tem.team;
    tem.highest_cowboy_position = -1;
    tem.leader_position = 11;
    tem.lowest_ninja_position = 10;
    tem.started_game = false;
    tem.team.fill(nullptr);
}

//destructor
Team::~Team() {
    for (size_t i = 0; i < 10; i++) {
        delete team.at(i);
    }
}

//adding a member to the team
void Team::add(Character *member) {
    if (member == nullptr) throw std::runtime_error("A nullptr cannot be added as a member");
    std::string tp = member->getType();
    if (tp == "C") {
        setTeamAt(member, static_cast<size_t>(this->highest_cowboy_position + 1));
        this->highest_cowboy_position++;
    } else {
        setTeamAt(member, this->lowest_ninja_position - 1);
        this->lowest_ninja_position--;
    }
}

//returns the number of alive members in the group
int Team::stillAlive() {
    int count = 0;
    for (auto character: team) {
        if (character != nullptr && character->isAlive()) count++;
    }
    return count;
}

//attack function of team
void Team::attack(Team *enemys) {
    check_change_leader();
    if (!enemys) throw std::invalid_argument("a nullptr has been given as a pointer");
    if (enemys->stillAlive() == 0) throw std::runtime_error("cannot attack a dead team");
    if (this->stillAlive() == 0) throw std::runtime_error("a dead team can't attack");
    if (this == enemys) throw std::runtime_error("group cannot attck itself");
    if (!started_game) {
        setStrtedGame(true);
        enemys->setStrtedGame(true);
    }
    
    Character *victim = find_closest(enemys);
    for (size_t i = 0; i < highest_cowboy_position + 1; i++) {
        if (team.at(i)->isAlive() && enemys->stillAlive() > 0) {
            if (!victim->isAlive()) {
                victim = find_closest(enemys);
            }
            if (victim == nullptr) break;
            dynamic_cast<Cowboy *>(team.at(i))->shoot(victim);
        }

    }
    for (size_t i = 9; i > lowest_ninja_position - 1; i--) {
        if (team.at(i)->isAlive() && enemys->stillAlive() > 0 && victim != nullptr) {
            if (!victim->isAlive()) {
                victim = find_closest(enemys);
            }
            if (victim == nullptr) break;
            if (team.at(i)->distance(victim) <= 1) dynamic_cast<Ninja *>(team.at(i))->slash(victim);
            else {
                dynamic_cast<Ninja *>(team.at(i))->move(victim);
            }
        }
    }
    if (enemys->stillAlive() == 0) {
        this->setStrtedGame(false);
        enemys->setStrtedGame(false);
    }
}

//prints the members of the team
void Team::print() {
    for (size_t i = 0; i < highest_cowboy_position + 1; i++) {
        std::cout << team.at(i)->print() << std::endl;
    }
    for (size_t i = 9; i > lowest_ninja_position - 1; i--) {
        std::cout << team.at(i)->print() << std::endl;
    }
}

//checks if need to change the leader (leader is dead), changes if there's a need
void Team::check_change_leader() {
    if (this->team.at(leader_position)->isAlive()) return;
    if (stillAlive() == 0) return;
    double tmp = std::numeric_limits<double>::max();
    size_t newlpos = 11;
    for (size_t i = 0; i < highest_cowboy_position + 1; i++) {
        if (team.at(i) != nullptr && team.at(i)->isAlive()) {
            double dist = team.at(leader_position)->distance(team.at(i));
            if (dist < tmp) {
                tmp = dist;
                newlpos = i;
            }
        }
    }
    for (size_t i = 9; i > lowest_ninja_position - 1; i--) {
        printf("a %d\n", team.at(i)->getHp());
        if (team.at(i) != nullptr && team.at(i)->isAlive()) {
            double dist = team.at(leader_position)->distance(team.at(i));
            if (dist < tmp) {
                tmp = dist;
                newlpos = i;
            }
        }
    }
    if (newlpos == 11) {
        printf("s %d\n", stillAlive());
        throw std::runtime_error("error with finding new leader");
    }
    setLeader(newlpos);
}

//finds the closest of the enemys
Character *Team::find_closest(Team *enemy) {
    double tmp = std::numeric_limits<double>::max();
    Character *victim = nullptr;
    Character *myleader = team.at(leader_position);
    for (size_t i = 0; i < 10; i++) {
        if (enemy->team.at(i) != nullptr && enemy->team.at(i)->isAlive()) {
            double dist = enemy->team.at(i)->distance(myleader);
            if (dist < tmp) {
                tmp = dist;
                victim = enemy->team.at(i);
            }
        }
    }
    return victim;
}

//sets the started game value
void Team::setStrtedGame(bool set_to) {
    this->started_game = set_to;
}

//sets team at specific position
void Team::setTeamAt(Character *newmember, size_t at) {
    if (newmember == nullptr) throw std::runtime_error("A nullptr cannot be added as a member");
    if (newmember->getInTeam()) throw std::runtime_error("this ch is already in a team");
    if (!newmember->isAlive()) throw std::runtime_error("can't add a dead character to team");
    if (started_game) throw std::runtime_error("cannot add a member while playing game");
    if (actualSize() == 10) throw std::runtime_error("team is full");
    this->team.at(at) = newmember;
    newmember->SetInTeam();
}

size_t Team::actualSize() const{
    std::size_t count = 0;
    for (const auto& ptr : team) {
        if (ptr != nullptr) {
            ++count;
        }
    }
    return count;
}

//sets a new leader
void Team::setLeader(size_t nleaderpos) {
    this->leader_position = nleaderpos;
}

//returns a pointer to the leader object
Character *Team::getLeader() {
    check_change_leader();
    return this->team.at(static_cast<unsigned long>(this->leader_position));
}

//a bit more dangerous function - returns the leader without checking he's valid and alive
Character *Team::getLeaderStraight() {
    return this->team.at(static_cast<unsigned long>(this->leader_position));
}

//getter to member of team
Character *Team::getTeamAt(size_t at) {
    if (at > 9) throw std::runtime_error("invalid index");
    return team.at(at);
}

//getter to started game value
bool Team::getStartedGame() {
    return this->started_game;
}

// ...
Team &Team::operator=(const Team &tem) {
    return (*this);
}

// ....
Team &Team::operator=(Team &&tem) noexcept {
    return (*this);
}

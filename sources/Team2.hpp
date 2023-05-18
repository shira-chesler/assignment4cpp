#ifndef TEAM2_H
#define TEAM2_H

#include <array>
#include "Team.hpp"
#include <iostream>

constexpr int INIT_PLACEMENT = 11;

namespace ariel {
    class Team2 : public Team {
        private:
        size_t last_assigned =INIT_PLACEMENT;

        public:
        Team2(Character* leader);
    
        void attack(Team *enemys) override;
        void add(Character* member) override;
        void print() override;

        void check_change_leader() override;
    };
}
#endif 

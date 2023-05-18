#ifndef SMARTTEAM_H
#define SMARTTEAM_H

#include <array>
#include "Character.hpp"
#include "Cowboy.hpp"
#include "OldNinja.hpp"
#include "TrainedNinja.hpp"
#include "YoungNinja.hpp"
#include "Team.hpp"

namespace ariel {
    class SmartTeam {
        std::array<Character*, NUM_MEMBERS_OF_A_TEAM> team;
        bool started_game;
        int alive_members;
        int leader_position;

        public:
        SmartTeam(Character* leader);
        SmartTeam(SmartTeam &stem);
        SmartTeam(SmartTeam &&stem) noexcept;
        int stillAlive();
        void attack(SmartTeam *enemys);
        void attack(Team *enemys);
        void add(Character* member);
        Character* getLeader();
        std::string print();
        ~SmartTeam();
        SmartTeam& operator=(const SmartTeam& stem);
        SmartTeam& operator=(SmartTeam&& stem) noexcept;
    };
}

#endif 

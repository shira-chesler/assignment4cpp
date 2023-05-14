#ifndef TEAM_H
#define TEAM_H

#include <array>
#include "Character.hpp"
#include "Cowboy.hpp"
#include "OldNinja.hpp"
#include "TrainedNinja.hpp"
#include "YoungNinja.hpp"

constexpr int NUM_MEMBERS_OF_A_TEAM = 10;

namespace ariel {
    class Team {
        std::array<Character*, NUM_MEMBERS_OF_A_TEAM> team;
        bool started_game;
        int highest_cowboy_position=-1;
        int lowest_ninja_position=NUM_MEMBERS_OF_A_TEAM;
        int alive_members;
        int leader_position;

        public:
        Team(Character* leader);
        Team(Team &tem);
        Team(Team &&tem) noexcept;
        int stillAlive();
        void attack(Team *enemys);
        void add(Character* member);
        Character* getLeader();
        std::string print();
        virtual ~Team();
        Team& operator=(const Team& tem);
        Team& operator=(Team&& tem) noexcept;
    };
}

#endif 

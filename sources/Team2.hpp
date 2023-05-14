#ifndef TEAM2_H
#define TEAM2_H

#include <array>
#include "Character.hpp"

constexpr int NUM_MEMBERS_OF_A_TEAM2 = 10;

namespace ariel {
    class Team2 {
        private:
        std::array<Character*, NUM_MEMBERS_OF_A_TEAM2> team;
        bool started_game;
        int alive_members=0;
        int leader_position;
        int last_assigned =0;

        public:
        Team2(Character* leader);
        Team2(Team2 &tem);
        Team2(Team2 &&tem) noexcept;
        int stillAlive();
        void add(Character* member);
        void print();
        Character* getLeader();
        ~Team2();
        Team2& operator=(const Team2& tem);
        Team2& operator=(Team2&& tem) noexcept;
    };
}
#endif 

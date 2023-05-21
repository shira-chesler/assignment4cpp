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
        bool started_game=false;
        int highest_cowboy_position=-1;
        size_t lowest_ninja_position=NUM_MEMBERS_OF_A_TEAM;
        size_t leader_position=0;

    public:
        Team();
        Team(Character* leader);
        Team(Team &tem);
        Team(Team &&tem) noexcept;
        virtual ~Team();

        int stillAlive();
        virtual void attack(Team *enemys);
        virtual void add(Character* member);
        virtual void print();

        virtual void check_change_leader();
        Character* find_closest(Team* Character);

        void setStrtedGame(bool set_to);
        void setTeamAt(Character *newmember, size_t at_i);
        void setLeader(size_t nleaderpos);
        Character* getLeader();
        Character* getLeaderStraight();
        Character* getTeamAt(size_t at_i);
        bool getStartedGame();

        Team& operator=(const Team& tem);
        Team& operator=(Team&& tem) noexcept;

        size_t actualSize() const;
    };
}

#endif
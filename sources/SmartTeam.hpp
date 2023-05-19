#ifndef SMARTTEAM_H
#define SMARTTEAM_H

#include <array>
#include "Character.hpp"
#include "Cowboy.hpp"
#include "OldNinja.hpp"
#include "TrainedNinja.hpp"
#include "YoungNinja.hpp"
#include "Team2.hpp"

namespace ariel {
    class SmartTeam :public Team2{


        public:
        SmartTeam(Character* leader);
        void attack(Team *enemys) override;
    };
}

#endif 
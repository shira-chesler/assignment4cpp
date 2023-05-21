#ifndef SMARTTEAM_H
#define SMARTTEAM_H

#include <array>
#include <vector>
#include "Character.hpp"
#include "Cowboy.hpp"
#include "OldNinja.hpp"
#include "TrainedNinja.hpp"
#include "YoungNinja.hpp"
#include "Team2.hpp"

namespace ariel {
    class SmartTeam : public Team2 {

    public:
        SmartTeam(Character *leader);

        void attack(Team *enemys) override;

    private:
        static double enemyScore(Character *enemy, Team *enemyTeam, Character *attackingCharacter);
        static int NinjaAttackScoreAdd(Character *attackingCharacter, Character *enemy);

    };
}

#endif 
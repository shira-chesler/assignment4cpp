#include "SmartTeam.hpp"
#include <map>

using namespace ariel;
const int youngSpeed = 14;
const int trainedSpeed = 12;
const int oldSpeed = 8;


// This function calculates and returns a score for a given enemy.
// The score is calculated based on several factors:
// 1. The enemy's health - lower health enemies have a higher score.
// 2. The type of the character making the attack - different types of characters (Cowboy or different types of Ninjas) adjust the score differently.
// 3. The number of bullets left (if the character is a Cowboy) - the more bullets left, the higher the score.
// 4. The proximity of other enemies - the more enemies are near the target enemy, the higher the score.
double SmartTeam::enemyScore(Character *enemy, Team *enemyTeam, Character *attackingCharacter) {
    double score = 0;

    double healthScore = 1.0 / enemy->getHp();
    score += healthScore * healthScore;

    int speed = 0;
    if (attackingCharacter->getType() == "C") {
        auto *cowboy = dynamic_cast<Cowboy *>(attackingCharacter);
        if (cowboy->hasboolets()) {
            score += 5 * cowboy->getNumBullets();
        }
    } 
    else if (attackingCharacter->getType() == "YN") {
        speed = youngSpeed;
        score += NinjaAttackScoreAdd(attackingCharacter, enemy);
    } 
    else if (attackingCharacter->getType() == "TN") {
        speed = trainedSpeed;
        score += NinjaAttackScoreAdd(attackingCharacter, enemy);
    } 
    else { 
        speed = oldSpeed;
        score += NinjaAttackScoreAdd(attackingCharacter, enemy);
    }

    int nearbyEnemies = 0;
    for(size_t i; i<10; i++){ 
        Character *other = enemyTeam->getTeamAt(i);
        if (other != enemy && other != nullptr && other->isAlive()) {
            double distance = enemy->distance(other);
            if (distance <= speed) {
                nearbyEnemies++;
            }
        }
    }
    score += nearbyEnemies;
    return score;
}

//help function to check if to add to the score of the enemy
int SmartTeam::NinjaAttackScoreAdd(Character *attackingCharacter, Character *enemy){
    if (attackingCharacter->distance(enemy) <= 1) {
            return 40;
    }
    return 0;
}


// This function makes the SmartTeam attack the enemy team.
// It does this by iterating over each character in the SmartTeam, and for each character:
// 1. If the character is not alive, it skips the character.
// 2. Otherwise, it calculates a score for each enemy in the enemy team.
// 3. It targets the enemy with the highest score.
// 4. If the character is a Cowboy and has bullets, it makes the Cowboy shoot the targeted enemy.
// 5. If the character is a Ninja, it checks the distance to the targeted enemy.
// 6. If the distance is less than or equal to 1, it makes the Ninja slash the targeted enemy.
// 7. Otherwise, it makes the Ninja move towards the targeted enemy.
// 8. If there are no enemies left alive, it breaks the loop.
void SmartTeam::attack(Team *enemyTeam) {
    //checks before an attack
    check_change_leader();
    if(!enemyTeam) throw std::invalid_argument("a nullptr has been given as a pointer");
    if(enemyTeam->stillAlive()==0) throw std::runtime_error("cannot attack a dead team");
    if (stillAlive()==0) return;
    if(this == enemyTeam) throw std::runtime_error("group cannot attck itself");
    if(!this->getStartedGame()){
        setStrtedGame(true);
        enemyTeam->setStrtedGame(true);
    }

    //attacking
    for (size_t j; j<10; j++){
        Character *attackingCharacter = this->getTeamAt(j);
        if (attackingCharacter == nullptr || !attackingCharacter->isAlive()) {
            continue;
        }

        //scoring the characters
        std::array<double, 10> scores{0};
        for (size_t i; i<10; i++){
            Character* enemy = enemyTeam->getTeamAt(i);
            if (enemy == nullptr || !enemy->isAlive()) {
                continue;
            }
            double score = this->enemyScore(enemy, enemyTeam, attackingCharacter);
            scores.at(i) = score;
        }

        //choosing the best character according to the scores
        Character *bestEnemy = nullptr;
        double bestScore = -1;
        for (size_t i=0; i<10; i++){
            double score = scores.at(i);
            if (score > bestScore) {
                bestScore = score;
                bestEnemy = enemyTeam->getTeamAt(i);
            }
        }

        // attcaking the enemy according to rules if not noll
        if (bestEnemy != nullptr) {
            if (attackingCharacter->getType() == "C") {
                dynamic_cast<Cowboy *>(attackingCharacter)->shoot(bestEnemy);
            } 
            else{ 
                if (attackingCharacter->distance(bestEnemy) <= 1) {
                    dynamic_cast<Ninja *>(attackingCharacter)->slash(bestEnemy);
                } 
                else {
                    dynamic_cast<Ninja *>(attackingCharacter)->move(bestEnemy);
                }
            }
        }
        
        //end of attack - the enemy team is dead
        if (enemyTeam->stillAlive() == 0) {
            break;
        }
    }
}

SmartTeam::SmartTeam(Character *leader) : Team2(leader) {
}


